#include "./../include/LeNguyenKhanhLam.h"

void runPID(void);
void sendData(int pos);

#define GEARRATIO 30

volatile static position;

static PID_TypeDef BPID;

static double inPutBase, outPutBase, lastOutPutBase, baseSetpoint;
static double posBase = 0;

static double E1, E2, Ea, alpha1, beta1, gama1, T;
static double Kd1, Kp1, Ki1;

static char buff[BUFFER];

int main()
{
  sysInit();
	
  GPIO_setMode(GPIO_A, 2, ALTERNATE);
  GPIO_setAlternateFunction(GPIO_A, 2, AF7);

  GPIO_setMode(GPIO_A, 3, ALTERNATE);
  GPIO_setAlternateFunction(GPIO_A, 3, AF7);

  uart_set_baudrate(USART2, SYSTEM_CORE_CLOCK, 115200);

  USART2->CR1 |= (1 << 3);
  USART2->CR1 |= (1 << 2);

  USART2->CR1 |= (1 << 13);

  USART_sendString(USART2, "\n xena cute");
			
  T = 0.01;
  E1 = E2 = Ea = 0;
  Kp1 = 1;
  Ki1 = 1;
  Kd1 = 1;

  while (1)
  {

  }
}

void USART2_IRQHandler(void)
{
  if (USART2->SR & USART_SR_RXNE)
  {
    USART_receiveString(USART2, buff, BUFFER);
    sendData(position);
  }
}

void chay(void)
{
  if (GPIO_readPin(GPIO_B, 9))
    position--;
  else
    position++;
}

void EXTI9_5_IRQHandler(void)
{
  chay();

  EXTI->PR |= (1 << 8);
}

// Calculate the number of pulses corresponding to a specific angle (in radians)
int calculatePulses(float angle)
{
  double pulsesPerRevolution = 11.0 * GEARRATIO;                                  // Number of pulses from the Encoder per revolution
  double pulsesEquivalent = (pulsesPerRevolution * (double)angle) / (360.0); // Calculate the equivalent pulses
  return (int)pulsesEquivalent;                                                   // Return the number of pulses as an integer
}

void runPID(void)
{
  posBase = calculatePulses(90);

  Ea = (baseSetpoint)-posBase;
  alpha1 = 2 * T * Kp1 + Ki1 * T * T + 2 * Kd1;
  beta1 = T * T * Ki1 - 4 * Kd1 - 2 * T * Kp1;
  gama1 = 2 * Kd1;
  outPutBase = (alpha1 * Ea + beta1 * E1 + gama1 * E2 + 2 * T * lastOutPutBase) / (2 * T);
  lastOutPutBase = outPutBase;
  E2 = E1;
  E1 = Ea;

  if (outPutBase > 255)
  {
    outPutBase = 255;
  }
  else if (outPutBase < -255)
  {
    outPutBase = -255;
  }
  if (outPutBase > 0)
  {
    TIM_SetDutyCycle(TIM2, CHANEL1, (uint16_t)outPutBase);
    GPIO_setPin(GPIO_C, 1);
    GPIO_resetPin(GPIO_C, 0);
  }
  else if (outPutBase < 0)
  {
    TIM_SetDutyCycle(TIM2, CHANEL1, (uint16_t)-outPutBase);
    GPIO_setPin(GPIO_C, 0);
    GPIO_resetPin(GPIO_C, 1);
  }
  else
  {
    GPIO_resetPin(GPIO_C, 0);
    GPIO_resetPin(GPIO_C, 1);
  }
}
void TIM4_IRQHandler(void)
{
  USART_sendString(USART2, "Hellu!\n");
  TIM4->SR &= ~(1u << 0);
}

void sendData(int pos)
{
  char buffer[33];
  sprintf(buffer, "%d", pos);
  USART_sendString(USART2, buffer);
  USART_sendString(USART2, "\n");
}

