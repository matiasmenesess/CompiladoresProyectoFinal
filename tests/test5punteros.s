.data
print_fmt: .string "%ld\n"
.text
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp
#offset calculado de -8 para la variable y
#offset calculado de -16 para la variable p
    movq $20, %rax
    movq %rax, -8(%rbp)  # y
# Cargando valor de y 0 -1
    movq -8(%rbp), %rax  # y
    leaq -8(%rbp), %rax  # &y
    movq %rax, -16(%rbp)  # p
.section .rodata
printf_fmt_0: .string "Valor original de y: %d\n"
.text
    leaq printf_fmt_0(%rip), %rdi
# Cargando valor de y 0 -1
    movq -8(%rbp), %rax  # y
    movq %rax, %rsi
    movl $0, %eax
    call printf
    movq $30, %rax
    pushq %rax
.section .rodata
printf_fmt_1: .string "Nuevo valor de y: %d\n"
.text
    leaq printf_fmt_1(%rip), %rdi
# Cargando valor de y 0 -1
    movq -8(%rbp), %rax  # y
    movq %rax, %rsi
    movl $0, %eax
    call printf
    movq $0, %rax
    leave
    ret
.section .note.GNU-stack,"",@progbits
