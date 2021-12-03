#include "4_banh_omi.h"
#include "config_uart.h"
#include "math.h"



int16_t v_A, v_B, v_C, v_D;//bien luu v 4 banh
float radian = 3.141592653589793238462643/1800;//chuyen doi sang radian
uint8_t lock=5;//tranh khoa banh
uint8_t v_limit=254;//van toc lon nhat
int16_t v_tinh_tien;//van toc tinh tien cho phep
int16_t v_xoay;//van toc xoay cho phep
int16_t goc_tinh_tien,goc_quay;//goc tinh tien va goc xoay can
float Kp=0.05, Ki=0.001, Kd=0;//he so pid dieu chinh bu goc
uint8_t che_do;//che do khoa banh dot ngot, =1 khoa banh,=0 binh thuong
uint8_t che_do_dung=2;//che do dung =1 luon khoa banh, che do dung =0 khoa banh theo time
int16_t v_thuc;//v hien tai cua robot
uint8_t he_so_gia_toc=1,he_so_giam_toc=1;//he so tang giam toc do
float v_max;
int16_t v_quay;
uint16_t dem_dung,time_khoa_banh=250;

float value_A,value_B,value_C,value_D;
float chieu_A,chieu_B,chieu_C,chieu_D;
int mor_A,mor_B,mor_C,mor_D;
 uint8_t data_send_PID[3];


int16_t gioi_han( int16_t x, int16_t level )
{
  if ( x > level ) return level;
  else if ( x < -level ) return -level;
  else return x;
}

float maxF4(float N1, float N2, float N3, float N4)
{
	float _maxNum;
	if(N1<0) N1 = -N1;
	if(N2<0) N2 = -N2;
	if(N3<0) N3 = -N3;
	if(N4<0) N4 = -N4;

	if(N1>_maxNum) _maxNum = N1;
	if(N2>_maxNum) _maxNum = N2;
	if(N3>_maxNum) _maxNum = N3;
	if(N4>_maxNum) _maxNum = N4;

	return _maxNum;
}

int16_t tinh_he_so(int16_t goc_can_lay)
{
  int16_t output_c, P, I, D;
  int16_t sai_so_goc_truoc, sai_so_goc;
  sai_so_goc = goc_can_lay - goc;
  P = sai_so_goc;
  I += sai_so_goc;
  D = sai_so_goc - sai_so_goc_truoc;
  sai_so_goc_truoc = sai_so_goc;
  output_c = (Kp * P) + (Ki * I) + (Kd * D);
	gioi_han(output_c,v_xoay);
  return output_c;
}

//---------------su dung khi chay bang UART-----------------//
void send_PID(uint8_t _chieu, uint8_t _dia_chi, uint8_t _vantoc)
{
	data_send_PID[0] = (_chieu<<7)|_dia_chi;
	data_send_PID[1] = _vantoc;
	data_send_PID[2] = 255;
	HAL_UART_Transmit(&huart4,data_send_PID,3,3);
}
//---------------su dung khi chay bang UART-----------------//
void set_motor(int16_t _v_A,int16_t _v_B,int16_t _v_C,int16_t _v_D)
{
	if(_v_A>v_limit) mor_A=v_limit;
	else mor_A=_v_A;
	
	if(_v_B>v_limit) mor_B=v_limit;
	else mor_B=_v_B;
	
	if(_v_C>v_limit) mor_C=v_limit;
	else mor_C=_v_C;
	
	if(_v_D>v_limit) mor_D=v_limit;
	else mor_D=_v_D;
	
	send_PID(chieu_A,1,mor_A);
	send_PID(chieu_B,2,mor_B);
	send_PID(chieu_C,3,mor_C);
	send_PID(chieu_D,4,mor_D);	
}
//-----------------------------------------------------------//
void di_chuyen(int16_t _van_toc_tinh_tien,int16_t _goc_tinh_tien, int16_t _goc_quay)
{
  v_quay = tinh_he_so(_goc_quay);
	
	value_A=1.5 * cosf(((_goc_tinh_tien - goc - 2250) * radian));
	value_B=1.5 * cosf(((_goc_tinh_tien - goc + 450)  * radian));
	value_C=1.5 * cosf(((_goc_tinh_tien - goc - 450)  * radian));
	value_D=1.5 * cosf(((_goc_tinh_tien - goc - 1350) * radian));
	
	v_max= v_limit/maxF4(value_A,value_B,value_C,value_D) - v_quay;
	if(_van_toc_tinh_tien>v_max) _van_toc_tinh_tien=v_max;
	

  v_A = v_quay + _van_toc_tinh_tien * value_A; //v A
  v_B = v_quay + _van_toc_tinh_tien * value_B; //v B
  v_C = v_quay + _van_toc_tinh_tien * value_C; //v C
  v_D = v_quay + _van_toc_tinh_tien * value_D; //v D

//========================motor A=========================//
	if(v_A>0) chieu_A=0;
	else
	{
		v_A=-v_A;
		chieu_A=1;
	}
//	v_A=v_A+lock;
//========================motor B=========================//	
	if(v_B>0) chieu_B=0;
	else
	{
		v_B=-v_B;
		chieu_B=1;
	}
//	v_B=v_B+lock;
//========================motor C=========================//
	if(v_C>0) chieu_C=0;
	else
	{
		v_C=-v_C;
		chieu_C=1;
	}
//	v_C=v_C+lock;
//========================motor D=========================//	
	if(v_D>0) chieu_D=0;
	else
	{
		v_D=-v_D;
		chieu_D=1;
	}
//	v_D=v_D+lock;	
	if (0<v_A&&v_A<4) {v_A=0;} 
  if (0<v_B&&v_B<4) {v_B=0;} 
	if (0<v_C&&v_C<4) {v_C=0;} 
	if (0<v_D&&v_D<4) {v_D=0;} 
	
	set_motor(v_A,v_B,v_C,v_D);
}

void dung(void)
{
	if(che_do_dung==1)
	{
		set_motor(2,2,2,2);
		return;
	}
	else if(che_do_dung==2)
	{
		set_motor(0,0,0,0);
		return;
	}
	if(dem_dung++ < time_khoa_banh) set_motor(2,2,2,2);
	else 
	{
		dem_dung = time_khoa_banh;
		set_motor(0,0,0,0);
	}
}


void chinh_robot(void)
{
	if(che_do==1)//che do phanh dot ngot
	{	
		return;
	}
	//=================gia toc===================//
	if(v_tinh_tien>0)//neu vua chay vua xoay
	{
		dem_dung=0;
		if(v_thuc<v_tinh_tien)//gia toc
		{
			v_thuc=v_thuc+he_so_gia_toc;
			if(v_thuc>v_tinh_tien) v_thuc=v_tinh_tien;
		}
		else if(v_thuc>v_tinh_tien)//giam toc
		{
			v_thuc=v_thuc-he_so_giam_toc;//giam toc
			if(v_thuc<v_tinh_tien) v_thuc=v_tinh_tien;
		}
	}
	else //neu dung im
	{
		if(v_thuc>0)
		{
			v_thuc=v_thuc-he_so_giam_toc;//giam toc
			if(v_thuc<0) v_thuc=0;
		}
		else
		{
			dung();
			return;
		}
	}
	di_chuyen(v_thuc,goc_tinh_tien, goc_quay);//muon xoay tai cho set v tinh tien = 0
	
}

void robot_run(int16_t _goc_tinh_tien,int16_t _v_tinh_tien,int16_t _goc_quay,int16_t _v_xoay)
{
	che_do=0;
	v_tinh_tien=_v_tinh_tien;
	v_xoay=_v_xoay;
	goc_tinh_tien=_goc_tinh_tien;
	goc_quay=_goc_quay;
	if(v_thuc==0&&v_tinh_tien>v_thuc) v_thuc=10;
}


void xoay_phai(void)
{
	che_do=1;
	v_tinh_tien=0;
	v_thuc=0;
	chieu_A=1;
	chieu_B=1;
	chieu_C=1;
	chieu_D=1;
	set_motor(15,15,15,15);
}

void xoay_trai(void)
{
	che_do=1;
	v_tinh_tien=0;
	v_thuc=0;
	chieu_A=0;
	chieu_B=0;
	chieu_C=0;
	chieu_D=0;
	set_motor(15,15,15,15);
	
}

void phanh_robot(void)
{
	che_do=1;
	v_tinh_tien=0;
	v_thuc=0;
	set_motor(2,2,2,2);
}

void robot_stop(uint8_t _che_do_dung,uint8_t _giam_toc)
{
	che_do=0;
	che_do_dung=_che_do_dung;
	v_tinh_tien=0;
	he_so_giam_toc=_giam_toc;
}
