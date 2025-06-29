.data
print_fmt: .string "%ld\n"
.text
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp
# Cantidad de globales: 0
    movq $20, %rax
    movq %rax, -8(%rbp)  # y
    movq -8(%rbp), %rax  # y
    leaq -8(%rbp), %rax  # &y
    movq %rax, -16(%rbp)  # p
.section .rodata
printf_fmt_0: .string "Valor original de y: %d\n"
.text
    leaq printf_fmt_0(%rip), %rdi
    movq -8(%rbp), %rax  # y
    movq %rax, %rsi
    movl $0, %eax
    call printf
    movq $30, %rax
    pushq %rax
