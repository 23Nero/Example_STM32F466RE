#ifndef __CAN_H__
#define __CAN_H__

#include <stdint.h>

#define CAN1_BASE ((uint32_t *)0x40006800)
#define CAN2_BASE ((uint32_t *)0x40006400)

struct CAN
{
    volatile uint32_t MCR;
    
}CAN_t;


#define CAN1 ((CAN_t *)CAN1_BASE)
#define CAN2 ((CAN_t *)CAN2_BASE)

#endif