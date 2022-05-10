#include "stm8_hd44780.h"
#include "stm8s.h"
#include "milis.h"

#include "stm8s_gpio.h"
#include "stm8s_tim2.h"
#include "swspi.h"


#define _ISOC99_SOURCE
#define _GNU_SOURCE

#define LED_PORT GPIOC
#define LED_PIN  GPIO_PIN_5
#define LED_HIGH   GPIO_WriteHigh(LED_PORT, LED_PIN)
#define LED_LOW  GPIO_WriteLow(LED_PORT, LED_PIN)
#define LED_TOGG GPIO_WriteReverse(LED_PORT, LED_PIN)

#define BTN_PORT GPIOE
#define BTN_PIN  GPIO_PIN_4

#define BTN_PUSH (GPIO_ReadInputPin(BTN_PORT, BTN_PIN)==RESET) 


void setup(void)
{
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);      // taktovani MCU na 16MHz
    GPIO_Init(LED_PORT, LED_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
    GPIO_Init(GPIOD, GPIO_PIN_4, GPIO_MODE_OUT_PP_LOW_SLOW);
    init_milis();
}

int a=1000;
uint16_t b=20;
int32_t ted=0;

int main(void){

    setup();

    TIM2_TimeBaseInit(TIM2_PRESCALER_16,20000);
    TIM2_OC1Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE,1000,TIM2_OCPOLARITY_HIGH);
    
    TIM2_OC1PreloadConfig(ENABLE);
    TIM2_Cmd(ENABLE);

    while (1) {
    
        if (BTN_PUSH &&(milis()-ted>=100)) {
            ted=milis();
            TIM2_SetCompare1(a);
            a += b;
        }
        if(a>=2000||a<=1000){b=b*-1;}
    }
}

/*-------------------------------  Assert -----------------------------------*/
#include "__assert__.h"
