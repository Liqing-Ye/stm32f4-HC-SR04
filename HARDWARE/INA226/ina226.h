#ifndef __INA226_H
#define __INA226_H
#include "sys.h"
#include "myiic.h"
#include "delay.h"

// ---模块接线---
// VCC 3.3V/5V
// GND GND
// SCL PB8 （时钟线）
// SDA PB9 （数据线）
// ALE 报警引脚(未使用报警功能可不接)
// -------------

#define READ_ADDR                  0x81	 //A1=GND，A2=GND // R=1, W=0
#define WRITE_ADDR                 0x80

#define Config_Reg                 0x00 // 配置寄存器  // 可配置
#define Shunt_V_Reg                0x01 // 分流电压寄存器
#define Bus_V_Reg                  0x02 // 总线电压寄存器
#define Power_Reg                  0x03 // 功率寄存器
#define Current_Reg                0x04 // 电流寄存器
#define Calib_Reg                  0x05 // 校准寄存器  // 可配置
#define Mask_En_Reg                0x06 // 屏蔽/使能寄存器  // 可配置
#define Alert_Reg                  0x07 // 警报限制寄存器 // 可配置
#define Man_ID_Reg                 0xFE  //0x5449 // 制造商 ID 注册
#define ID_Reg                     0xFF  //0x2260 // 包含唯一的芯片标识号

//定义配置数据
#define INA226_VAL_LSB						 2.5f	//分流电压 LSB 2.5uV
#define Voltage_LSB		  					 1.25f   //总线电压 LSB 1.25mV
#define CURRENT_LSB 	 						 1.0f 	//电流LSB 1mA
#define POWER_LSB       					 25*CURRENT_LSB
#define CAL             					 456     //0.00512/(Current_LSB*R_SHUNT) = 470  //电流偏大改小

typedef struct
{
	float voltageVal;			//mV
	float Shunt_voltage;		//uV
	float Shunt_Current;		//mA
	float Power_Val;				//功率
	float Power;				//功率mW
	u32   ina226_id;
}INA226;

extern INA226 ina226_data;

// 模块底层实现部分
void INA226_SetRegPointer(u8 addr,u8 reg);
void INA226_SendData(u8 addr,u8 reg,u16 data);

u16 INA226_ReadData(u8 addr);
void INA226_Get_ID(u8 addr);			
u16 INA226_GetVoltage( u8 addr);		//获取总线电压装载值
u16 INA226_GetShunt_Current(u8 addr);	//获取分流电流装载值
u16 INA226_GetShuntVoltage(u8 addr);	//分流电压装载值
u16 INA226_Get_Power(u8 addr);		//获取功率装载值，不使用
void Get_Power(float *Power);     //获取功率,ina226内部计算，不准确，不采用
u16 INA226_GET_CAL_REG(u8 addr);		//获取校准值
u8 INA226_AlertAddr(void);  //不设置报警，舍弃
// 模块底层实现部分 -END-

// 用户函数
void INA226_Init(void); // 模块初始化函数
void GetVoltage(float *Voltage); //获取总线电压
void Get_Shunt_voltage(float *Current);	//获取分流电流
void Get_Shunt_Current(float *Current); //获取分流电压
void get_power(void);						////获取功率= 总线电压 * 分流电流
//使用方法示例：
//    				short Voltage;
//    				float Current;
//    				float powerVal=0.0;
//            Voltage = INA226_GetVoltage(WRITE_ADDR) * 1.251f;  //电压值
//            Current = INA226_GetShunt_Current(WRITE_ADDR)* 5.9f; //获取电流
//            powerVal = Value * Current; //获取功率= 总线电压 * 电流
// 用户函数 -END-

#endif

