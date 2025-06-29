.data
print_fmt: .string "%ld\n"
.text
.globl main
.globl factorial
factorial:
    pushq %rbp
    movq %rsp, %rbp
    movq %rdi, -8(%rbp)
    movq -8(%rbp), %rax  # n
    pushq %rax
    movq $1, %rax
    movq %rax, %rcx
    popq %rax
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
    movq -8(%rbp), %rax  # n
    pushq %rax
    movq -8(%rbp), %rax  # n
    pushq %rax
    movq $1, %rax
    movq %rax, %rcx
    popq %rax
    subq %rcx, %rax
    movq %rax, %rdi
    call factorial
    movq %rax, %rcx
    popq %rax
    imulq %rcx, %rax
    leave
    ret
    leave
    ret
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $8, %rsp
    movq $5, %rax
    movq %rax, %rdi
    call factorial
    movq %rax, -8(%rbp)  # f
.section .rodata
printf_fmt_0: .string "Factorial de 5 es: %d\n"
.text
    leaq printf_fmt_0(%rip), %rdi
    movq -8(%rbp), %rax  # f
    movq %rax, %rsi
    movl $0, %eax
    call printf
    movq $0, %rax
    leave
    ret
    movl $0, %eax
    leave
    ret
.section .note.GNU-stack,"",@progbits
