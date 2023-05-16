//#include "HT66F3185.h"
#include "cc_generated_files\CodeConfig.h"

//vu16 g_nADC_ISR_Value = 0;	//AD conversion value
vu16 chgDC_ADC = 0;
vu16 ACin_ADC=0;
vu16 BATCur_ADC=0;
vu16 dcOVP_ADC=0;
//vu16 Charg[4] = {0,0,0,0};
//vu16 *P = Charg;
//u8 Count = 0;
//vu8  g_nADC_Finish;		//AD conversion complete flag
vu8 SW_Model = 0;
extern bool ADCTRAN_f;
/*vb1 Test_F;*/

//typedef enum
//{
//	Idel_Mode = 0,
//	Cgarge_Mode,
//	Test_Mode,
//	Emergeny_Modes,
//	ChargeFault_Modes,
//	Without_BAT_Mode
//}Status;


void main()
{
	System_Init();
	System_Setting();
	GCC_DELAY(DELAY_CNT);
	/*Test_F = FALSE;*/
	while(1)
	{
		GCC_CLRWDT();
								
        if(ADCTRAN_f)
        {
        	ACin_ADC=GetaveADC(1);    	
        	GCC_DELAY(100);
        	BATCur_ADC=GetaveADC(2);
        	GCC_DELAY(100);
        	dcOVP_ADC=GetaveADC(3);
        	GCC_DELAY(100);
        	chgDC_ADC=GetaveADC(4);        	
        }
        SW_Model = Model_Switching(ACin_ADC,BATCur_ADC,dcOVP_ADC,chgDC_ADC);
        Main_Flow(SW_Model);
	}
}

