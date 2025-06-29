.data
print_fmt: .string "%ld\n"
.text
.globl main
.globl suma
suma:
    pushq %rbp
    movq %rsp, %rbp
    movq (%rdi), %rax  # Valor de a
    pushq %rax
    movq %rsi, %rax  # Valor de b
    movq %rax, %rcx
    popq %rax
    addq %rcx, %rax
    pushq %rax
    popq %rax
    movq %rax, (%rdi)  # a (por referencia)
    movq (%rdi), %rax  # Valor de a
    leave
    ret
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp
# Cantidad de globales: 0
    movq $10, %rax
    movq %rax, -8(%rbp)  # a
    movq $30, %rax
    movq %rax, -16(%rbp)  # c
.section .rodata
printf_fmt_0: .string "Entero: %d, Caracter: %c\n"
.text
    leaq printf_fmt_0(%rip), %rdi
    movq -16(%rbp), %rax  # c
    movq %rax, %rsi
    movq $99, %rax
    movq %rax, %rdx
    movl $0, %eax
    call printf
    movq $20, %rax
    movq %rax, -24(%rbp)  # b
    leaq -8(%rbp), %rax  # Dirección de a
    movq %rax, %rdi
    movq -24(%rbp), %rax  # b
    movq %rax, %rsi
    call suma
    movq %rax, -32(%rbp)  # resultado
.section .rodata
printf_fmt_1: .string "La suma es: %d\n"
.text
    leaq printf_fmt_1(%rip), %rdi
    movq -8(%rbp), %rax  # a
    movq %rax, %rsi
    movl $0, %eax
    call printf
    movq $0, %rax
    leave
    ret
.section .note.GNU-stack,"",@progbits
