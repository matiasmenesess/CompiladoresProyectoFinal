.data
print_fmt: .string "%ld\n"
.text
.globl main
.globl cambiar_valor
cambiar_valor:
    pushq %rbp
    movq %rsp, %rbp
# Registrando variable: num reg_index: 0 offset: 0 is_global: false is_reference: false
    movq $100, %rax
    pushq %rax
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp
#offset calculado de -8 para la variable mi_numero
    movq $10, %rax
    movq %rax, -8(%rbp)  # mi_numero
.section .rodata
printf_fmt_0: .string "Valor antes de la funcion: %d\n"
.text
    leaq printf_fmt_0(%rip), %rdi
# Cargando valor de mi_numero 0 -1
    movq -8(%rbp), %rax  # mi_numero
    movq %rax, %rsi
    movl $0, %eax
    call printf
# Cargando valor de mi_numero 0 -1
    movq -8(%rbp), %rax  # mi_numero
    leaq -8(%rbp), %rax  # &mi_numero
    movq %rax, %rdi
    call cambiar_valor
.section .rodata
printf_fmt_1: .string "Valor despues de la funcion: %d\n"
.text
    leaq printf_fmt_1(%rip), %rdi
# Cargando valor de mi_numero 0 -1
    movq -8(%rbp), %rax  # mi_numero
    movq %rax, %rsi
    movl $0, %eax
    call printf
    movq $0, %rax
    leave
    ret
.section .note.GNU-stack,"",@progbits
