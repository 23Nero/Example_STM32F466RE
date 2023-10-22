#include "./../include/dma.h"
#include "./../include/uart.h"
#include "./../include/interrupt.h"

DMA_t *DMA1 = (DMA_t *)DMA1_BASE;
DMA_t *DMA2 = (DMA_t *)DMA2_BASE;

#define DMA1EN (1 << 21)
#define CHSEL4 (1 << 27)
#define DMA_MEM_INC (1 << 10)
#define DMA_DIR_MEM_TO_PERIPH (1 << 6)
#define DMA_CR_TCIE (1 << 4)
#define DMA_CR_EN (1U << 0)
#define UART_CR3_DMAT (1 << 7)

void dma1_stream6_init(uint32_t src, uint32_t dst, uint32_t len)
{
    /** Disable DMA1 Stream6*/
    DMA1->stream[6].CR &= ~DMA_CR_EN;
    while (DMA1->stream[6].CR & DMA_CR_EN)
        ;
    /** Clear all interrupt flags of stream6*/
    DMA1->HIFCR |= (1 << 16) | (1 << 18) | (1 << 19) | (1 << 20) | (1 << 21);

    /** Set destrination buffer*/
    DMA1->stream[6].PAR = dst;

    /** Set the source buffer*/
    DMA1->stream[6].M0AR = src;

    /**Set lenght*/
    DMA1->stream[6].NDTR = len;

    /** Select stream6  CH4*/
    DMA1->stream[6].CR |= CHSEL4;

    /** Enable memory increment*/
    DMA1->stream[6].CR |= DMA_MEM_INC;

    /** Configure tranfer direction*/
    DMA1->stream[6].CR |= DMA_DIR_MEM_TO_PERIPH;

    /** Enable DMA transfer complete interrupt*/
    DMA1->stream[6].CR |= DMA_CR_TCIE;

    /** Enable direct mode and disable FIFO*/
    DMA1->stream[6].FCR = 0;

    /** Enable DMA1 Stream6*/
    DMA1->stream[6].CR |= DMA_CR_EN;

    /** Enable USART2 transmitter DMA*/
    USART2->CR3 |= UART_CR3_DMAT;

    /** DMA Interrupt enable in NVIC*/
    NVIC->ISER[0] |= (1 << 17);
}

// Hàm bật DMA stream
void DMA_enable(DMA_t *dma, uint8_t stream) 
{
    dma->stream[stream].CR |= DMA_CR_EN;
}

// Hàm tắt DMA stream
void DMA_disable(DMA_t *dma, uint8_t stream) 
{
    dma->stream[stream].CR &= ~DMA_CR_EN;
}

// Hàm khởi tạo cấu hình cho DMA stream
void DMA_stream_init(DMA_t *dma, uint8_t stream, uint32_t src, uint32_t dst, uint32_t len) 
{
    // Tắt DMA stream trước khi cấu hình
    dma->stream[stream].CR &= ~DMA_CR_EN;
    while (dma->stream[stream].CR & DMA_CR_EN);

    // Xóa tất cả các cờ ngắt của stream
    dma->HIFCR |= (1 << 16) | (1 << 18) | (1 << 19) | (1 << 20) | (1 << 21);

    // Đặt địa chỉ đích
    dma->stream[stream].PAR = dst;

    // Đặt địa chỉ nguồn
    dma->stream[stream].M0AR = src;

    // Đặt độ dài dữ liệu cần truyền
    dma->stream[stream].NDTR = len;

    // Cấu hình các thiết lập khác cho stream
    dma->stream[stream].CR |= CHSEL4; // Chọn kênh 4
    dma->stream[stream].CR |= DMA_MEM_INC; // Cho phép tăng địa chỉ bộ nhớ
    dma->stream[stream].CR |= DMA_DIR_MEM_TO_PERIPH; // Hướng truyền từ bộ nhớ đến thiết bị ngoại vi
    dma->stream[stream].CR |= DMA_CR_TCIE; // Bật ngắt hoàn thành truyền
    dma->stream[stream].FCR = 0; // Tắt chế độ FIFO

    // Bật DMA stream
    dma->stream[stream].CR |= DMA_CR_EN;
}

void  DMA_usat_tx_enable(USART_t *usart)
{
    usart->CR3 |= (1 << 7);
}
