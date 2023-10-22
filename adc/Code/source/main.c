#include "./../include/gpio.h"
#include "./../include/uart.h"
#include "./../include/RCC.h"
#include "./../include/adc.h"

int main()
{
  /* Enable clock */
  RCC->AHB1ENR |= (1 << 0);
  RCC->AHB1ENR |= (1 << 2);
  RCC->APB1ENR |= (1 << 17);

  /* Set PA5 as output */
  GPIO_SetMode(GPIO_A, 5, OUTPUT);      // General purpose output mode
  GPIO_SetOutputType(GPIO_A, 5, 0x00);  // Push-pull output
  GPIO_SetOutputSpeed(GPIO_A, 5, 0x02); // High speed
  GPIO_SetPullUpDown(GPIO_A, 5, 0x00);  // No pull-up, no pull-down

  GPIO_SetMode(GPIO_A, 0, OUTPUT);      // General purpose output mode
  GPIO_SetOutputType(GPIO_A, 0, 0x00);  // Push-pull output
  GPIO_SetOutputSpeed(GPIO_A, 0, 0x02); // High speed
  GPIO_SetPullUpDown(GPIO_A, 0, 0x00);  // No pull-up, no pull-down
  /* Set PC13 as input */
  GPIO_SetMode(GPIO_C, 13, INPUT);

  /* Set USART2 */
  GPIO_SetMode(GPIO_A, 2, ALTERNATE);
  GPIO_SetAlternateFunction(GPIO_A, 2, AF7);

  GPIO_SetMode(GPIO_A, 3, ALTERNATE);
  GPIO_SetAlternateFunction(GPIO_A, 3, AF7);

  uart_set_baudrate(USART2, 16000000, 115200);

  USART2->CR1 |= (1 << 3);
  USART2->CR1 |= (1 << 2);

  USART2->CR1 |= (1 << 13);
  // char key[BUFFER];

  /* Set ADC */
  GPIO_SetMode(GPIO_A, 1, ANALOG);
  RCC->APB2ENR |= (1 << 8);

  /* Conversion sequence start */
  ADC1->SQR3 |= ADC_CH1;

  /* Coversion sequence length */
  ADC1->SQR1 = ADC_SEQ_LEN_1;

  /* Enable ADC module */
  ADC1->CR2 |= CR2_ADON;

  /* Enable continuous conversion */
  ADC1->CR2 |= CR2_CONT;
  /* Start Coversion */
  ADC1->CR2 |= CR2_SWSTART;
  /* Wait for conversion to be complete */
  while (!(ADC1->SR & SR_EOC))
    ;
  uint32_t result_adc = ADC1->DR;

  while (1)
  {
  while (!(ADC1->SR & SR_EOC))
    ;
  result_adc = ADC1->DR;
  }
}
