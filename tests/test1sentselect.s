.data
print_fmt: .string "%ld\n"
.text
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp
    movq $1, %rax
    movq %rax, -8(%rbp)  # a
    movq $0, %rax
    movq %rax, -16(%rbp)  # b
    movq -8(%rbp), %rax  # a
    pushq %rax
    movq $1, %rax
    movq %rax, %rcx
    popq %rax
    cmpq %rcx, %rax
    movl $0, %eax
    sete %al
    movzbq %al, %rax
    pushq %rax
    movq -16(%rbp), %rax  # b
    pushq %rax
    movq $1, %rax
    movq %rax, %rcx
    popq %rax
    cmpq %rcx, %rax
    movl $0, %eax
    sete %al
    movzbq %al, %rax
    movq %rax, %rcx
    popq %rax
    testq %rax, %rax
    jnz .Ltrue1
    testq %rcx, %rcx
    movl $0, %eax
    jz .Lend2
.Ltrue1:
    movl $1, %eax
.Lend2:
    testq %rax, %rax
    jz .Lelse2
.section .rodata
printf_fmt_0: .string "Al menos una condicion es verdadera\n"
.text
    leaq printf_fmt_0(%rip), %rdi
    movl $0, %eax
    call printf
.Lelse2:
    movq $0, %rax
    leave
    ret
    movl $0, %eax
    leave
    ret
.section .note.GNU-stack,"",@progbits
