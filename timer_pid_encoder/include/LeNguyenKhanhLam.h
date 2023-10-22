#ifndef __LeNguyenKhanhLam_H__
#define __LeNguyenKhanhLam_H__

#include "./../include/gpio.h"
#include "./../include/uart.h"
#include "./../include/timer.h"
#include "./../include/sysTick.h"
#include "./../include/interrupt.h"
#include "./../include/RCC.h"
#include "./../include/spi.h"
#include "./../pid.h"


void enaleClockModule(void);
void configTim(void);
void configGPIO(void);
void configUsart(void);

void chay(void);

void wheel(int16_t energy);
int calculatePulses(float angle);
void sysInit(void);

#endif
