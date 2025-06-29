.data
print_fmt: .string "%ld\n"
resta: .quad 0
maximo: .quad 0
.text
.globl main
.globl suma
suma:
    pushq %rbp
    movq %rsp, %rbp
    movq %rdi, %rax  # Valor de a
    pushq %rax
    movq %rsi, %rax  # Valor de b
    movq %rax, %rcx
    popq %rax
    addq %rcx, %rax
    leave
    ret
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp
# Cantidad de globales: 2
# Variablles globales inicializadasresta
    movq $11, %rax
    negq %rax
    movq %rax, resta(%rip)
# Variablles globales inicializadasmaximo
    movq $100, %rax
    pushq %rax
    movq $2, %rax
    movq %rax, %rcx
    popq %rax
    cqo
    idivq %rcx
    movq %rax, maximo(%rip)
    movq $5, %rax
    movq %rax, %rdi
    movq $3, %rax
    movq %rax, %rsi
    call suma
    movq %rax, -8(%rbp)  # resultado
.section .rodata
printf_fmt_0: .string "La suma es: %d\n"
.text
    leaq printf_fmt_0(%rip), %rdi
    movq -8(%rbp), %rax  # resultado
    movq %rax, %rsi
    movl $0, %eax
    call printf
    movq $0, %rax
    leave
    ret
.section .note.GNU-stack,"",@progbits
