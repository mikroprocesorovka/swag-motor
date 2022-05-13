#include "stm8s.h"
#include "stm8s_gpio.h"
#include "stm8s_tim2.h"

#define R1_PORT GPIOF
#define R1_PIN  GPIO_PIN_4
#define R2_PORT GPIOF
#define R2_PIN  GPIO_PIN_5
#define R3_PORT GPIOF
#define R3_PIN  GPIO_PIN_6
#define R4_PORT GPIOF
#define R4_PIN  GPIO_PIN_7

void setup(void)
{
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);      // taktovani MCU na 16MHz
    GPIO_Init(GPIOD, GPIO_PIN_4, GPIO_MODE_OUT_PP_LOW_SLOW); //inicializace pinu s timerem
    GPIO_Init (GPIOF,GPIO_PIN_4,GPIO_MODE_IN_PU_NO_IT); //inicializace pinů pro tlačítka
    GPIO_Init (GPIOF,GPIO_PIN_5,GPIO_MODE_IN_PU_NO_IT);
    GPIO_Init (GPIOF,GPIO_PIN_6,GPIO_MODE_IN_PU_NO_IT);
    GPIO_Init (GPIOF,GPIO_PIN_7,GPIO_MODE_IN_PU_NO_IT);
    init_milis();
}

int a=1000; //aktuální šířka pulzu (počáteční nastavena na 1 ms)
uint8_t tlacitko1=0; //stavy tlačítek
uint8_t tlacitko2=0;
uint8_t tlacitko3=0;
uint8_t tlacitko4=0;

int main(void){

    setup();

    //nastavení timeru
    TIM2_TimeBaseInit(TIM2_PRESCALER_16,20000); //nastavení PWM periody na 20 ms
    TIM2_OC1Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE,1000,TIM2_OCPOLARITY_HIGH);//inicializace timeru
    TIM2_OC1PreloadConfig(ENABLE);
    TIM2_Cmd(ENABLE);

    while (1) {
    
        if ((GPIO_ReadInputPin(R1_PORT,R1_PIN)==RESET)&&tlacitko1==0&&a<=2000) { //sledování zmáčknutí tlačítka
            a += 30;
            if (a>2000){ //zamezení překročení krajní hodnoty
                a=2000;
            }
            TIM2_SetCompare1(a);
            tlacitko1 = 1;
        }
        if ((GPIO_ReadInputPin(R1_PORT,R1_PIN)!=RESET)&&tlacitko1==1) {
            tlacitko1 = 0;
        }

        
        if ((GPIO_ReadInputPin(R2_PORT,R2_PIN)==RESET)&&tlacitko2==0&&a>=1000) {
            a = a-30;
            if (a<1000){
                a=1000;
            }
            TIM2_SetCompare1(a);
            tlacitko2 = 1;
        }
        if ((GPIO_ReadInputPin(R2_PORT,R2_PIN)!=RESET)&&tlacitko2==1) {
            tlacitko2 = 0;
        }

        if ((GPIO_ReadInputPin(R3_PORT,R3_PIN)==RESET)&&tlacitko3==0&&a<=2000) {
            a += 90;
            if (a>2000){
                a=2000;
            }
            TIM2_SetCompare1(a);
            tlacitko3 = 1;
        }
        if ((GPIO_ReadInputPin(R3_PORT,R3_PIN)!=RESET)&&tlacitko3==1) {
            tlacitko3 = 0;
        }

        if ((GPIO_ReadInputPin(R4_PORT,R4_PIN)==RESET)&&tlacitko4==0&&a>=1000) {
            a = a-90;
            if (a<1000){
                a=1000;
            }
            TIM2_SetCompare1(a);
            tlacitko4 = 1;
        }
        if ((GPIO_ReadInputPin(R4_PORT,R4_PIN)!=RESET)&&tlacitko4==1) {
            tlacitko4 = 0;
        }
    }


}

/*-------------------------------  Assert -----------------------------------*/
#include "__assert__.h"
