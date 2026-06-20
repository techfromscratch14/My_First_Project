#include <stdint.h>

/* Linker symbols*/

extern uint32_t _sidata;

extern uint32_t _sdata;
extern uint32_t _edata;

extern uint32_t _sbss;
extern uint32_t _ebss;

static void DataInit(void);
static void BssInit(void);

/******************************************************************************
 * Project : Push Button Interface (No HAL)
 * Board   : STM32F446RE Nucleo
 *
 * Requirement:
 * ---------------------------------------------------------
 * 1. Configure PA5 as GPIO Output.
 * 2. Configure PC13 as GPIO Input.
 * 3. By default LED should be OFF.
 * 4. When Push Button is pressed, LED should turn ON.
 * 
 *******************************************************************************/
/************************************************
 * RCC Registers
 ***********************************************/

#define RCC_BASE_ADDR              0x40023800UL

#define RCC_AHB1ENR_REG           (*(volatile uint32_t *)(RCC_BASE_ADDR + 0x30))


/************************************************
 * GPIOA Registers
 ***********************************************/

#define GPIOA_BASE_ADDR           0x40020000UL

#define GPIOA_MODER_REG          (*(volatile uint32_t *)(GPIOA_BASE_ADDR + 0x00))
#define GPIOA_OTYPER_REG         (*(volatile uint32_t *)(GPIOA_BASE_ADDR + 0x04))
#define GPIOA_OSPEEDR_REG        (*(volatile uint32_t *)(GPIOA_BASE_ADDR + 0x08))
#define GPIOA_PUPDR_REG          (*(volatile uint32_t *)(GPIOA_BASE_ADDR + 0x0C))
#define GPIOA_IDR_REG            (*(volatile uint32_t *)(GPIOA_BASE_ADDR + 0x10))
#define GPIOA_ODR_REG            (*(volatile uint32_t *)(GPIOA_BASE_ADDR + 0x14))

/************************************************
 * GPIOC Registers
 ***********************************************/

#define GPIOC_BASE_ADDR           0x40020800UL

#define GPIOC_MODER_REG          (*(volatile uint32_t *)(GPIOC_BASE_ADDR + 0x00))
#define GPIOC_OTYPER_REG         (*(volatile uint32_t *)(GPIOC_BASE_ADDR + 0x04))
#define GPIOC_OSPEEDR_REG        (*(volatile uint32_t *)(GPIOC_BASE_ADDR + 0x08))
#define GPIOC_PUPDR_REG          (*(volatile uint32_t *)(GPIOC_BASE_ADDR + 0x0C))
#define GPIOC_IDR_REG            (*(volatile uint32_t *)(GPIOC_BASE_ADDR + 0x10))
#define GPIOC_ODR_REG            (*(volatile uint32_t *)(GPIOC_BASE_ADDR + 0x14))


int main()
{

    
     /* Enable GPIOA Clock */
    RCC_AHB1ENR_REG |= (1 << 0);

    /* Enable GPIOC Clock */
    RCC_AHB1ENR_REG |= (1 << 2);

     /* PA5 Output */
    GPIOA_MODER_REG &= ~(3 << 10);
    GPIOA_MODER_REG |=  (1 << 10);

    GPIOA_OTYPER_REG &= ~(1 << 5);

    GPIOA_OSPEEDR_REG |= (3 << 10);

    GPIOA_PUPDR_REG &= ~(3 << 10);


    /* PC13 Input */
    GPIOC_MODER_REG &= ~(3 << 26);

    GPIOC_PUPDR_REG &= ~(3 << 26);
    GPIOC_PUPDR_REG |=  (1 << 26);
	

    while(1)
    {

         if((GPIOC_IDR_REG & (1<<13)) == 0)
        {
            GPIOA_ODR_REG |= (1<<5);
        }
        else
        {
            GPIOA_ODR_REG &= ~(1<<5);
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