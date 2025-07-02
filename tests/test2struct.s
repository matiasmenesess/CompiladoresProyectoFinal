.data
print_fmt: .string "%ld\n"
# Miembro: titulo tipo: char offset: 0 tamaño: 8
# Miembro: anio tipo: int offset: 8 tamaño: 8
# Struct Libro tamaño total: 16
# Campo anio: offset 8
# Campo titulo: offset 0
.text
.globl main
main:
 pushq %rbp
 movq %rsp, %rbp
 subq $16, %rsp
# Declarando variable: mi_libro en offset -16
# Inicializando struct en offset -16
.section .rodata
string_1: .string "C Programming"
.text
 leaq string_1(%rip), %rax
    movq %rax, -16(%rbp) # titulo
 movq $1978, %rax
    movq %rax, -8(%rbp) # anio
.section .rodata
printf_fmt_0: .string "Libro: %s, Publicado en: %d\n"
.text
    leaq printf_fmt_0(%rip), %rdi
 movq -16(%rbp), %rax # titulo de struct local
    movq %rax, %rsi
 movq -8(%rbp), %rax # anio de struct local
    movq %rax, %rdx
    xorq %rax, %rax # 0 registros vectoriales usados
    call printf@PLT
 movq $0, %rax
    leave
    ret
.section .note.GNU-stack,"",@progbits
