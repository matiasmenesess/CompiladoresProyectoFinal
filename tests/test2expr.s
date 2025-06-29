.data
print_fmt: .string "%ld\n"
.text
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp
# Cantidad de globales: 0
    movq $10, %rax
    movq %rax, -8(%rbp)  # a
    movq $2, %rax
    movq %rax, -16(%rbp)  # b
    movq $4, %rax
    movq %rax, -24(%rbp)  # c
    movq -8(%rbp), %rax  # a
    pushq %rax
    movq -16(%rbp), %rax  # b
    movq %rax, %rcx
    popq %rax
    addq %rcx, %rax
    pushq %rax
    movq -24(%rbp), %rax  # c
    movq %rax, %rcx
    popq %rax
    cqo
    idivq %rcx
    movq %rax, -32(%rbp)  # y
.section .rodata
printf_fmt_0: .string "Resultado: %d\n"
.text
    leaq printf_fmt_0(%rip), %rdi
    movq -32(%rbp), %rax  # y
    movq %rax, %rsi
    movl $0, %eax
    call printf
    movq $0, %rax
    leave
    ret
.section .note.GNU-stack,"",@progbits
