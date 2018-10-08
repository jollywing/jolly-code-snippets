    .text
    .section .rodata
    .LC0:
    .string "hello, world!"
    .text
    .global main
    .type main, @function
main:
    .cfi_startproc
    leaq .LC0(%rip), %rdi
    call puts@PLT
    movl $0, %eax
    ret
    .cfi_endproc
