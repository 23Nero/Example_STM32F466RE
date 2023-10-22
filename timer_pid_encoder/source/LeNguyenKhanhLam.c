#include "./../include/LeNguyenKhanhLam.h"

void sysInit(void)
{
    enaleClockModule();
    configGPIO();

    configTim();
    configSysTickInt(NULL);
}

void enaleClockModule(void)
{
    /* Enable clock */
    RCC->AHB1ENR |= (1 << 0);  // Port A
    RCC->AHB1ENR |= (1 << 1);  // Port B
    RCC->AHB1ENR |= (1 << 2);  // Port C
    RCC->APB1ENR |= (1 << 17); // USART2
    RCC->APB1ENR |= (1 << 0);  // TIM2
    RCC->APB1ENR |= (1 << 1);  // TIM3
	  RCC->APB1ENR |= (1 << 2);  // TIM4
    RCC->APB2ENR |= SYSCFGEN;  // Exti
}

void configTim(void)
{
    /* Set timer2 channel 1 - PA0 */
    GPIO_setMode(GPIO_A, 0, ALTERNATE); // General purpose output mode
    GPIO_setAlternateFunction(GPIO_A, 0, AF1);

    TIM_Config(TIM2, PWM_PRESCALER, PWM_PERIOD, TIM_MODE_BASIC);

    TIM_ConfigOutputCompare(TIM2, CHANEL1, TIM_OCMODE1_PWM1);
    TIM_EnableOutputCompare(TIM2, CHANEL1, ACTIVE_HIGH);

    /* Set timer2 channel 2 - PA1 */
    GPIO_setMode(GPIO_A, 1, ALTERNATE); // General purpose output mode
    GPIO_setAlternateFunction(GPIO_A, 1, AF1);

    TIM_ConfigOutputCompare(TIM2, CHANEL2, TIM_OCMODE2_PWM1);
    TIM_EnableOutputCompare(TIM2, CHANEL2, ACTIVE_HIGH);

    /* Set timer2 channel 3 - PA2 */
    GPIO_setMode(GPIO_A, 2, ALTERNATE); // General purpose output mode
    GPIO_setAlternateFunction(GPIO_A, 2, AF1);

    TIM_ConfigOutputCompare(TIM2, CHANEL3, TIM_OCMODE2_PWM1);
    TIM_EnableOutputCompare(TIM2, CHANEL3, ACTIVE_HIGH);

    /* Set timer2 channel 4 - PA3 */
    GPIO_setMode(GPIO_A, 3, ALTERNATE); // General purpose output mode
    GPIO_setAlternateFunction(GPIO_A, 3, AF1);

    TIM_ConfigOutputCompare(TIM2, CHANEL4, TIM_OCMODE2_PWM1);
    TIM_EnableOutputCompare(TIM2, CHANEL4, ACTIVE_HIGH);

    /* Set timer3 channel 1 - PA6 */
    GPIO_setMode(GPIO_A, 6, ALTERNATE); // General purpose output mode
    GPIO_setAlternateFunction(GPIO_A, 6, AF2);

    TIM_Config(TIM3, PWM_PRESCALER, PWM_PERIOD, TIM_MODE_BASIC);

    TIM_ConfigOutputCompare(TIM3, CHANEL1, TIM_OCMODE1_PWM1);
    TIM_EnableOutputCompare(TIM3, CHANEL1, ACTIVE_HIGH);

    /* Set timer3 channel 2 - PA7 */
    GPIO_setMode(GPIO_A, 7, ALTERNATE); // General purpose output mode
    GPIO_setAlternateFunction(GPIO_A, 7, AF2);

    TIM_ConfigOutputCompare(TIM3, CHANEL2, TIM_OCMODE1_PWM1);
    TIM_EnableOutputCompare(TIM3, CHANEL2, ACTIVE_HIGH);

    /* Set timer3 channel 3 - PC8 */
    GPIO_setMode(GPIO_C, 8, ALTERNATE); // General purpose output mode
    GPIO_setAlternateFunction(GPIO_C, 8, AF2);

    TIM_ConfigOutputCompare(TIM3, CHANEL3, TIM_OCMODE1_PWM1);
    TIM_EnableOutputCompare(TIM3, CHANEL3, ACTIVE_HIGH);

    /* Set timer3 channel 4 - PC9 */
    GPIO_setMode(GPIO_A, 9, ALTERNATE); // General purpose output mode
    GPIO_setAlternateFunction(GPIO_A, 7, AF2);

    TIM_ConfigOutputCompare(TIM3, CHANEL2, TIM_OCMODE1_PWM1);
    TIM_EnableOutputCompare(TIM3, CHANEL2, ACTIVE_HIGH);

    TIM_Start(TIM2);
    TIM_Start(TIM3);
		
		  TIM_Config(TIM4, 1600, 1000, TIM_MODE_BASIC);
  /*Enable interrupt TIM4*/
  TIM4->DIER |= (1 << 0);
  /*Enable IRQ tim4*/
  NVIC->ISER[0] |= (1 << 30);
  TIM_Start(TIM4);
}

void configGPIO(void)
{
    /* Set PB8 input */
    GPIO_setMode(GPIO_B, 8, INPUT);
    GPIO_setPullUpDown(GPIO_B, 8, PULL_UP);

    /* Enable interrupt EXTI8_9 */
    NVIC->ISER[0] |= (1 << 23);

    /* Select PORTB for EXTI8 */
    SYSCFG->EXTICR3 |= (1 << 0);
    /* Unmask EXTI8 */
    EXTI->IMR |= (1 << 8);
    /* Rising or Falling */
    EXTI->RTSR |= (1 << 8);

    /* Set PB9 input */
    GPIO_setMode(GPIO_B, 9, INPUT);
    GPIO_setPullUpDown(GPIO_B, 9, PULL_UP);

    GPIO_setMode(GPIO_C, 1, OUTPUT);
    GPIO_setMode(GPIO_C, 0, OUTPUT);
}

void configUsart(void)
{
	NVIC->ISER[1] |= (1 << 6);
  GPIO_setMode(GPIO_A, 2, ALTERNATE);
  GPIO_setAlternateFunction(GPIO_A, 2, AF7);

  GPIO_setMode(GPIO_A, 3, ALTERNATE);
  GPIO_setAlternateFunction(GPIO_A, 3, AF7);

  uart_set_baudrate(USART2, SYSTEM_CORE_CLOCK, 115200);

  USART2->CR1 |= (1 << 3);
  USART2->CR1 |= (1 << 2);
  USART2->CR1 |= USART_CR1_RXNEIE;
  USART2->CR1 |= (1 << 13);
}
