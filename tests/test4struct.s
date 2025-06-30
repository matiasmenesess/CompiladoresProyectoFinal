.data
print_fmt: .string "%ld\n"
# Miembro de estructura: x (tipo: int, offset: 0, tamaño: 4)
# Miembro de estructura: y (tipo: int, offset: 8, tamaño: 4)
#   y : offset 8
#   x : offset 0
.text
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp
#offset calculado de -16 para la variable p
    movq $0, -16(%rbp)  # Inicializar a 0
    movq $5, %rax
    pushq %rax
    movq -16(%rbp), %rax  # x de struct local
    pushq %rax
    movq $2, %rax
    movq %rax, %rcx
    popq %rax
    # Operación binaria: *
    imulq %rcx, %rax
    pushq %rax
.section .rodata
printf_fmt_0: .string "p.y deberia ser 10: %d\n"
.text
    leaq printf_fmt_0(%rip), %rdi
    movq -8(%rbp), %rax  # y de struct local
    movq %rax, %rsi
    movl $0, %eax
    call printf
    movq $0, %rax
    leave
    ret
.section .note.GNU-stack,"",@progbits
