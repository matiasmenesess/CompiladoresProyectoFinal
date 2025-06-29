.data
print_fmt: .string "%ld\n"
.text
.globl main
.globl factorial
factorial:
    pushq %rbp
    movq %rsp, %rbp
    pushq %rbx
    pushq %r12
    pushq %r13
    pushq %r14
    pushq %r15
