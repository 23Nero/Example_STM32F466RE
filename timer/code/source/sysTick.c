#include "./../include/sysTick.h"
#include "./../include/RCC.h"

void configSysTickInt(uint8_t interrupt)
{
    sysTick->SYST_CSR = 0;                              // Disable counter
    sysTick->SYST_RVR = (SYSTEM_CORE_CLOCK / 1000) - 1; // set clock count 1 ms
    sysTick->SYST_CVR = 0;                              // clear current value to 0

    if (interrupt)
    {
        sysTick->SYST_CSR |= 7; // Enable interrupt
    }
    else
    {
        sysTick->SYST_CSR |= 5; // Not use interrupt
    }
}

void delay(uint32_t milliseconds)
{
    sysTick->SYST_RVR = (milliseconds * SYSTEM_CORE_CLOCK / 1000U) - 1U; // set clock count 1 ms

    sysTick->SYST_CVR = 0;
    sysTick->SYST_CSR |= 1; // Enable SysTick counter

    while (!(sysTick->SYST_CSR & (1 << 16)))
    {
        // Wait until COUNTFLAG becomes 1 (delay time has passed)
    }
    sysTick->SYST_CSR &= ~(1U); // Disable SysTick counter
}
