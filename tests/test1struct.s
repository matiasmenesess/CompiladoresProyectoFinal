.data
print_fmt: .string "%ld\n"
# Miembro de estructura: nombre (tipo: char, offset: 0, tamaño: 1)
# Miembro de estructura: edad (tipo: int, offset: 8, tamaño: 4)
#   edad : offset 8
#   nombre : offset 0
.text
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $48, %rsp
#offset calculado de -8 para la variable mensaje
#offset calculado de -16 para la variable x
#offset calculado de -24 para la variable ptr
#offset calculado de -40 para la variable p
.section .rodata
string_1: .string "Hola mundo!"
.text
    leaq string_1(%rip), %rax
    movq %rax, -8(%rbp)  # mensaje
    # Padding de 7 bytes para alineación
    movq $5, %rax
    pushq %rax
    movq $1, %rax
    movq %rax, %rcx
    popq %rax
    # Operación binaria: /
    cqo
    idivq %rcx
    movq %rax, -16(%rbp)  # x
# Cargando valor de x 0 -1
    movq -16(%rbp), %rax  # x
    leaq -16(%rbp), %rax  # &x
    movq %rax, -24(%rbp)  # ptr
#offset se paso con -40
.section .rodata
string_2: .string "Juan"
.text
    leaq string_2(%rip), %rax
    movq %rax, -40(%rbp)  # Inicializando miembro nombre
    movq $20, %rax
    movq %rax, -32(%rbp)  # Inicializando miembro edad
.section .rodata
printf_fmt_0: .string "Mensaje: %s\n"
.text
    leaq printf_fmt_0(%rip), %rdi
# Cargando valor de mensaje 0 -1
    movq -8(%rbp), %rax  # mensaje
    movq %rax, %rsi
    movl $0, %eax
    call printf
.section .rodata
printf_fmt_1: .string "Persona: %s, %d anos\n"
.text
    leaq printf_fmt_1(%rip), %rdi
    movq -40(%rbp), %rax  # nombre de struct local
    movq %rax, %rsi
    movq -32(%rbp), %rax  # edad de struct local
    movq %rax, %rdx
    movl $0, %eax
    call printf
    movq $0, %rax
    leave
    ret
.section .note.GNU-stack,"",@progbits
