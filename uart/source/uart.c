#include "./../include/uart.h"
#include "./../include/RCC.h"

uint16_t compute_uart(uint32_t PeriphClk, uint32_t BaudRate)
{
    return ((PeriphClk + (BaudRate / 2u) / BaudRate));
}

void uart_set_baudrate(USART_t *USARTx, uint32_t PeriphClk, uint32_t BaudRate)
{
    USARTx->BRR = compute_uart(PeriphClk, BaudRate);
}

void USART_SendChar(USART_t *usart, char ch)
{
    while (!(usart->SR & USART_SR_TXE));
    usart->DR = ch;
}

void USART_SendString(USART_t *usart, const char *str)
{
    while (*str != '\0')
    {
        USART_SendChar(usart, *str);
        str++;
    }
}


