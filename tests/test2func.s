.data
print_fmt: .string "%ld\n"
.text
.globl main
.globl llenar
llenar:
    pushq %rbp
    movq %rsp, %rbp
    movq %rdi, -8(%rbp)
    movq %rsi, -16(%rbp)
