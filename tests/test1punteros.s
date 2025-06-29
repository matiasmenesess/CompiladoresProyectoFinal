.data
print_fmt: .string "%ld\n"
.text
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp
# Cantidad de globales: 0
    movq $50, %rax
    movq %rax, -8(%rbp)  # x
    movq $0, -16(%rbp)  # NULL para puntero
    movq -8(%rbp), %rax  # x
    leaq -8(%rbp), %rax  # &x
    pushq %rax
    popq %rax
    movq %rax, -16(%rbp)  # ptr
.section .rodata
printf_fmt_0: .string "El valor de x es: %d\n"
.text
    leaq printf_fmt_0(%rip), %rdi
    movq -16(%rbp), %rax  # ptr
    movq (%rax), %rax  # *ptr
    movq %rax, %rsi
    movl $0, %eax
    call printf
    movq $0, %rax
    leave
    ret
.section .note.GNU-stack,"",@progbits
