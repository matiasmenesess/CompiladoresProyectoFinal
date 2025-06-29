.data
print_fmt: .string "%ld\n"
.data
resta: .quad 0
.text
.data
maximo: .quad 0
.text
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
    subq $8, %rsp
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
    movl $0, %eax
    leave
    ret
.section .note.GNU-stack,"",@progbits
