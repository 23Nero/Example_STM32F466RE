#include "./../include/LeNguyenK
hanhLam.h"

static char buff[BUFFER];

int main()
{
  sysInit();

  // Khởi tạo DMA1 Stream 6
  uint32_t source_address = (uint32_t) "Hello";             // Địa chỉ của dữ liệu bạn muốn gửi
  uint32_t destination_address = (uint32_t) & (USART2->DR); // Địa chỉ của thanh ghi dữ liệu USART2
  uint32_t data_count = strlen("Hello");                    // Độ dài dữ liệu cần gửi
  DMA_stream_init(DMA1, 6, source_address, destination_address, data_count);
  DMA_usat_tx_enable(USART2);
  NVIC->ISER[0] |= (1 << 17);

  while (1)
  {
    // do something
  }
}

void USART2_IRQHandler(void)
{
  if (USART2->SR & USART_SR_RXNE)
  {
    USART_receiveString(USART2, buff, BUFFER);
  }
}

void DMA1_Stream6_IRQHandler(void)
{
  /** Check for trafer complete*/
  if (DMA1->HISR & (1 << 21))
  {
    /** Clear flag */
    DMA1->HIFCR |= (1 << 21);
  }
}
