.data
print_fmt: .string "%ld\n"
.text
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp
#offset calculado de -8 para la variable a
#offset calculado de -16 para la variable b
#offset calculado de -24 para la variable c
#offset calculado de -32 para la variable y
    movq $10, %rax
    movq %rax, -8(%rbp)  # a
    movq $2, %rax
    movq %rax, -16(%rbp)  # b
    movq $4, %rax
    movq %rax, -24(%rbp)  # c
# Cargando valor de a 0 -1
    movq -8(%rbp), %rax  # a
    pushq %rax
# Cargando valor de b 0 -1
    movq -16(%rbp), %rax  # b
    movq %rax, %rcx
    popq %rax
    # Operación binaria: +
    addq %rcx, %rax
    pushq %rax
# Cargando valor de c 0 -1
    movq -24(%rbp), %rax  # c
    movq %rax, %rcx
    popq %rax
    # Operación binaria: /
    cqo
    idivq %rcx
    movq %rax, -32(%rbp)  # y
.section .rodata
printf_fmt_0: .string "Resultado: %d\n"
.text
    leaq printf_fmt_0(%rip), %rdi
# Cargando valor de y 0 -1
    movq -32(%rbp), %rax  # y
    movq %rax, %rsi
    movl $0, %eax
    call printf
    movq $0, %rax
    leave
    ret
.section .note.GNU-stack,"",@progbits
