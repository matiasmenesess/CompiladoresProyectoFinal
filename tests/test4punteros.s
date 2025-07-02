.data
print_fmt: .string "%ld\n"
.text
.globl main
.globl cambiar_valor
cambiar_valor:
    pushq %rbp
    movq %rsp, %rbp
# Parámetro: num reg_index: 0 is_reference: false
 movq $100, %rax
 pushq %rax
# Cargando valor de num 0 0
 movq %rdi, %rax # Valor de num
 movq %rax, %rbx # guardar dirección
 popq %rax # recuperar valor a asignar
 movq %rax, (%rbx) # *ptr = valor
    leave
    ret
main:
 pushq %rbp
 movq %rsp, %rbp
 subq $16, %rsp
# Declarando variable: mi_numero en offset -8
 movq $10, %rax
    movq %rax, -8(%rbp) # mi_numero
.section .rodata
printf_fmt_0: .string "Valor antes de la funcion: %d\n"
.text
    leaq printf_fmt_0(%rip), %rdi
# Cargando valor de mi_numero 0 -1
 movq -8(%rbp), %rax # mi_numero
    movq %rax, %rsi
    xorq %rax, %rax # 0 registros vectoriales usados
    call printf@PLT
# Cargando valor de mi_numero 0 -1
 movq -8(%rbp), %rax # mi_numero
    leaq -8(%rbp), %rax  # &mi_numero
    movq %rax, %rdi
    call cambiar_valor
.section .rodata
printf_fmt_1: .string "Valor despues de la funcion: %d\n"
.text
    leaq printf_fmt_1(%rip), %rdi
# Cargando valor de mi_numero 0 -1
 movq -8(%rbp), %rax # mi_numero
    movq %rax, %rsi
    xorq %rax, %rax # 0 registros vectoriales usados
    call printf@PLT
 movq $0, %rax
    leave
    ret
.section .note.GNU-stack,"",@progbits
