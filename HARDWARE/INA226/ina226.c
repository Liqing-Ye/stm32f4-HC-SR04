#include "ina226.h"

INA226 ina226_data;

void INA226_Init(void)
{
	IIC_Init();
	INA226_SendData(WRITE_ADDR,Config_Reg,0x8000);	//��������
	
//	INA226_SendData(WRITE_ADDR,Config_Reg,0x484f);	//����ת��ʱ��204us,��ƽ��ֵ����128������ʱ��Ϊ204*128������ģʽΪ��������������ģʽ
  INA226_SendData(WRITE_ADDR,Config_Reg,0x4527);	 //16��ƽ��,1.1ms,1.1ms,��������������ѹ�����ߵ�ѹ
	INA226_SendData(WRITE_ADDR,Calib_Reg,CAL);	//���÷ֱ���
//  INA226_SendData(INA226_ADDR1,CAL_REG,0x0012);//���÷�����ѹת����ת������	
	INA226_Get_ID(WRITE_ADDR);					//��ȡina226��id
}

//���üĴ���ָ��
void INA226_SetRegPointer(u8 addr,u8 reg)
{
	IIC_Start();

	IIC_Send_Byte(addr);
	IIC_Wait_Ack();

	IIC_Send_Byte(reg);
	IIC_Wait_Ack();

	IIC_Stop();
}

//����,д������
void INA226_SendData(u8 addr,u8 reg,u16 data)
{
	u8 temp=0;
	IIC_Start();

	IIC_Send_Byte(addr);
	IIC_Wait_Ack();

	IIC_Send_Byte(reg);
	IIC_Wait_Ack();
	
	temp = (u8)(data>>8);
	IIC_Send_Byte(temp);
	IIC_Wait_Ack();

	temp = (u8)(data&0x00FF);
	IIC_Send_Byte(temp);
	IIC_Wait_Ack();
	
	IIC_Stop();
}

//��ȡ����
u16 INA226_ReadData(u8 addr)
{
	u16 temp=0;
	IIC_Start();

	IIC_Send_Byte(addr+1);
	IIC_Wait_Ack();
	
	temp = IIC_Read_Byte(1);
	temp<<=8;	
	temp |= IIC_Read_Byte(0);
	
	IIC_Stop();
	return temp;
}
//1mA/bit
u16 INA226_GetShunt_Current(u8 addr)
{
	u16 temp=0;	
	INA226_SetRegPointer(addr,Current_Reg);
	temp = INA226_ReadData(addr);
	if(temp&0x8000)	temp = ~(temp - 1);	
	return temp;
}

//��ȡid
void INA226_Get_ID(u8 addr)
{
	u32 temp=0;
	INA226_SetRegPointer(addr,ID_Reg);
	temp = INA226_ReadData(addr);
	ina226_data.ina226_id = temp;
}

//��ȡУ׼ֵ
u16 INA226_GET_CAL_REG(u8 addr)
{	
	u32 temp=0;
	INA226_SetRegPointer(addr,Calib_Reg);
	temp = INA226_ReadData(addr);
	return (u16)temp;
}

//1.25mV/bit
u16 INA226_GetVoltage(u8 addr)
{
	u32 temp = 0;
	INA226_SetRegPointer(addr,Bus_V_Reg);
	temp = INA226_ReadData(addr);
	return (u16)temp;	
}

//2.5uV/bit
u16 INA226_GetShuntVoltage(u8 addr)
{
	int16_t temp = 0;
	INA226_SetRegPointer(addr,Shunt_V_Reg);
	temp = INA226_ReadData(addr);
	if(temp&0x8000)	temp = ~(temp - 1);	
	return (u16)temp;	
}

//��ȡ��ѹ
void GetVoltage(float *Voltage)//mV
{
	*Voltage = INA226_GetVoltage(WRITE_ADDR)*Voltage_LSB;
}

//��ȡ������ѹ
void Get_Shunt_voltage(float *Voltage)//uV
{
	*Voltage = (INA226_GetShuntVoltage(WRITE_ADDR)*INA226_VAL_LSB);//��������������������뽫�����Ϊ2.5
}

//��ȡ����
void Get_Shunt_Current(float *Current)//mA
{
	*Current = (INA226_GetShunt_Current(WRITE_ADDR)* CURRENT_LSB);
}

//��ȡ����= ���ߵ�ѹ * ����
void get_power()//W
{
	GetVoltage(&ina226_data.voltageVal);			//mV
	Get_Shunt_voltage(&ina226_data.Shunt_voltage);	//uV
	Get_Shunt_Current(&ina226_data.Shunt_Current);	//mA
	Get_Power(&ina226_data.Power);
	ina226_data.Power_Val = ina226_data.voltageVal*0.001f * ina226_data.Shunt_Current*0.001f; 	//mV*mA
}

//��ȡ����װ��ֵ,ina226�ڲ�����ĵĹ��ʣ�����δ��У׼���ʲ�����

u16 INA226_Get_Power(u8 addr)
{
	int16_t temp=0;
	INA226_SetRegPointer(addr,Power_Reg);
	temp = INA226_ReadData(addr);
	return (u16)temp;
}

//��ȡ����,ina226�ڲ����㣬��׼ȷ��������
void Get_Power(float *Power)//W
{
	*Power = (INA226_Get_Power(WRITE_ADDR)*POWER_LSB);
}

//�����ñ���������
u8 INA226_AlertAddr(void)
{
	u8 temp;
	IIC_Start();

	IIC_Send_Byte(Alert_Reg);
	IIC_Wait_Ack();
	
	temp = IIC_Read_Byte(1);
	
	IIC_Stop();
	return temp;
}


