.data
print_fmt: .string "%ld\n"
.text
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp
#offset calculado de -8 para la variable x
#offset calculado de -16 para la variable y
    movq $1, %rax
    movq %rax, -8(%rbp)  # x
    movq $0, %rax
    movq %rax, -16(%rbp)  # y
# Cargando valor de x 0 -1
    movq -8(%rbp), %rax  # x
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
# Cargando valor de y 0 -1
    movq -16(%rbp), %rax  # y
    pushq %rax
    movq $0, %rax
    movq %rax, %rcx
    popq %rax
    # Operación binaria: ==
    cmpq %rcx, %rax
    movl $0, %eax
    sete %al
    movzbq %al, %rax
    movq %rax, %rcx
    popq %rax
    # Operación binaria: &&
    testq %rax, %rax
    jz .Lfalse1
    testq %rcx, %rcx
    movl $1, %eax
    jnz .Lend2
.Lfalse1:
    movl $0, %eax
.Lend2:
    testq %rax, %rax
    jz .Lelse2
.section .rodata
printf_fmt_0: .string "Ambas condiciones son verdaderas\n"
.text
    leaq printf_fmt_0(%rip), %rdi
    movl $0, %eax
    call printf
.Lelse2:
    movq $0, %rax
    leave
    ret
.section .note.GNU-stack,"",@progbits
