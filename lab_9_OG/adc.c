

//#include "adc.h"
//#include <inc/tm4c123gh6pm.h>
//#include <math.h>
//#include <math.h>
//
//
//void adc_init(void){
//
//    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R3;    //enable ADC 0 module on port D
//    SYSCTL_RCGCADC_R |= 0x1;    //enable clock for ADC
//    GPIO_PORTD_AFSEL_R |= 0x01;     //enable port D pin 0 to work as alternate functions
//    GPIO_PORTD_DEN_R &= 0b11111110; //set pin to input - 0
//    GPIO_PORTD_AMSEL_R |= 0x01;     //disable analog isolation for the pin
//    GPIO_PORTD_ADCCTL_R = 0x00;     //initialize the port trigger source as processor (default)
//    ADC0_ACTSS_R &= ~ADC_ACTSS_ASEN0;   //disable SS0 sample sequencer to configure it
//    ADC0_EMUX_R = ADC_EMUX_EM0_PROCESSOR;   //initialize the ADC trigger source as processor (default)
//    ADC0_SSMUX0_R |= 0x000A;    //set 1st sample to use the AIN10 ADC pin
//    ADC0_SSCTL0_R |= (ADC_SSCTL0_IE0 | ADC_SSCTL0_END0);    //enable raw interrupt status
//    ADC0_SAC_R |= ADC_SAC_AVG_64X;      //enable oversampling to average
//    ADC0_ACTSS_R |= ADC_ACTSS_ASEN0;    //re-enable ADC0 SS0
//}
//
//
//unsigned adc_read(char channel){
//    ADC0_ACTSS_R &= ~ADC_ACTSS_ASEN0;   //disable ADC0SS0 sample sequencer to configure it
//
//    ADC0_SSMUX0_R |= channel;   //set 1st sample to use the channel ADC pin
//
//    ADC0_ACTSS_R |= ADC_ACTSS_ASEN0;    //re-enable ADC0 SS0
//
//    ADC0_PSSI_R=ADC_PSSI_SS0;   //initiate SS0 conversion
//
//    while((ADC0_RIS_R & ADC_RIS_INR0) == 0){}   //wait for ADC conversion to be complete
//
//    ADC0_ISC_R=ADC_ISC_IN0; //clear interrupt
//
//    return ADC0_SSFIFO0_R;
//}
//void adc_polling(void){
//
//    ADC0_PSSI_R=ADC_PSSI_SS0;   //initiate SS0 conversion
//    while((ADC0_RIS_R & ADC_RIS_INR0) == 0){    //wait for ADC conversion to be complete
//        //wait
//    }
//    ADC0_ISC_R = ADC_ISC_IN0;   //clear interrupt
//
//}
//void adc_handler_en(void){
//    //Enable ADC interrupt handler
//    ADC0_ISC_R |= ADC_ISC_IN0;//clear interrupt flags
//    ADC0_IM_R |= ADC_IM_MASK0;  //enable ADC0SS0 interrupt
//    NVIC_EN0_R |= 0x00004000;   //enable interrupt for IRQ 14 set bit 14
//    IntRegister(INT_ADC0SS0, adc_handler_en);  //tell cpu to use ISR handler for ADC0SS0
//    IntMasterEnable();  //enable global interrupts
//}
//
//int adc_average(void){
//        int i = 0;
//        int data = 0;
//        int raw = 0;
//        for(i=0; i<10; i++){
//            int raw_data = adc_read(ADC0_SSMUX0_R); // reads sensor data from bot
//
//            int calibrate = 18010/(pow((raw_data), .824)); // converts raw sensor data to known distances in cm
//            raw = raw+raw_data;
//            data = data+calibrate;
//
//        }
//
//        raw = raw/10;  //raw average for graphing purposes
//        data= data/10;  // average to get a non-changing disance
//        adc_polling();
//        return data;
//}
