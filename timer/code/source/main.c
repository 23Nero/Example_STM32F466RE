#include "./../include/gpio.h"
#include "./../include/uart.h"
#include "./../include/timer.h"
#include "./../include/sysTick.h"
#include "./../include/RCC.h"

int main()
{
  /* Enable clock */
  RCC->AHB1ENR |= (1 << 0);
  RCC->AHB1ENR |= (1 << 2);
  RCC->APB1ENR |= (1 << 17);
  RCC->APB1ENR |= (1 << 0);

  /* Set PA5 as output */
  GPIO_setMode(GPIO_A, 0, ALTERNATE); // General purpose output mode
  GPIO_setAlternateFunction(GPIO_A, 0, AF1);

  // GPIO_setMode(GPIO_A, 0, OUTPUT); // General purpose output mode

  TIM_Config(TIM2, 16000, 1000, TIM_MODE_BASIC);

  TIM2->CCMR1 |= TIM_OCMODE_PWM1;

  TIM2->CCER |= (TIM_CCER_CC1E | TIM_CCER_CC1P); // Enable tim2 ch1 output compare

  // Đặt giá trị so sánh để điều khiển độ sáng của đèn LED (giá trị PWM)
  TIM_SetDutyCycle(TIM2, 1, 500); // Đặt duty cycle 50% cho kênh 1 của TIM2

  // Bắt đầu timer
  TIM_Start(TIM2);
  // configSysTickInt(NULL);

  while (1)
  {

  }
}
