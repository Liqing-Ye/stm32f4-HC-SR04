#ifndef __INA226_H
#define __INA226_H
#include "sys.h"
#include "myiic.h"
#include "delay.h"

// ---ģ�����---
// VCC 3.3V/5V
// GND GND
// SCL PB8 ��ʱ���ߣ�
// SDA PB9 �������ߣ�
// ALE ��������(δʹ�ñ������ܿɲ���)
// -------------

#define READ_ADDR                  0x81	 //A1=GND��A2=GND // R=1, W=0
#define WRITE_ADDR                 0x80

#define Config_Reg                 0x00 // ���üĴ���  // ������
#define Shunt_V_Reg                0x01 // ������ѹ�Ĵ���
#define Bus_V_Reg                  0x02 // ���ߵ�ѹ�Ĵ���
#define Power_Reg                  0x03 // ���ʼĴ���
#define Current_Reg                0x04 // �����Ĵ���
#define Calib_Reg                  0x05 // У׼�Ĵ���  // ������
#define Mask_En_Reg                0x06 // ����/ʹ�ܼĴ���  // ������
#define Alert_Reg                  0x07 // �������ƼĴ��� // ������
#define Man_ID_Reg                 0xFE  //0x5449 // ������ ID ע��
#define ID_Reg                     0xFF  //0x2260 // ����Ψһ��оƬ��ʶ��

//������������
#define INA226_VAL_LSB						 2.5f	//������ѹ LSB 2.5uV
#define Voltage_LSB		  					 1.25f   //���ߵ�ѹ LSB 1.25mV
#define CURRENT_LSB 	 						 1.0f 	//����LSB 1mA
#define POWER_LSB       					 25*CURRENT_LSB
#define CAL             					 456     //0.00512/(Current_LSB*R_SHUNT) = 470  //����ƫ���С

typedef struct
{
	float voltageVal;			//mV
	float Shunt_voltage;		//uV
	float Shunt_Current;		//mA
	float Power_Val;				//����
	float Power;				//����mW
	u32   ina226_id;
}INA226;

extern INA226 ina226_data;

// ģ��ײ�ʵ�ֲ���
void INA226_SetRegPointer(u8 addr,u8 reg);
void INA226_SendData(u8 addr,u8 reg,u16 data);

u16 INA226_ReadData(u8 addr);
void INA226_Get_ID(u8 addr);			
u16 INA226_GetVoltage( u8 addr);		//��ȡ���ߵ�ѹװ��ֵ
u16 INA226_GetShunt_Current(u8 addr);	//��ȡ��������װ��ֵ
u16 INA226_GetShuntVoltage(u8 addr);	//������ѹװ��ֵ
u16 INA226_Get_Power(u8 addr);		//��ȡ����װ��ֵ����ʹ��
void Get_Power(float *Power);     //��ȡ����,ina226�ڲ����㣬��׼ȷ��������
u16 INA226_GET_CAL_REG(u8 addr);		//��ȡУ׼ֵ
u8 INA226_AlertAddr(void);  //�����ñ���������
// ģ��ײ�ʵ�ֲ��� -END-

// �û�����
void INA226_Init(void); // ģ���ʼ������
void GetVoltage(float *Voltage); //��ȡ���ߵ�ѹ
void Get_Shunt_voltage(float *Current);	//��ȡ��������
void Get_Shunt_Current(float *Current); //��ȡ������ѹ
void get_power(void);						////��ȡ����= ���ߵ�ѹ * ��������
//ʹ�÷���ʾ����
//    				short Voltage;
//    				float Current;
//    				float powerVal=0.0;
//            Voltage = INA226_GetVoltage(WRITE_ADDR) * 1.251f;  //��ѹֵ
//            Current = INA226_GetShunt_Current(WRITE_ADDR)* 5.9f; //��ȡ����
//            powerVal = Value * Current; //��ȡ����= ���ߵ�ѹ * ����
// �û����� -END-

#endif

