#include "./../include/timer.h"

// Hàm cấu hình timer với chu kỳ và chế độ cơ bản
void TIM_Config(timer_t *tim, uint32_t prescaler, uint32_t period, uint32_t mode)
{
    // Dừng timer trước khi cấu hình
    TIM_Stop(tim);

    // Cấu hình Prescaler và Period
    tim->PSC = prescaler - 1; // Đặt bộ chia tần số
    tim->ARR = period - 1;    // Đặt giá trị tự động nạp

    // Cấu hình chế độ
    tim->CR1 |= mode; // Chế độ cơ bản

    // Xóa cờ Update (chờ cho lần đầu tiên)
    TIM_ClearUpdateInterruptFlag(tim);
}

// Hàm bắt đầu timer
void TIM_Start(timer_t *tim)
{
    tim->CR1 |= TIM_CR1_CEN; // Bật bit CEN để bắt đầu đếm
}

// Hàm dừng timer
void TIM_Stop(timer_t *tim)
{
    tim->CR1 &= ~TIM_CR1_CEN; // Tắt bit CEN để dừng đếm
}

// Hàm xác định trạng thái cờ Update
uint32_t TIM_GetUpdateInterruptStatus(timer_t *tim)
{
    return (tim->SR & TIM_SR_UIF);
}

// Hàm xóa cờ Update
void TIM_ClearUpdateInterruptFlag(timer_t *tim)
{
    tim->SR &= ~TIM_SR_UIF;
}

// Hàm cấu hình chế độ so sánh đầu ra (Output Compare Mode) cho một kênh cụ thể của timer
void TIM_ConfigOutputCompare(timer_t *tim, uint8_t channel, uint32_t mode)
{
    // Tắt chế độ so sánh trước khi cấu hình
    tim->CCER &= ~(uint32_t)(TIM_CCER_CC1E << (channel * 4)); // Xóa bit CCxE cho kênh cụ thể

    // Cấu hình chế độ so sánh cho kênh cụ thể
    tim->CCMR1 |= (uint32_t)(mode << (4 * channel)); // Cài đặt chế độ so sánh cho kênh cụ thể

    // Bật chế độ so sánh cho kênh cụ thể
    tim->CCER |= (uint32_t)(TIM_CCER_CC1E << (channel * 4)); // Bật bit CCxE cho kênh cụ thể
}

// Hàm đặt giá trị so sánh (Compare Value) cho một kênh cụ thể của timer
void TIM_SetDutyCycle(timer_t *tim, uint8_t channel, uint16_t dutyCycle) 
{
    uint32_t period = tim->ARR;
    uint32_t compareValue = (dutyCycle * (period + 1)) / 100;
    
    switch (channel) {
        case 1:
            tim->CCR1 = compareValue;
            break;
        case 2:
            tim->CCR2 = compareValue;
            break;
        case 3:
            tim->CCR3 = compareValue;
            break;
        case 4:
            tim->CCR4 = compareValue;
            break;
        // Thêm các trường hợp khác tùy theo số lượng kênh của timer
        default:
            // Xử lý lỗi hoặc thêm các kênh khác (nếu có)
            break;
    }
}

// Hàm bật chế độ so sánh đầu ra (Output Compare) cho một kênh cụ thể của timer
void TIM_EnableOutputCompare(timer_t *tim, uint8_t channel)
{
    tim->CCER |= (uint32_t)(TIM_CCER_CC1E << (channel * 4)); // Bật bit CCxE cho kênh cụ thể
}

// Hàm tắt chế độ so sánh đầu ra (Output Compare) cho một kênh cụ thể của timer
void TIM_DisableOutputCompare(timer_t *tim, uint8_t channel)
{
    tim->CCER &= ~(uint32_t)(TIM_CCER_CC1E << (channel * 4)); // Xóa bit CCxE cho kênh cụ thể
}
