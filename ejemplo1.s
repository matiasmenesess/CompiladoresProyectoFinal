.data
print_fmt: .string "%ld\n"
.text
.globl main
.globl suma
suma:
    pushq %rbp
    movq %rsp, %rbp
    movq %rdi, -8(%rbp)
    movq %rsi, -16(%rbp)
    movq -8(%rbp), %rax  # a
    pushq %rax
    movq -16(%rbp), %rax  # b
    movq %rax, %rcx
    popq %rax
    addq %rcx, %rax
    leave
    ret
    leave
    ret
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $24, %rsp
    movq $5, %rax
    movq %rax, -8(%rbp)  # a
    movq $3, %rax
    movq %rax, -16(%rbp)  # b
    movq -8(%rbp), %rax  # a
    movq %rax, %rdi
    movq -16(%rbp), %rax  # b
    movq %rax, %rsi
    call suma
    movq %rax, -24(%rbp)  # resultado
.section .rodata
printf_fmt_0: .string "La suma es: %d\n"
.text
    leaq printf_fmt_0(%rip), %rdi
    movq -24(%rbp), %rax  # resultado
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
