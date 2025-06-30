.data
print_fmt: .string "%ld\n"
.text
.globl main
.globl factorial
factorial:
    pushq %rbp
    movq %rsp, %rbp
# Registrando variable: n reg_index: 0 offset: 0 is_global: false is_reference: false
# Cargando valor de n 0 0
    movq %rdi, %rax  # Valor de n
    pushq %rax
    movq $1, %rax
    movq %rax, %rcx
    popq %rax
    # Operación binaria: <=
    cmpq %rcx, %rax
    movl $0, %eax
    setle %al
    movzbq %al, %rax
    testq %rax, %rax
    jz .Lelse2
    movq $1, %rax
    leave
    ret
.Lelse2:
# Cargando valor de n 0 0
    movq %rdi, %rax  # Valor de n
    pushq %rax
# Cargando valor de n 0 0
    movq %rdi, %rax  # Valor de n
    pushq %rax
    movq $1, %rax
    movq %rax, %rcx
    popq %rax
    # Operación binaria: -
    subq %rcx, %rax
    movq %rax, %rdi
    call factorial
    movq %rax, %rcx
    popq %rax
    # Operación binaria: *
    imulq %rcx, %rax
    leave
    ret
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp
#offset calculado de -8 para la variable f
    movq $5, %rax
    movq %rax, %rdi
    call factorial
    movq %rax, -8(%rbp)  # f
.section .rodata
printf_fmt_0: .string "Factorial de 5 es: %d\n"
.text
    leaq printf_fmt_0(%rip), %rdi
# Cargando valor de f 0 -1
    movq -8(%rbp), %rax  # f
    movq %rax, %rsi
    movl $0, %eax
    call printf
    movq $0, %rax
    leave
    ret
.section .note.GNU-stack,"",@progbits
