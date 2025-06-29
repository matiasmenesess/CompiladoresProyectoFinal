.data
print_fmt: .string "%ld\n"
.text
.globl main
.globl suma
suma:
    pushq %rbp
    movq %rsp, %rbp
    movq (%rdi), %rax  # Valor de a
    pushq %rax
    movq %rsi, %rax  # Valor de b
    movq %rax, %rcx
    popq %rax
    addq %rcx, %rax
    pushq %rax
    popq %rax
    movq %rax, (%rdi)  # a (por referencia)
    movq (%rdi), %rax  # Valor de a
    leave
    ret
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $24, %rsp
    movq $22, %rax
    movq %rax, -8(%rbp)  # a
    movq $3, %rax
    movq %rax, -16(%rbp)  # b
    leaq -8(%rbp), %rax  # Dirección de a
    movq %rax, %rdi
    movq -16(%rbp), %rax  # b
    movq %rax, %rsi
    call suma
    movq %rax, -24(%rbp)  # resultado
.section .rodata
printf_fmt_0: .string "La suma es: %d\n"
.text
    leaq printf_fmt_0(%rip), %rdi
    movq -8(%rbp), %rax  # a
    movq %rax, %rsi
    movl $0, %eax
    call printf
    movq $0, %rax
    leave
    ret
.section .note.GNU-stack,"",@progbits
