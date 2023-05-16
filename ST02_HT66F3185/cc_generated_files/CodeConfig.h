/**
  ******************************************************************************
  * @file CodeConfig.h
  * @ brief CodeConfig setting file.
  * @author Holtek Semiconductor Inc.
  * @version V1.0.0
  * @date 2020-10-24
  ******************************************************************************
  * @attention
  *
  * Firmware Disclaimer Information
  *
  * 1. The customer hereby acknowledges and agrees that the program technical documentation, including the
  *    code, which is supplied by Holtek Semiconductor Inc., (hereinafter referred to as "HOLTEK") is the
  *    proprietary and confidential intellectual property of HOLTEK, and is protected by copyright law and
  *    other intellectual property laws.
  *
  * 2. The customer hereby acknowledges and agrees that the program technical documentation, including the
  *    code, is confidential information belonging to HOLTEK, and must not be disclosed to any third parties
  *    other than HOLTEK and the customer.
  *
  * 3. The program technical documentation, including the code, is provided "as is" and for customer reference
  *    only. After delivery by HOLTEK, the customer shall use the program technical documentation, including
  *    the code, at their own risk. HOLTEK disclaims any expressed, implied or statutory warranties, including
  *    the warranties of merchantability, satisfactory quality and fitness for a particular purpose.
  *
  * <h2><center>Copyright (C) Holtek Semiconductor Inc. All rights reserved</center></h2>
  ************************************************************************************************************/

#ifndef __CodeConfig_H__
#define __CodeConfig_H__ 1

#include "../SW_Lib/HT8_MCU_IP_SEL.h"
#include "../SW_Lib/HT8_Type.h"



void System_Init();
void System_Setting();
void Main_Flow(vu8 model);
void Light_Blinking(vu8 ststus);
void CharStrategy(vu8 status);
vu16 Average_Matrix(vu16 *matrix);
vu8 Model_Switching(vu16 ACin_ADC,vu16 BATCur_ADC,vu16 dcOVP_ADC,vu16 chgDC_ADC);
bool ACIN_Debounce(vu16 acin_adc);
bool NOBAT_Debounce(vu16 bat_adc);
vu16 GetaveADC(vu8 source);
vu8 Minute_Count(vu8 ststus);


#define ACOn _pc0 = 0
#define ACOff _pc0 = 1
#define GreenON _pa3 = 1
#define GreenOFF _pa3 = 0
#define RedON _pb6 = 1
#define RedOFF _pb6 = 0
#define OrangeON {_pa3 = 1; _pb6 = 1;}
#define OrangeOFF {_pa3 = 0;_pb6 = 0;}
#define TEST_SW _pc1
#define CHG_ON _pb5 = 0
#define CHG_OFF _pb5 = 1
#define V_BAT _pb3
#define Vo _pa7
#define V_CUR _pa6
#define V_chg _pb0
//#define PWM1_OFF _pb5 = 0
//#define PWM1_ON _pb5 = 1
#define PWM_OFF _pb4 = 0
#define PWM_ON _pb4 = 1
//#define LED1_ON _pa7 = 1
//#define LED1_OFF _pa7 = 0
//#define LED2_ON _pa5 = 1
//#define LED2_OFF _pa5 = 0

//#define ST03 1

#define	DELAY_CNT	4000


#endif
