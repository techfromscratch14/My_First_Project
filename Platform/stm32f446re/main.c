#include <stdint.h>

/* Linker symbols*/

extern uint32_t _sidata;

extern uint32_t _sdata;
extern uint32_t _edata;

extern uint32_t _sbss;
extern uint32_t _ebss;

static void DataInit(void);
static void BssInit(void);


#define RCC_BASE        0x40023800UL
#define GPIOC_BASE      0x40020800UL

#define RCC_AHB1ENR     (*(volatile uint32_t *)(RCC_BASE + 0x30))
#define GPIOC_MODER     (*(volatile uint32_t *)(GPIOC_BASE + 0x00))
#define GPIOC_ODR       (*(volatile uint32_t *)(GPIOC_BASE + 0x14))


void delay(void)
{
    for(uint32_t i = 0; i < 5000000; i++);
}

int main()
{

    RCC_AHB1ENR |= (1 << 2); // To enable the clock for PORTC

    /* Configure PC5 as Output */
    GPIOC_MODER &= ~(3U << (5 * 2));  // Clear bits 11:10
    GPIOC_MODER |=  (1U << (5 * 2));  // Set bits 11:10 = 01

     while(1)
    {
        GPIOC_ODR ^= (1 << 5);   // Toggle PC5
        delay();
    }


    return 0;

}

void SystemInit()
{

    /* Initialize .data section */

    DataInit();

    /* Initialize .bss section*/

    BssInit();

}

/* copy initialized variables from FLASH to RAM */

static void DataInit(void)
{
    uint32_t *src = &_sidata;
    uint32_t *dst = &_sdata;
    while(dst < &_edata)
    {
        *dst = *src;

        dst++;
        src++;

    }
}

/* Clear uninitialized variables*/

static void BssInit(void)
{
    uint32_t *dst = &_sbss;

    while(dst < &_ebss)
    {
        *dst = 0;
        dst++;
    }
}