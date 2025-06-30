.data
print_fmt: .string "%ld\n"
.text
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp
#offset calculado de -8 para la variable a
#offset calculado de -16 para la variable b
    movq $1, %rax
    movl %eax, -8(%rbp)  # a
    # Padding de 4 bytes para alineación
    movq $0, %rax
    movl %eax, -16(%rbp)  # b
    # Padding de 4 bytes para alineación
    movq -8(%rbp), %rax  # a
    pushq %rax
    movq $1, %rax
    movq %rax, %rcx
    popq %rax
    # Operación binaria: ==
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
    # Operación binaria: ==
    cmpq %rcx, %rax
    movl $0, %eax
    sete %al
    movzbq %al, %rax
    movq %rax, %rcx
    popq %rax
    # Operación binaria: ||
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
.section .note.GNU-stack,"",@progbits
