#include "./../include/gpio.h"
#include "./../include/uart.h"
#include "./../include/RCC.h"

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

    /* Set PC13 as input */
    GPIO_SetMode(GPIO_C, 13, INPUT);

    /* Set USART2 */
    GPIO_SetMode(GPIO_A, 2, ALTERNATE);
    GPIO_SetAlternateFunction(GPIO_A, 2, AF7);

    uart_set_baudrate(USART2, 16000000, 115200);
    USART2->CR1 |= (1 << 3);
    USART2->CR1 |= (1 << 13);


    while (1)
    {
        USART_SendChar(USART2, 'A');
    }
}
