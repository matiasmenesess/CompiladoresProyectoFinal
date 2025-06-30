.data
print_fmt: .string "%ld\n"
.text
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
 # debug de init
    movq $0, %rax
    movl %eax, -8(%rbp)  # i
    # Padding de 4 bytes para alineación
.Lfor1:
# Cargando valor de i 0 -1
    movl -8(%rbp), %eax  # i
    pushq %rax
