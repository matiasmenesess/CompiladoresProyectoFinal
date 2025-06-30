.data
print_fmt: .string "%ld\n"
# Miembro de estructura: nombre (tipo: char, offset: 0, tamaño: 1)
# Miembro de estructura: edad (tipo: int, offset: 8, tamaño: 4)
# Estructura Persona (tamaño: 16 bytes)
#   edad : offset 8
#   nombre : offset 0
.text
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp
#offset calculado de -16 para la variable p
#offset se paso con -16
.section .rodata
string_1: .string "Juan"
.text
    leaq string_1(%rip), %rax
    movq %rax, -16(%rbp)  # Inicializando miembro nombre
    movq $20, %rax
    movq %rax, -8(%rbp)  # Inicializando miembro edad
.section .rodata
printf_fmt_0: .string "Persona: %s, %d anos\n"
.text
    leaq printf_fmt_0(%rip), %rdi
    movq -16(%rbp), %rax  # nombre de struct local
    movq %rax, %rsi
    movq -8(%rbp), %rax  # edad de struct local
    movq %rax, %rdx
    movl $0, %eax
    call printf
    movq $0, %rax
    leave
    ret
.section .note.GNU-stack,"",@progbits
