.data
print_fmt: .string "%ld\n"
.text
.globl main
.globl suma
suma:
    pushq %rbp
    movq %rsp, %rbp
# Registrando variable: a reg_index: 0 offset: 0 is_global: false is_reference: true
# Registrando variable: b reg_index: 1 offset: 0 is_global: false is_reference: false
# Cargando valor de a 1 0
    movq (%rdi), %rax  # Valor de* a
    movq %rax, %rcx
    incq %rcx
    movq %rcx, (%rdi)  # *ref++
# Cargando valor de a 1 0
    movq (%rdi), %rax  # Valor de* a
    leave
    ret
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp
#offset calculado de -8 para la variable a
#offset calculado de -16 para la variable b
#offset calculado de -24 para la variable resultado
    movq $10, %rax
    movq %rax, -8(%rbp)  # a
.section .rodata
printf_fmt_0: .string "Entero: %d, Caracter: %c\n"
.text
    leaq printf_fmt_0(%rip), %rdi
# Cargando valor de a 0 -1
    movq -8(%rbp), %rax  # a
    movq %rax, %rsi
    movq $97, %rax
    movq %rax, %rdx
    movl $0, %eax
    call printf
    movq $20, %rax
    movq %rax, -16(%rbp)  # b
    leaq -8(%rbp), %rax  # Dirección de a
    movq %rax, %rdi
# Cargando valor de b 0 -1
    movq -16(%rbp), %rax  # b
    movq %rax, %rsi
    call suma
    movq %rax, -24(%rbp)  # resultado
.section .rodata
printf_fmt_1: .string "La suma es: %d\n"
.text
    leaq printf_fmt_1(%rip), %rdi
# Cargando valor de a 0 -1
    movq -8(%rbp), %rax  # a
    movq %rax, %rsi
    movl $0, %eax
    call printf
    movq $0, %rax
    leave
    ret
.section .note.GNU-stack,"",@progbits
