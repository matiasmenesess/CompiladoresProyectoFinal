.data
print_fmt: .string "%ld\n"
.text
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp
# Cantidad de globales: 0
    movq $0, -8(%rbp)  # Inicializar a 0
    movq $0, -16(%rbp)  # Inicializar a 0
    movq $1, %rax
    pushq %rax
    popq %rax
    movq %rax, -8(%rbp)  # x
    movq $10, %rax
    pushq %rax
    popq %rax
    movq %rax, -16(%rbp)  # y
    movq $20, %rax
    pushq %rax
    popq %rax
    movq %rax, -8(%rbp)  # x
.section .rodata
printf_fmt_0: .string " %d\n"
.text
    leaq printf_fmt_0(%rip), %rdi
    movq -8(%rbp), %rax  # x
    movq %rax, %rsi
    movl $0, %eax
    call printf
.section .rodata
printf_fmt_1: .string " %d\n"
.text
    leaq printf_fmt_1(%rip), %rdi
    movq -16(%rbp), %rax  # y
    movq %rax, %rsi
    movl $0, %eax
    call printf
    movq $0, %rax
    leave
    ret
.section .note.GNU-stack,"",@progbits
