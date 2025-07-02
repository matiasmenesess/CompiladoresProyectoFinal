.data
print_fmt: .string "%ld\n"
# Miembro: nombre tipo: char offset: 0 tamaño: 8
# Miembro: edad tipo: int offset: 8 tamaño: 8
# Struct Persona tamaño total: 16
# Campo edad: offset 8
# Campo nombre: offset 0
.text
.globl main
main:
 pushq %rbp
 movq %rsp, %rbp
 subq $48, %rsp
# Declarando variable: mensaje en offset -8
# Declarando variable: x en offset -16
# Declarando variable: ptr en offset -24
# Declarando variable: p en offset -40
.section .rodata
string_1: .string "Hola mundo"
.text
 leaq string_1(%rip), %rax
    movq %rax, -8(%rbp) # mensaje
 movq $5, %rax
    movq %rax, %rdx
 movq $1, %rax
    movq %rax, %rcx
    movq %rdx, %rax
    cqo
    idivq %rcx
    movq %rax, -16(%rbp) # x
# Cargando valor de x 0 -1
 movq -16(%rbp), %rax # x
    leaq -16(%rbp), %rax  # &x
    movq %rax, -24(%rbp) # ptr
# Inicializando struct en offset -40
.section .rodata
string_2: .string "Juan"
.text
 leaq string_2(%rip), %rax
    movq %rax, -40(%rbp) # nombre
 movq $20, %rax
    movq %rax, -32(%rbp) # edad
.section .rodata
printf_fmt_0: .string "Mensaje: %s\n"
.text
    leaq printf_fmt_0(%rip), %rdi
# Cargando valor de mensaje 0 -1
 movq -8(%rbp), %rax # mensaje
    movq %rax, %rsi
    xorq %rax, %rax # 0 registros vectoriales usados
    call printf@PLT
.section .rodata
printf_fmt_1: .string "Persona: %s, %d anos\n"
.text
    leaq printf_fmt_1(%rip), %rdi
 movq -40(%rbp), %rax # nombre de struct local
    movq %rax, %rsi
 movq -32(%rbp), %rax # edad de struct local
    movq %rax, %rdx
    xorq %rax, %rax # 0 registros vectoriales usados
    call printf@PLT
 movq $0, %rax
    leave
    ret
.section .note.GNU-stack,"",@progbits
