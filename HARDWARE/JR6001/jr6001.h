#ifndef __JR6001_H
#define __JR6001_H
#include "sys.h"
#include "usart.h"
#include "delay.h"
#include "stm32f4xx_conf.h"

// ---模块接线---
// VCC 5V（3.6-5.2V），工作电流10mA
// GND GND
// RX 异步串口数据输入 (UART 标准串口，3.3TTL电平，波特率9600)
// TX 异步串口数据输出 (UART 标准串口，3.3TTL电平，波特率9600)
// BUSY 播放语音时输出高电平
// SPK+ 接喇叭，不分正负
// SPK- 接喇叭，不分正负
// AD_KEY AD口，接不同参数的电阻有不同的功能，参考电路图。预留给外部增加（最多5个）控制按键使用，音量减小，音量增加，上一首，下一首，播放/暂停。
// DACR 音频右声道输出
// DACL 音频坐声道输出
// -------------

// ---通信机制---
//1、我方作为从机处理，上电默认等待状态，所有播放操作由主机发起。
//2、从机不会主动发起通信，所有通信都是由主机发起
//3、串口是 3.3V 的 TTL 电平，如果主机系统是 5V 电平请在中间串上 1K 电阻。
//4、协议中所有数据均是 ASCII 码。
//5、本芯片的 IO 电平是 3.3V
//指令： A7:00001  例如: A7:00008 指定播放当前存储器下文件名为 00008 的文件
//指令： AF:XX  例如：AF:20 设置音量为 20 级(默认20级)
// -------------


#define BUSY 									GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1)  // PC1   判断模块是否正在播放语音，1是 0否

void JR6001_Init(void); 
void JR6001_Voice(u16); // 播放语音文件“Data.mp3” //u8 musicFile[5]

void JR6001_VolumeSetting(u16); // 播放音量的设置
#endif

