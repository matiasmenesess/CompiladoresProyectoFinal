.data
print_fmt: .string "%ld\n"
.text
.globl main
main:
 pushq %rbp
 movq %rsp, %rbp
 subq $16, %rsp
# Declarando variable: y en offset -8
# Declarando variable: p en offset -16
 movq $20, %rax
    movq %rax, -8(%rbp) # y
# Cargando valor de y 0 -1
 movq -8(%rbp), %rax # y
    leaq -8(%rbp), %rax  # &y
    movq %rax, -16(%rbp) # p
.section .rodata
printf_fmt_0: .string "Valor original de y: %d\n"
.text
    leaq printf_fmt_0(%rip), %rdi
# Cargando valor de y 0 -1
 movq -8(%rbp), %rax # y
    movq %rax, %rsi
    xorq %rax, %rax # 0 registros vectoriales usados
    call printf@PLT
 movq $30, %rax
 pushq %rax
# Cargando valor de p 0 -1
 movq -16(%rbp), %rax # p
 movq %rax, %rbx # guardar dirección
 popq %rax # recuperar valor a asignar
 movq %rax, (%rbx) # *ptr = valor
.section .rodata
printf_fmt_1: .string "Nuevo valor de y: %d\n"
.text
    leaq printf_fmt_1(%rip), %rdi
# Cargando valor de y 0 -1
 movq -8(%rbp), %rax # y
    movq %rax, %rsi
    xorq %rax, %rax # 0 registros vectoriales usados
    call printf@PLT
 movq $0, %rax
    leave
    ret
.section .note.GNU-stack,"",@progbits
