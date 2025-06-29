.data
print_fmt: .string "%ld\n"
.text
.globl main
.globl cambiar_valor
cambiar_valor:
    pushq %rbp
    movq %rsp, %rbp
    movq %rdi, -8(%rbp)
    movq $100, %rax
    pushq %rax
