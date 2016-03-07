.section .text.start
.align 4
.arm
.global _start
_start:
_init:
	@ Change the stack pointer
	mov sp, #0x27000000

    bl main

.die:
    b .die