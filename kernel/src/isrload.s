
# This file contains the actual assembly ISRs which each go on to invoke
# isr_load() (also in this file) which in turn invokes isr_main() (found
# in isr.c). If the interrupt is an IRQ, isr_main will go on to invoke
# a function defined irq_handlers.h.

## setup isrs that don't pop error codes themselves
.irp    param,0,1,2,3,4,5,6,7,9,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47
.global int\param
int\param:
    cli
    push $0         # dummy error code
    push $\param
    jmp isr_load
.endr

## setup isrs that do pop error codes themselves
.irp    param,8,10,11,12,13,14
.global int\param
int\param:
    cli
    push $\param
    jmp isr_load
.endr


isr_load:
    pusha
    push %ds
    push %es
    push %fs
    push %gs
    mov $0x10, %ax  # Load KDS descriptor
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    mov %esp, %eax
    push %eax
    
    # preserve eip through indirect call
    mov $isr_main, %eax
    call *%eax
    
    pop %eax
    pop %gs
    pop %fs
    pop %es
    pop %ds
    popa
    add $8, %esp # Cleans up the pushed error code and pushed ISR number
    iret           # pops CS & EIP & EFLAGS & SS & ESP
