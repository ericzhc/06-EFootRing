/**
  ******************************************************************************
	*文件：Process.h
	*作者：吴新有
	*版本：1.0
	*日期：2016-12-17
	*概要：
	*备注：
	*
  ******************************************************************************  
	*/ 
	
/* 定义防止递归包含的控制宏----------------------------------------------------*/
#ifndef _PROCESS_H
#define _PROCESS_H

	/* 头文件包含 ------------------------------------------------------------------*/
	#include "DataTypeConvertion.h"
	#include "stm32f10x.h"
	#include "TerminalControl.h"
	#include "SpiPort.h"
	#include "LCDdisplay.h"
	#include "SerialPort.h"
	#include "Timer.h"
	#include "IoOut.h"
	#include "Key.h"
	#include "STM32_SysTick.h"
	#include "STM32_ADC.h" 
	#include "stdint.h"
	
	#include "oled.h"
	#include "sqStack.h"
	
//#define USE_SLEEP	
#define USE_OLED
/* 引脚定义--------------------------------------------------------------------*/


#define	USE_PERIPH
#ifdef	USE_PERIPH

	
	//<按键 引脚定义>
	#define KEYNUM1_PORT           GPIOA             //数字按键1号
	#define KEYNUM1_PIN            GPIO_Pin_2
	#define KEYNUM2_PORT           GPIOB            //数字按键2号
	#define KEYNUM2_PIN            GPIO_Pin_0
	#define KEYNUM3_PORT           GPIOA            //按键3
	#define KEYNUM3_PIN            GPIO_Pin_15
	#define KEYNUM4_PORT           GPIOB           //按键4
	#define KEYNUM4_PIN            GPIO_Pin_3	
	#define KEYNUM5_PORT           GPIOB           //按键5
	#define KEYNUM5_PIN            GPIO_Pin_1  	
	#define KEYNUM6_PORT           GPIOB            //按键6
	#define KEYNUM6_PIN            GPIO_Pin_2      
	#define KEYNUM7_PORT           GPIOA            //按键7
	#define KEYNUM7_PIN            GPIO_Pin_11 
	#define KEYNUM8_PORT           GPIOA            //按键8
	#define KEYNUM8_PIN            GPIO_Pin_12
	#define KEYNUM9_PORT           GPIOB             //按键9
	#define KEYNUM9_PIN            GPIO_Pin_10
	#define KEYNUM0_PORT           GPIOB              //按键0
	#define KEYNUM0_PIN            GPIO_Pin_11
	
	#define KEYMODE_PORT           GPIOB              //模式按键
	#define KEYMODE_PIN            GPIO_Pin_12
	#define KEYALARM_PORT           GPIOB              //报警按键
	#define KEYALARM_PIN            GPIO_Pin_13
	#define KEYSHOCK_PORT           GPIOB              //电击按键
	#define KEYSHOCK_PIN            GPIO_Pin_14
	#define KEYDEL_PORT           GPIOA                //退格按键
	#define KEYDEL_PIN            GPIO_Pin_8
	#define KEYCHECK_PORT					GPIOB							//查询本体电量
	#define KEYCHECK_PIN					GPIO_Pin_15
	
	
	//指示灯
	#define LED_PORT              GPIOB
	#define LED_PIN               GPIO_Pin_7
	
	
	//使能电源
	#define POW_EN_PORT              GPIOB
	#define POW_EN_PIN               GPIO_Pin_6
	
	//使能数传模块
	#define YL_EN_PORT           GPIOB                //SETA
	#define YL_EN_PIN            GPIO_Pin_5 
	#define YL_SET_PORT           GPIOB                //SETA
	#define YL_SET_PIN            GPIO_Pin_4 

	

	
	//</按键 引脚定义>
	

	
//</引脚端口定义>
	
//<AD 相关定义>
	/* AD顺序定义--------------------------------------------------------------------*/

	#define	NUM_POWER			   	0										//	电源电压




	//</AD 相关定义>

#endif
	//定时器时间
	#define	TIM2_DELAY_TIME		50
	#define	TIM3_DELAY_TIME		80
	#define	TIM4_DELAY_TIME		200

	/* 静态变量声明 --------------------------------------------------------------------*/
	


	/* 类的声明 --------------------------------------------------------------------*/
	class Process
	{
		public:
						Process();
						~Process();
			void 		runOnTime2(void);							//	运行在定时器TIM2中的函数
			void 		runOnTime3(void);							//	运行在定时器TIM3中的函数
			void 		runOnTime4(void);							//	运行在定时器TIM4中的函数
			void 		openPeriph(void);							//	打开用外设		
		
		private:
		
			u8* OLEDString;                  //显示的字符串
			SqStack *sqStack;                //存放按键数据的栈
			
			u8 *sendData;
			u8 *receiveData;
			u8 *showData;
		


			Timer		         *t2,*t3,*t4;								//	定时器2,定时器3,定时器4			
			SerialPort       *zigbeePort;
			TerminalControl  *zigbeeControl;
		//	LCDdisplay *LCDCtrl;						            //控制液晶屏
		//	SpiPort *lcdPort;									          //和LCD液晶屏通信的SPI类

			//<按键实例声明>

			Key     *keyNum1;
			Key     *keyNum2;
			Key     *keyNum3;
			Key     *keyNum4;
			Key     *keyNum5;
			Key     *keyNum6;
			Key     *keyNum7;
			Key     *keyNum8;
			Key     *keyNum9;
			Key     *keyNum0;
		
		
		


		
			Key   *keyDel;
			Key   *keyMode;
			Key   *keyShock;
			Key   *keyAlarm;
			Key   *keyCheck;
		
			//IO
			IoOut   *Led;
			IoOut   *Pow_EN,*YL_Set,*YL_EN;
			IoOut   *zigbeeReset;
			
			u8 controlData;
			u8 controlModeFlag;  //标识控制模式
			u8 controlStatusFlag;  //标识控制状态
			u8 isFreeMode;
			u8 checkPowerMode;				//查询本体电量
			
			uint16_t	RoomID;						//	接收到的房间ID
			uint16_t	TerminalID;					//	接收到的终端ID
			int Data;
			
			u8 powerValue;   //电压值
			bool isShocking;       //正在电击
			bool isAlarming;        //正在警报
			
			int watchDogTimer;
					
	
			
private:
			void	    initAllData(void);							//	全部数据初始化，包括标志位
			void			initGPIO(void);							  	//	初始化IO
			void	    initADs(void);								//	初始化AD通道
			void	    initUsarts(void);							//	初始化串口
			void	    initTimers(void);							//	初始化定时器		
			void      initOLED(void);                //初始化液晶屏
			
			void    getPowerValue();
			void	  getKeyValue(void);							//	获取按键值
			bool    returnKeyEvent();               //  返回是否有按键
			bool    returnKeyValue();             

			void		dealKeyValue(void);							//	处理按键控制数据

			void 		showOtherSymbol();          //显示OLED字符串
			void    showPowerValue();
			void    showControlMode();          //显示控制模式  接近和定点
			void    showControlStatus();        //显示控制状态  电击和警报
			void    disPage_start();
			void    showTitleName();

			void    showNoPower();
			
			void    updataToZigbee();         //更新发送数据
		
		  void		receiveMainData(void);     //接收本体数据

			void    SYSCLKconfig_STOP(void);   //从停机状态唤醒后需要设置时钟
			void		enable_SWD_disable_Jtag(void);				//	使能SWD，关闭JTAG
			void		testWithUsart(void);						//	通过串口测试数据
			
			
			void 		itoa(int, u8*);
	};
	
#endif 
/*--------------------------------- End of Process.h -----------------------------*/
