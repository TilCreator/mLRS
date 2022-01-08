//*******************************************************
// Copyright (c) MLRS project
// GPL3
// https://www.gnu.org/licenses/gpl-3.0.de.html
// OlliW @ www.olliw.eu
//*******************************************************
// hal
//*******************************************************

//-------------------------------------------------------
// TX DIY MOADULE01v014 STM32G491RE
//-------------------------------------------------------
#define DEVICE_IS_TRANSMITTER


//-- Timers, Timing and such stuff

#define DELAY_USE_DWT

#define SYSTICK_TIMESTEP          1000
#define SYSTICK_DELAY_MS(x)       (uint16_t)(((uint32_t)(x)*(uint32_t)1000)/SYSTICK_TIMESTEP)


//-- UARTS
// UARTB = serial port, UARTC = USB (debug port), UARTD = BT/ESP port
// UART = SPORT (pin5) on JR bay

#define UARTB_USE_UART5 // serial
#define UARTB_BAUD                57600 // 115200
#define UARTB_USE_TX
#define UARTB_TXBUFSIZE           512
#define UARTB_USE_TX_ISR
#define UARTB_USE_RX
#define UARTB_RXBUFSIZE           512

#define UARTB_RTS                 IO_PB4
#define UARTB_CTS                 IO_PB5

#define UARTC_USE_UART1 // USB, debug
#define UARTC_BAUD                115200
#define UARTC_USE_TX
#define UARTC_TXBUFSIZE           512
#define UARTC_USE_TX_ISR
#define UARTC_USE_RX
#define UARTC_RXBUFSIZE           512

#define UART_USE_UART2 // MBridge
#define UART_BAUD                 400000 // 115200
#define UART_USE_TX
#define UART_TXBUFSIZE            512
#define UART_USE_TX_ISR
#define UART_USE_RX
#define UART_RXBUFSIZE            512

#define TX_INVERT_INTERNAL
#define RX_INVERT_INTERNAL

#define UARTD_USE_UART4 // BT/ESP
#define UARTD_BAUD                115200
#define UARTD_USE_TX
#define UARTD_TXBUFSIZE           512
#define UARTD_USE_TX_ISR
#define UARTD_USE_RX
#define UARTD_RXBUFSIZE           512

#define ESP_RESET                 IO_PA11
#define ESP_GPIO                  IO_PA12


//-- SX12xx & SPI

#define SPI_USE_SPI1              // PA5, PA6, PA7
#define SPI_CS_IO                 IO_PA4
#define SPI_USE_CLK_LOW_1EDGE     // datasheet says CPHA = 0  CPOL = 0
#define SPI_USE_CLOCKSPEED_2250KHZ // SPI_USE_CLOCKSPEED_4500KHZ // SPI_USE_CLOCKSPEED_9MHZ // 9 MHz seems to be too fast! got Tx lockups

#define SX_RESET                  IO_PB0
#define SX_DIO1                   IO_PC4
#define SX_BUSY                   IO_PC5
//#define SX_AMP_CTX
//#define SX_ANT_SELECT

//#define SX_USE_DCDC

//#define SX_POWER_MAX              SX1280_POWER_DBM_TO_REG(0) // don't blast all at it

#define SX_DIO1_GPIO_AF_EXTI_PORTx    LL_GPIO_AF_EXTI_PORTC
#define SX_DIO1_GPIO_AF_EXTI_LINEx    LL_GPIO_AF_EXTI_LINE4
#define SX_DIO1_EXTI_LINE_x           LL_EXTI_LINE_4
#define SX_DIO1_EXTI_IRQn             EXTI4_IRQn
#define SX_DIO1_EXTI_IRQHandler       EXTI4_IRQHandler
//#define SX_DIO1_EXTI_IRQ_PRIORITY   11

void sx_init_gpio(void)
{
  gpio_init(SX_RESET, IO_MODE_OUTPUT_PP_HIGH, IO_SPEED_VERYFAST);

  gpio_init(SX_DIO1, IO_MODE_INPUT_PD, IO_SPEED_VERYFAST);
}

bool sx_dio1_read(void)
{
  return (gpio_read_activehigh(SX_DIO1)) ? true : false;
}

void sx_amp_transmit(void)
{
}

void sx_amp_receive(void)
{
}

void sx_dio1_init_exti_isroff(void)
{
  LL_GPIO_AF_SetEXTISource(SX_DIO1_GPIO_AF_EXTI_PORTx, SX_DIO1_GPIO_AF_EXTI_LINEx);

  // let's not use LL_EXTI_Init(), but let's do it by hand, is easier to allow enabling isr later
  LL_EXTI_DisableEvent_0_31(SX_DIO1_EXTI_LINE_x);
  LL_EXTI_DisableIT_0_31(SX_DIO1_EXTI_LINE_x);
  LL_EXTI_DisableFallingTrig_0_31(SX_DIO1_EXTI_LINE_x);
  LL_EXTI_EnableRisingTrig_0_31(SX_DIO1_EXTI_LINE_x);

  NVIC_SetPriority(SX_DIO1_EXTI_IRQn, SX_DIO1_EXTI_IRQ_PRIORITY);
  NVIC_EnableIRQ(SX_DIO1_EXTI_IRQn);
}

void sx_dio1_enable_exti_isr(void)
{
  LL_EXTI_ClearFlag_0_31(SX_DIO1_EXTI_LINE_x);
  LL_EXTI_EnableIT_0_31(SX_DIO1_EXTI_LINE_x);
}


//-- SX12xx II & SPIB

#define SPIB_USE_SPI1             // PB12, PB13, PB14
#define SPIB_CS_IO                IO_PB12
#define SPIB_USE_CLK_LOW_1EDGE    // datasheet says CPHA = 0  CPOL = 0
#define SPIB_USE_CLOCKSPEED_2250KHZ

#define SX2_RESET                 IO_PC8
#define SX2_DIO1                  IO_PC6
#define SX2_BUSY                  IO_PC7
//#define SX2_AMP_CTX
//#define SX2_ANT_SELECT

//#define SX2_USE_DCDC

//#define SX2_POWER_MAX             SX1280_POWER_DBM_TO_REG(0) // don't blast all at it

#define SX2_DIO1_GPIO_AF_EXTI_PORTx   LL_GPIO_AF_EXTI_PORTC
#define SX2_DIO1_GPIO_AF_EXTI_LINEx   LL_GPIO_AF_EXTI_LINE6
#define SX2_DIO1_EXTI_LINE_x          LL_EXTI_LINE_6
#define SX2_DIO1_EXTI_IRQn            EXTI9_5_IRQn
#define SX2_DIO1_EXTI_IRQHandler      EXTI9_5_IRQHandler
//#define SX2_DIO1_EXTI_IRQ_PRIORITY   11


//-- Button

#define BUTTON                    IO_PB9

void button_init(void)
{
  gpio_init(BUTTON, IO_MODE_INPUT_PU, IO_SPEED_DEFAULT);
}

bool button_pressed(void)
{
  return gpio_read_activelow(BUTTON);
}


//-- LEDs

#define LED_LEFT_GREEN            IO_PC3
#define LED_LEFT_RED              IO_PC25
#define LED_RIGHT_GREEN           IO_PC0
#define LED_RIGHT_RED             IO_PC13 // ???????

#define LED_GREEN_ON              gpio_low(LED_LEFT_GREEN)
#define LED_RED_ON                gpio_low(LED_LEFT_RED)
#define LED_RIGHT_RED_ON          gpio_low(LED_RIGHT_RED)
#define LED_RIGHT_GREEN_ON        gpio_low(LED_RIGHT_GREEN)

#define LED_GREEN_OFF             gpio_high(LED_LEFT_GREEN)
#define LED_RED_OFF               gpio_high(LED_LEFT_RED)
#define LED_RIGHT_RED_OFF         gpio_high(LED_RIGHT_RED)
#define LED_RIGHT_GREEN_OFF       gpio_high(LED_RIGHT_GREEN)

#define LED_GREEN_TOGGLE          gpio_toggle(LED_LEFT_GREEN)
#define LED_RED_TOGGLE            gpio_toggle(LED_LEFT_RED)
#define LED_RIGHT_RED_TOGGLE      gpio_toggle(LED_RIGHT_RED)
#define LED_RIGHT_GREEN_TOGGLE    gpio_toggle(LED_RIGHT_GREEN)

void leds_init(void)
{
  gpio_init(LED_LEFT_GREEN, IO_MODE_OUTPUT_PP_HIGH, IO_SPEED_DEFAULT);
  gpio_init(LED_LEFT_RED, IO_MODE_OUTPUT_PP_HIGH, IO_SPEED_DEFAULT);
  gpio_init(LED_RIGHT_GREEN, IO_MODE_OUTPUT_PP_HIGH, IO_SPEED_DEFAULT);
  gpio_init(LED_RIGHT_RED, IO_MODE_OUTPUT_PP_HIGH, IO_SPEED_DEFAULT);
  LED_GREEN_OFF;
  LED_RED_OFF;
  LED_RIGHT_RED_OFF;
  LED_RIGHT_GREEN_OFF;
}


//-- Position Switch

#define POS_SWITCH_BIT1
#define POS_SWITCH_BIT2
#define POS_SWITCH_BIT3
#define POS_SWITCH_BIT4

void pos_switch_init(void)
{
}

uint8_t pos_switch_read(void)
{
  return 0;
}


//-- 5 Way Switch

#define FIVEWAY_SWITCH_CENTER     IO_PC15
#define FIVEWAY_SWITCH_UP         IO_PC14
#define FIVEWAY_SWITCH_DOWN       IO_PA1
#define FIVEWAY_SWITCH_LEFT       IO_PA0
#define FIVEWAY_SWITCH_RIGHT      IO_PC1

void fiveway_init(void)
{
  gpio_init(FIVEWAY_SWITCH_CENTER, IO_MODE_INPUT_PU, IO_SPEED_DEFAULT);
  gpio_init(FIVEWAY_SWITCH_UP, IO_MODE_INPUT_PU, IO_SPEED_DEFAULT);
  gpio_init(FIVEWAY_SWITCH_DOWN, IO_MODE_INPUT_PU, IO_SPEED_DEFAULT);
  gpio_init(FIVEWAY_SWITCH_LEFT, IO_MODE_INPUT_PU, IO_SPEED_DEFAULT);
  gpio_init(FIVEWAY_SWITCH_RIGHT, IO_MODE_INPUT_PU, IO_SPEED_DEFAULT);
}

bool fiveway_pressed(void)
{
  return gpio_read_activelow(FIVEWAY_SWITCH_CENTER);
}

uint8_t fiveway_read(void)
{
  return (uint8_t)gpio_read_activelow(FIVEWAY_SWITCH_UP) +
         ((uint8_t)gpio_read_activelow(FIVEWAY_SWITCH_DOWN) << 1) +
         ((uint8_t)gpio_read_activelow(FIVEWAY_SWITCH_LEFT) << 2) +
         ((uint8_t)gpio_read_activelow(FIVEWAY_SWITCH_RIGHT) << 3);
}


//-- OLED I2C

#define I2C_USE_I2C3              // PA8, PC9
#define I2C_SCL                   IO_PA8
#define I2C_SDA                   IO_PC9

void oled_init_gpio(void)
{
}




