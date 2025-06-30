.data
print_fmt: .string "%ld\n"
# Miembro de estructura: titulo (tipo: char, offset: 0, tamaño: 1)
# Miembro de estructura: anio (tipo: int, offset: 8, tamaño: 4)
#   anio : offset 8
#   titulo : offset 0
.text
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp
#offset calculado de -16 para la variable mi_libro
#offset se paso con -16
.section .rodata
string_1: .string "C Programming"
.text
    leaq string_1(%rip), %rax
    movq %rax, -16(%rbp)  # Inicializando miembro titulo
    movq $1978, %rax
    movq %rax, -8(%rbp)  # Inicializando miembro anio
.section .rodata
printf_fmt_0: .string "Libro: %s, Publicado en: %d\n"
.text
    leaq printf_fmt_0(%rip), %rdi
    movq -16(%rbp), %rax  # titulo de struct local
    movq %rax, %rsi
    movq -8(%rbp), %rax  # anio de struct local
    movq %rax, %rdx
    movl $0, %eax
    call printf
    movq $0, %rax
    leave
    ret
.section .note.GNU-stack,"",@progbits
