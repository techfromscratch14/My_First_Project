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
#define GPIOA_BASE      0x40020000UL



#define RCC_AHB1ENR     (*(volatile uint32_t *)(RCC_BASE + 0x30))
#define GPIOA_MODER     (*(volatile uint32_t *)(GPIOA_BASE + 0x00))
#define GPIOA_ODR       (*(volatile uint32_t *)(GPIOA_BASE + 0x14))
#define GPIOA_BSRR       (*(volatile uint32_t *)(GPIOA_BASE + 0x18))

void delay(void)
{
    for(uint32_t i = 0; i < 500000; i++);
}

int main()
{

    
    while(1)
    {

        
        /* Enable GPIOA clock */
    RCC_AHB1ENR |= (1 << 0);

    
    /* Configure PA5 as output */
    GPIOA_MODER &= ~(3U << (5 * 2)); // clear the existing configuration

    GPIOA_MODER |=  (1U << (5 * 2)); // Set the new configuration of the PIN

      while(1)
    {

        /***************************  By toggling****************/
        GPIOA_ODR ^= (1 << 5);   // Toggle PA5 ( ODR - will read and write the value)

        /**************** Another method ************************/
    //    GPIOA_BSRR |= (1<<21); // Reset PA5 bit using BSRR register
    //     delay();
    //   GPIOA_BSRR |= (1<<5); // Set PA5 bit using BSRR register
    //     delay();
    }


        
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