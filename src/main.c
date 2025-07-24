#include "stm32f1xx.h"
#include <stdint.h>

/*
    Только не пугайтесь этого огромного кода! Он всего лишь моргает диодом)
    Если серьезно - эта программа написана без использования даже CMSIS, что и делает её такой громадной 
    Суть - просто просигнализировать об успешной прошивке
*/

static void enable_port_clock(void);
static void configure_pin(void);
static void toggle_pin(void);

int main(void)
{
    enable_port_clock();
    configure_pin();

    for (;;)
    {
        for (uint32_t delay = 500000; delay > 0; delay--)
        {
        }

        toggle_pin();
    }
    return 0;
}

static void enable_port_clock(void)
{
    uint32_t rcc_base_address = 0x40021000;
    uint32_t rcc_apb2enr_address = rcc_base_address + 0x18;
    uint32_t rcc_apb2enr_iopcen = 1 << 4;

    uint32_t *rcc_apb2enr_pointer = (uint32_t *)rcc_apb2enr_address;
    uint32_t rcc_apb2enr_value = *rcc_apb2enr_pointer;
    rcc_apb2enr_value |= rcc_apb2enr_iopcen;
    *rcc_apb2enr_pointer = rcc_apb2enr_value;
}

static void configure_pin(void)
{
    uint32_t gpioc_base_address = 0x40011000;
    uint32_t gpioc_crh_address = gpioc_base_address + 0x04;
    uint32_t gpiox_crh_mode13_0 = 1 << 20;
    uint32_t gpiox_crh_mode13_1 = 1 << 21;
    uint32_t gpiox_crh_cnf13_0 = 1 << 22;
    uint32_t gpiox_crh_cnf13_1 = 1 << 23;

    uint32_t *gpioc_crh_pointer = (uint32_t *)gpioc_crh_address;
    uint32_t gpioc_crh_value = *gpioc_crh_pointer;
    gpioc_crh_value &= ~gpiox_crh_mode13_0;
    gpioc_crh_value |= gpiox_crh_mode13_1;
    gpioc_crh_value |= gpiox_crh_cnf13_0;
    gpioc_crh_value &= ~gpiox_crh_cnf13_1;
    *gpioc_crh_pointer = gpioc_crh_value;
}

static void toggle_pin(void)
{
    uint32_t gpioc_base_address = 0x40011000;
    uint32_t gpioc_odr_address = gpioc_base_address + 0x0c;
    uint32_t gpiox_odr_odr13 = 1 << 13;

    uint32_t *gpioc_odr_pointer = (uint32_t *)gpioc_odr_address;
    uint32_t gpioc_odr_value = *gpioc_odr_pointer;
    gpioc_odr_value ^= gpiox_odr_odr13;
    *gpioc_odr_pointer = gpioc_odr_value;
}
