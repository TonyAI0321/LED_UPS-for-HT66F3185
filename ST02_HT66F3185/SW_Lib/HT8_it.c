/**
  ******************************************************************************
  * @file HT8_it.c
  * @brief This file provides all the interrupt firmware functions.
  * @author Holtek Semiconductor Inc.
  * @version V1.0.0
  * @date 2020-06-15
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


#include "HT8_it.h"
#include "../cc_generated_files/CodeConfig.h"

//extern vu16 g_nADC_ISR_Value;
//extern vu16 BAT_ADC;
//extern vu8  g_nADC_Finish;
extern bool Time_f;
vu16 TB0_Count = 0;
vu16 Inial_Count=0;
vu8 TestSW_Count = 0;
vu8 ACIN_Count = 0;
vu8 ACIN2_Count = 0;
vu8 FAULT_Count = 0;
vu8 FAULT1_Count = 0;
vu8 BAT_Count = 0;
vu8 ADCTRAN_Count = 0;
vu8 IsACin_Count=0; 
extern vu16 chgDC_ADC;
extern vu16 ACin_ADC;
extern vu16 BATCur_ADC;
extern vu16 dcOVP_ADC;
extern bool BatCheck_f;
vu16 ACin_ADC_temp=0;
//vu8 START_Count = 0;
bool TestSW_f = FALSE;
bool ADIN_f = FALSE;
bool BAT_f = FALSE;
bool FAULT_f = FALSE;
bool ADCTRAN_f = FALSE;
bool TimeCount_f=FALSE;
bool IsACin=FALSE;
bool Inial_f=FALSE;
bool NoBAT_f=FALSE;
bool IsEmergency_f=FALSE;

typedef enum
{
	BatConnect_status=1,
	NoBAT_status,
	IsBatConnect_status,
	NoACin_status,
	IsACin_status,
	IsEmergency_status,
	CheckBAT_status,
	Watting_status
}UPS_Status;
UPS_Status ups_status=IsBatConnect_status;
//vu8 Currently_status=(vu8)Watting_status;
//vb1 START_f = FALSE;
/**
  * @brief external Interruption 0 routine.
  * @par Parameters:
  * None
  * @retval
  * None
  */
void __attribute((interrupt(0x04))) INT0_ISR(void)
{
	/* user define */
}

/**
  * @brief compare Interruption routine.
  * @par Parameters:
  * None
  * @retval
  * None
  */
void __attribute((interrupt(0x08))) COMP_ISR(void)
{
	/* user define */
}

/**
  * @brief STM Interruption routine(Multi-Function Interrupt 0).
  * @par Parameters:
  * None
  * @retval
  * None
  */
void __attribute((interrupt(0x0C))) STM_ISR(void)
{	
	if (_stmaf == 1)
	{
		_stmaf = 0;
		/* user define */
	}
	if (_stmpf == 1)
	{
		_stmpf = 0;
		/* user define */
	}	
}

/**
  * @brief PTM or CTM Interruption routine(Multi-Function Interrupt 1).
  * @par Parameters:
  * None
  * @retval
  * None
  */
void __attribute((interrupt(0x10))) PTM_CTM_ISR(void)
{	
	if (_ptmaf == 1)
	{
		_ptmaf = 0;	
		/* user define */
	}
	if (_ptmpf == 1)
	{
		_ptmpf = 0;	
		/* user define */
	}
	
	if (_ctmaf == 1)
	{
		_ctmaf = 0;
		/* user define */
	}
	if (_ctmpf == 1)
	{
		_ctmpf = 0;
		/* user define */
	}
}

/**
  * @brief LVD or EEPROM Interruption routine(Multi-Function Interrupt 2).
  * @par Parameters:
  * None
  * @retval
  * None
  */
void __attribute((interrupt(0x14))) LVD_EEPROM_ISR(void)
{
	if (_lvf == 1)
	{
		_lvf = 0;
		/* user define */
	}
	if (_def == 1)
	{
		_def = 0;
		/* user define */
	}
}

/**
  * @brief ADC Interruption routine.
  * @par Parameters:
  * None
  * @retval
  * None
  */
void __attribute((interrupt(0x18))) ADC_ISR(void)
{
	//g_nADC_ISR_Value = ADC_READ_VALUE();
//	g_nADC_Finish = 1;
	GCC_DELAY(1);
}


/**
  * @brief timebase0 Interruption routine.
  * @par Parameters:
  * None
  * @retval
  * None
  * 2ms
  */
void __attribute((interrupt(0x1C))) TB0_ISR(void)
{
	TB0_Count++;
	if(TB0_Count>=500)
	{
		TB0_Count=0;
		Time_f=~Time_f;
	}
	
	
//	START_Count++;
//	if(START_Count>100)
//	{
//		START_Count = 0;
//		START_f = TRUE;
//	}
	
	if(!TEST_SW)
	{
		TestSW_Count++;
		if(TestSW_Count>10)
		{
			TestSW_f = TRUE;
		}
	}
	else
	{
		TestSW_Count = 0;
		TestSW_f = FALSE;
	}
	
//	if(g_nADC_ISR_Value>500)
//	{
//		ACIN2_Count = 0;
//		ACIN_Count++;
//		if(ACIN_Count>10)
//		{
//			ADIN_f = TRUE;
//			ACIN_Count = 0;
//		}
//	}
//	else
//	{
//		ACIN2_Count++;
//		ACIN_Count = 0;
//		if(ACIN2_Count>10)
//		{
//			ADIN_f = FALSE;
//		}
//	}
	
	
//	if(BAT_ADC<1000 || BAT_ADC>4000)
//	{
//		BAT_Count++;
//		if(BAT_Count>10)
//		{
//			BAT_Count = 0;
//			BAT_f = TRUE;
//		}
//	}
//	else
//	{
//		BAT_Count = 0;
//		BAT_f = FALSE;
//	}
	
//	if(g_nADC_ISR_Value<1300 && g_nADC_ISR_Value>500)
//	{
//		FAULT1_Count = 0;
//		FAULT_Count++;
//		if(FAULT_Count>30)
//		{
//			FAULT_Count = 0;
//			FAULT_f = TRUE;
//		}
//	}
//	else
//	{
//		FAULT_Count = 0;
//		FAULT1_Count++;
//		if(FAULT1_Count>20)
//		{
//			FAULT1_Count = 0;
//			FAULT_f = FALSE;
//		}	
//	}
	
	ADCTRAN_Count++;
	if(ADCTRAN_Count>=2)
	{
		ADCTRAN_Count = 0;
		ADCTRAN_f = ~ADCTRAN_f;
	}
	
/*	_pc0 = ~_pc0;*/
	/* user define */
}


/**
  * @brief timebase1 Interruption routine.
  * @par Parameters:
  * None
  * @retval
  * 2ms
  */
void __attribute((interrupt(0x20))) TB1_ISR(void)
{
	//_pc0 = ~_pc0;
	TimeCount_f=~TimeCount_f;
	
	if(BatCheck_f)
	{
		/*
		do something check after 30min was done
		return a flag for Model_Switching
		*/
		BatCheck_f=FALSE;
	}
	
	switch(ups_status)
	{
		case Watting_status:
		{
			if(ACin_ADC>2000)
			{
				ups_status=IsACin_status;
			}
			//ups_status=Watting_status;
			break;
		} 
		case IsBatConnect_status:
		{
			if(chgDC_ADC>500 && Inial_Count++>100)
			{
				NoBAT_f=FALSE;
				ups_status=Watting_status;
			}
			else
			{
				//Inial_Count=0;
				if(chgDC_ADC<500)
				{
					Inial_Count=0;
				}
				NoBAT_f=TRUE;
				ups_status=IsBatConnect_status;
			}
			
			/*if(chgDC_ADC<500)
			{
				NoBAT_f=TRUE;
				ups_status=IsBatConnect_status;
			}
			else
			{
				NoBAT_f=FALSE;
				ups_status=Watting_status;
			}*/
			break;
		}
		case BatConnect_status:
		{
			break;
		}
		case NoACin_status:
		{
			break;
		}
		case IsACin_status:
		{
			if(ACin_ADC>2000)
			{
				IsACin=TRUE;
				ups_status=IsEmergency_status;
			}
			else
			{
				IsACin=FALSE;
				ups_status=IsEmergency_status;
			}
			break;
		}
		case IsEmergency_status:
		{			
			if(ACin_ADC<2000)
			{
				IsEmergency_f=TRUE;
				ups_status=IsACin_status;
			}
			else
			{
				IsEmergency_f=FALSE;
				ups_status=IsACin_status;
			}
			break;
		}
		case CheckBAT_status:
		{
			
			break;
		}    
	}
	
	/*if(IsACin!=TRUE && ACin_ADC>2000)
	{
		NoBAT_f=TRUE;
		Inial_Count=0;
	}
	else
	{
		NoBAT_f=FALSE;
	}
	
	if(NoBAT_f!=TRUE && Inial_Count++>2000 && Inial_f!=TRUE)
	{
		Inial_f=TRUE;
		ACin_ADC_temp=ACin_ADC;
	}
		
	//ACin_ADC_temp=ACin_ADC;
	if(Inial_f!=FALSE && abs(ACin_ADC-ACin_ADC_temp)>300 && IsACin!=TRUE)
	{
		if(IsACin_Count++>20)
		{
			IsACin=TRUE;
		}	
	}
	*/
	/* user define */
}


/**
  * @brief external Interruption 1 routine.
  * @par Parameters:
  * None
  * @retval
  * None
  */
void __attribute((interrupt(0x24))) INT1_ISR(void)
{
	/* user define */
}

/******************* (C) COPYRIGHT 2019 Holtek Semiconductor Inc *****END OF FILE****/