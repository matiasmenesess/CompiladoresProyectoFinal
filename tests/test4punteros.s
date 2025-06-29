.data
print_fmt: .string "%ld\n"
.text
.globl main
.globl cambiar_valor
cambiar_valor:
    pushq %rbp
    movq %rsp, %rbp
    movq $100, %rax
    pushq %rax
