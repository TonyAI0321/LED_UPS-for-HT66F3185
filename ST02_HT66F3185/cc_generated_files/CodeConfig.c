/**
  ******************************************************************************
  * @file CodeConfig.c
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

#include "CodeConfig.h"

bool Time_f = FALSE;
vu8 Model_Status = 0;
vu8 Pre30mins_Count=0;
extern bool TestSW_f;
extern bool ADIN_f;
extern bool BAT_f;
extern bool FAULT_f;
extern bool TimeCount_f;
extern bool IsACin;
extern bool NoBAT_f;
extern bool IsEmergency_f;
bool TimeCheck_f;
bool BatCheck_f=FALSE;
bool Buffer_f=FALSE;
//vu16 Charg[4] = {0,0,0,0};
vu16 ACin[4] = {0,0,0,0};
vu16 BCur[4] = {0,0,0,0};
vu16 DCOVP[4] = {0,0,0,0};
vu16 vBAT[4] = {0,0,0,0};
vu16 minuteCount=0;
//u8 Count = 0;
u8 ACin_Count=0;
u8 BCur_Count=0;
u8 DCOVP_Count=0;
u8 vBAT_Count=0;
//extern vb1 START_f;

typedef enum
{
	Idel_Model = 0,
	Cgarge_Model,
	Test_Model,
	Emergeny_Model,
	ChargeFault_Model,
	Without_BAT_Model,
	Buffer_Mode
}vStatus;
vStatus status = Idel_Model;

typedef enum 
{
	Red = 0,
	Green,
	Orenge,
	none,
	Only_Red,
	Only_Green,
	Only_Orenge
}Light;

typedef enum
{
	Pre30mins=1,
	Charging,
	Alram,
	Fulled,
	None
}Bstatus;

typedef enum
{
	ACin_ADC=1,//AN0
	BCur_ADC,//AN5
	DCOVP_ADC,//AN6
	vBAT_ADC//AN7
}SelADC;

typedef enum
{
	MinuteOFF=1,
	MinuteON=2
}Minute;

//typedef enum
//{	
//}BatStatus;

void System_Init()
{	
	SysClock_Init();
	GPIO_Init();
	ADC_Init();
	TimeBase0_Init();
	TimeBase1_Init();
//end System Init
}

void System_Setting()
{
//Begin System Setting
	EMI_ENABLE();
    
    //ADC_SelectChannel(ADC_CH7);
    ADC_CLEAR_ISR_FLAG();
    //ADC_ISR_ENABLE();
    ADC_ENABLE();
	TB0_CLEAR_FLAG();
	TB0_ISR_ENABLE();
	TB0_ENABLE();
	TB1_CLEAR_FLAG();
	TB1_ISR_ENABLE();
	TB1_ENABLE();
//end System Setting
}

void Light_Blinking(vu8 ststus)
{
	Light STATUS=(Light)ststus;
	//vu8 STATUS = ststus;
	switch(STATUS)
    {
    	case Red: //Red light
    	{
    		if(Time_f) RedON;
    		else       RedOFF;
    		GreenOFF;
    		break;
    	}
    	case Green: //Green light
    	{
    		if(Time_f) GreenON;
    		else       GreenOFF;
    		RedOFF;
    		break;
    	}
    	case Orenge: //Orenge light
    	{
    		if(Time_f) OrangeON
    		else       OrangeOFF
    		break;
    	}
    	case none://None
    	{
    		OrangeOFF
    		break;
    	}
    	case Only_Red:
    	{
    		RedON;
    		GreenOFF;
    		break;
    	}
    	case Only_Green:
    	{
    		GreenON;
    		RedOFF;
    		break;
    	}
    	case Only_Orenge:
    	{
    		OrangeON;
    		break;
    	}
    }
}

void Main_Flow(vu8 model)
{
	//vu8 MODEL = model;
	vStatus stutas=(vStatus)model;
	switch(stutas)
	{
		case Idel_Model://Idel_Mode
		{
//			OrangeOFF
//			//Light_Blinking(Green);
//			AC_OFF;
//			Emergency_OFF;
            PWM_OFF;
            ACOn;
            CHG_OFF;            
            Light_Blinking(Only_Orenge);
			break;
		}
		case Buffer_Mode:
		{
			PWM_ON;
			GCC_DELAY(100);
			PWM_OFF;
			GCC_DELAY(10);
			PWM_ON;
			Buffer_f=TRUE;
			break;
		}
		case Cgarge_Model://Cgarge_Mode
		{
//			OrangeOFF
//			GreenON;
//			AC_ON;
//			Emergency_OFF;
            PWM_ON;
            ACOn;
            CHG_ON;
            Light_Blinking(Green);
            //GreenON;
            //GreenOFF;
            //RedON;
			break;
		}
		case Test_Model://Test_Mode
		{
//			OrangeOFF
//			RedON;
//			AC_OFF;
//			Emergency_ON;
            CHG_OFF;
            PWM_ON;
            Light_Blinking(Red);//Red
			break;
		}
		case Emergeny_Model://Emergeny_Mode
		{
//			OrangeON
//			AC_OFF;
//			Emergency_ON;
            Light_Blinking(Orenge);
	     	break;
		}
		case ChargeFault_Model://ChargeFault_Modes
		{
//			OrangeOFF
//			Light_Blinking(Red);
//			//AC_OFF;
//			Emergency_OFF;
			break;
		}
		case Without_BAT_Model://Without_BAT_Mode
		{
//			Light_Blinking(Orenge);
//			AC_OFF;
//			Emergency_OFF;            
            Light_Blinking(Only_Red);
			break;
		}		
	}
}

vu8 Model_Switching(vu16 ACin_ADC,vu16 BATCur_ADC,vu16 dcOVP_ADC,vu16 chgDC_ADC)
{
//	vu16 AC_ADC = ac_adc;
//	vu16 BAT_ADC = bat_adc;
	//bool Is_AC_f;
	//bool NOBAT_f;
	//vStatus status = Idel_Model;
	switch(status)
	{
		case Idel_Model://Idel_Mode
		{
//			Is_AC_f = ACIN_Debounce(AC_ADC);
//			NOBAT_f = NOBAT_Debounce(BAT_ADC);
//			if(BAT_f){Model_Status = 5; break;}
//		    else if(FAULT_f) {Model_Status = 4; break;}
//		    else if(Is_AC_f) {Model_Status = 1; break;}
//		    else {return Idel_Model; break;}
            if(NoBAT_f) {status=Without_BAT_Model;}
            else if(IsACin) {status=Cgarge_Model;}
            else status=Idel_Model; 
            //Model_Status = 1;
            //return status;
            break;
		}
		case Buffer_Mode:
		{
			if(Buffer_f)
			{
				status=Cgarge_Model;
				Buffer_f=FALSE;
				break;
			}
			status=Buffer_Mode;			
			break;
		}
		case Cgarge_Model://Cgarge_Mode
		{
//			Is_AC_f = ACIN_Debounce(AC_ADC);
//			if(!Is_AC_f) {Model_Status = 3; break;}
//			else if(FAULT_f)  {Model_Status = 4; break;}
//			else if(TestSW_f) {Model_Status = 2; break;}
//			else if(BAT_f) {Model_Status = 5; break;}
//			else {return Cgarge_Model; break;}
            if(IsEmergency_f) {status=Emergeny_Model; break;}
            else if(TestSW_f) {status=Test_Model; break;}
             
            status=Cgarge_Model;            
            break;
		}
		case Test_Model://Test_Mode
		{
			/* TEST Buttom放開後返回Idel Mode*/
		    if(!TestSW_f) 
		    {
		    	status=Idel_Model;
		    	//Model_Status = 0;
		    	break;
		    }
		    status=Test_Model;			        
			break;
		}
		case Emergeny_Model://Emergeny_Modes
		{
//			Is_AC_f = ACIN_Debounce(AC_ADC);
//			if(Is_AC_f) {Model_Status = 0;break;}
//			return Emergeny_Model;
            if(!IsEmergency_f) {status=Idel_Model; break;}
            status=Emergeny_Model;
			break;
		}
		case ChargeFault_Model://ChargeFault_Modes
		{
//			if(!FAULT_f) {Model_Status = 0;break;}
//			return ChargeFault_Model;
			break;
		}
		case Without_BAT_Model://Without_BAT_Mode
		{
//			if(!BAT_f) {Model_Status = 0;break;}
//			return Without_BAT_Model;
            if(!NoBAT_f)
            {
            	status=Idel_Model;
            	break;
            }
            status=Without_BAT_Model; 
			break;
		}
	}
	return (vu8)status;
}

vu16 Average_Matrix(vu16 *matrix)
{
	vu16 result = 0;
	u8 k=0;
	u8 qq=0;
	for(k=0;k<4;k++)
	{
		result += *(matrix+qq++);
	}
	return (result>>2);
}

bool ACIN_Debounce(vu16 acin_adc)
{
	vu16 ACIN_ADC = acin_adc; //備用做ADC電壓數值判斷
	if(ADIN_f) return TRUE;
	else       return FALSE;
}

bool NOBAT_Debounce(vu16 bat_adc)
{
	vu16 BAT_ADC = bat_adc;//備用做ADC電壓判斷
	if(BAT_f) return TRUE;
	else      return FALSE;
}

void CharStrategy(vu8 status)
{
	Bstatus chrStatus=(Bstatus)status; 
	switch(chrStatus)
	{
		case Pre30mins:
		{
			Pre30mins_Count=GetaveADC((vu8)MinuteON);
			if(Pre30mins_Count>=30)
			{
				Pre30mins_Count=0;
				/*
				 do something check
				*/
			}
			break;
		}
		case Charging:
		{
			break;
		}
		case Alram:
		{
			break;
		}
		case Fulled:
		{
			break;
		}
		case None:
		{
			GetaveADC((vu8)MinuteOFF);
			Pre30mins_Count=0;
			break;
		}
	}
}

vu16 GetaveADC(vu8 source)
{
	//vu16 ADC_Value = 0;
	vu16 ACin_Value=0;
	vu16 BCur_Value=0;
	vu16 DCOVP_Value=0;
	vu16 vBAT_Value=0;
	SelADC SelStatus=(SelADC)source;
	switch(SelStatus)
	{
		case ACin_ADC:
		{
			ACin[ACin_Count++] = ADC_GetChannelValue(ADC_CH0);
			if(ACin_Count>=4) ACin_Count=0;
			ACin_Value=Average_Matrix(ACin);
			return  ACin_Value;
			break;
		}
		case BCur_ADC:
		{
			BCur[BCur_Count++] = ADC_GetChannelValue(ADC_CH5);
			if(BCur_Count>=4) BCur_Count=0;
			BCur_Value=Average_Matrix(BCur);
			return  BCur_Value;
			break;
		}
		case DCOVP_ADC:
		{
			DCOVP[DCOVP_Count++] = ADC_GetChannelValue(ADC_CH6);
			if(DCOVP_Count>=4) DCOVP_Count=0;
			DCOVP_Value=Average_Matrix(DCOVP);
			return  DCOVP_Value;
			break;
		}
		case vBAT_ADC:
		{
			vBAT[vBAT_Count++] = ADC_GetChannelValue(ADC_CH7);
		    if(vBAT_Count>=4) vBAT_Count=0;
		    vBAT_Value=Average_Matrix(vBAT);
			return  vBAT_Value;
			break;
		}
	}	
}

vu8 Minute_Count(vu8 ststus)
{
	Minute minute=(Minute)ststus;
	vu8 result=0;
	switch(minute)
	{
		case MinuteON:
		{
			if((TimeCheck_f!=TimeCount_f) && (minuteCount++>=30000))
			{
				minuteCount=0;
				result=1;
				return result;
			}
			break;
		}
		case MinuteOFF:
		{
			result=0;
			minuteCount=0;
			return result;
			break;
		} 
	}
	TimeCheck_f=TimeCount_f;
	return result;	
}