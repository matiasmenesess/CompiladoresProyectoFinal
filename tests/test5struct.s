.data
print_fmt: .string "%ld\n"
.text
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp
# Cantidad de globales: 0
    movq $0, -8(%rbp)  # Inicializar a 0
    movq $10, %rax
    pushq %rax
