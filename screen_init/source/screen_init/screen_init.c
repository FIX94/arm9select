#include <inttypes.h>

#define BRIGHTNESS 0x39

static inline void regSet();
void __attribute__ ((naked)) a11Entry()
{
    __asm__ ("ldr r0,=_stack\n\t mov sp, r0");
    regSet();
}

static inline void regSet()
{
    volatile uint32_t *entry = (uint32_t *)0x1FFFFFF8;

    *((volatile uint32_t*)0x10202240) = BRIGHTNESS;
    *((volatile uint32_t*)0x10202A40) = BRIGHTNESS;

    // Reset the entry
    *entry = 0;

    // Wait for entry to be set
    while(!*entry);
   
    // Jump
    ((void (*)())*entry)();
}
