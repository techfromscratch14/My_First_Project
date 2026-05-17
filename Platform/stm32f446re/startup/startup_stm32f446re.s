.syntax unified
.cpu cortex-m4
.thumb

.global _estack
.global Reset_Handler

.extern main
.extern SystemInit

.section .isr_vector , "a", %progbits

.word _estack
.word Reset_Handler

.section .text

Reset_Handler:

    /* Initialize systemn */
    bl SystemInit

    /* Enter main application */
    bl main

LoopForeever :
    b LoopForeever

