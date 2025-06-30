.data
print_fmt: .string "%ld\n"
# Miembro de estructura: x (tipo: int, offset: 0, tamaño: 4)
# Miembro de estructura: y (tipo: int, offset: 8, tamaño: 4)
#   y : offset 8
#   x : offset 0
# Miembro de estructura: top_left (tipo: struct Punto, offset: 0, tamaño: 8)
# Miembro de estructura: ancho (tipo: int, offset: 8, tamaño: 4)
# Miembro de estructura: alto (tipo: int, offset: 16, tamaño: 4)
#   alto : offset 16
#   ancho : offset 8
#   top_left : offset 0
.text
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp
#offset calculado de -24 para la variable r
    movq $0, -24(%rbp)  # Inicializar a 0
    movq $0, %rax
    pushq %rax
    movq $0, %rax
    pushq %rax
    movq $100, %rax
    pushq %rax
.section .rodata
printf_fmt_0: .string "Rectangulo en (%d, %d)\n"
.text
    leaq printf_fmt_0(%rip), %rdi
    addq $8, %rax  # offset del miembro x
    movq (%rax), %rax
    movq %rax, %rsi
    addq $8, %rax  # offset del miembro y
    movq (%rax), %rax
    movq %rax, %rdx
    movl $0, %eax
    call printf
    movq $0, %rax
    leave
    ret
.section .note.GNU-stack,"",@progbits
