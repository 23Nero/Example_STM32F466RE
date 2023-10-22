#include "./../include/gpio.h"
#include "./../include/RCC.h"

int main()
{
    /* Enable clock */
    RCC->AHB1ENR |= (1 << 0);
    RCC->AHB1ENR |= (1 << 2);

    /* Set PA5 as output */
    GPIO_SetMode(GPIO_A, 5, OUTPUT);      // General purpose output mode
    GPIO_SetOutputType(GPIO_A, 5, 0x00);  // Push-pull output
    GPIO_SetOutputSpeed(GPIO_A, 5, 0x02); // High speed
    GPIO_SetPullUpDown(GPIO_A, 5, 0x00);  // No pull-up, no pull-down

    /* Set PC13 as input */
    GPIO_SetMode(GPIO_C, 13, INPUT);

    while (1)
    {
        uint32_t check = GPIO_ReadPin(GPIO_C, 13);
        if (check)
        {
            GPIO_SetPin(GPIO_A, 5);
        }
        else
        {
            GPIO_ResetPin(GPIO_A, 5);
        }
    }
}
