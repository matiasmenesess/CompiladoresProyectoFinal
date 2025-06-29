.data
print_fmt: .string "%ld\n"
.text
.globl main
.globl cambiar_valor
cambiar_valor:
    pushq %rbp
    movq %rsp, %rbp
    pushq %rbx
    pushq %r12
    pushq %r13
    pushq %r14
    pushq %r15
