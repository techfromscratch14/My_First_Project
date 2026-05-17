#include <stdint.h>

/* Linker symbols*/

extern uint32_t _sidata;

extern uint32_t _sdata;
extern uint32_t _edata;

extern uint32_t _sbss;
extern uint32_t _ebss;

static void DataInit(void);
static void BssInit(void);


void main()
{

    while(1)
    {
        
    }

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