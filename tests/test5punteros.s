.data
print_fmt: .string "%ld\n"
.text
.globl main
.globl suma10
suma10:
    pushq %rbp
    movq %rsp, %rbp
# Parámetro: n reg_index: 0 is_reference: false
# Cargando valor de n 0 0
 movq %rdi, %rax # Valor de n
    movq (%rax), %rax  # *ptr
    movq %rax, %rdx
 movq $10, %rax
    addq %rdx, %rax
 pushq %rax
# Cargando valor de n 0 0
 movq %rdi, %rax # Valor de n
 movq %rax, %rbx # guardar dirección
 popq %rax # recuperar valor a asignar
 movq %rax, (%rbx) # *ptr = valor
    leave
    ret
main:
 pushq %rbp
 movq %rsp, %rbp
 subq $32, %rsp
# Declarando variable: x en offset -8
# Declarando variable: y en offset -16
# Declarando variable: p en offset -24
# Declarando variable: q en offset -32
 movq $5, %rax
    movq %rax, -8(%rbp) # x
 movq $20, %rax
    movq %rax, -16(%rbp) # y
# Cargando valor de y 0 -1
 movq -16(%rbp), %rax # y
    leaq -16(%rbp), %rax  # &y
    movq %rax, -24(%rbp) # p
# Cargando valor de x 0 -1
 movq -8(%rbp), %rax # x
    leaq -8(%rbp), %rax  # &x
    movq %rax, -32(%rbp) # q
.section .rodata
printf_fmt_0: .string "Valor original de x: %d\n"
.text
    leaq printf_fmt_0(%rip), %rdi
# Cargando valor de x 0 -1
 movq -8(%rbp), %rax # x
    movq %rax, %rsi
    xorq %rax, %rax # 0 registros vectoriales usados
    call printf@PLT
.section .rodata
printf_fmt_1: .string "Valor original de y: %d\n"
.text
    leaq printf_fmt_1(%rip), %rdi
# Cargando valor de y 0 -1
 movq -16(%rbp), %rax # y
    movq %rax, %rsi
    xorq %rax, %rax # 0 registros vectoriales usados
    call printf@PLT
# Cargando valor de q 0 -1
 movq -32(%rbp), %rax # q
    movq (%rax), %rax  # *ptr
    movq %rax, %rdx
 movq $15, %rax
    addq %rdx, %rax
 pushq %rax
# Cargando valor de p 0 -1
 movq -24(%rbp), %rax # p
 movq %rax, %rbx # guardar dirección
 popq %rax # recuperar valor a asignar
 movq %rax, (%rbx) # *ptr = valor
# Cargando valor de q 0 -1
 movq -32(%rbp), %rax # q
    movq %rax, %rdi
    call suma10
.section .rodata
printf_fmt_2: .string "Nuevo valor de x: %d\n"
.text
    leaq printf_fmt_2(%rip), %rdi
# Cargando valor de x 0 -1
 movq -8(%rbp), %rax # x
    movq %rax, %rsi
    xorq %rax, %rax # 0 registros vectoriales usados
    call printf@PLT
.section .rodata
printf_fmt_3: .string "Nuevo valor de y: %d\n"
.text
    leaq printf_fmt_3(%rip), %rdi
# Cargando valor de y 0 -1
 movq -16(%rbp), %rax # y
    movq %rax, %rsi
    xorq %rax, %rax # 0 registros vectoriales usados
    call printf@PLT
 movq $0, %rax
    leave
    ret
.section .note.GNU-stack,"",@progbits
