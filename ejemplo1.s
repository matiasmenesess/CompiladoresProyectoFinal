.data
print_fmt: .string "%ld\n"
.text
.globl main
main:
 pushq %rbp
 movq %rsp, %rbp
 subq $16, %rsp
# Declarando variable: x en offset -8
# Declarando variable: y en offset -16
 movq $42, %rax
    movq %rax, -8(%rbp) # x
# Cargando valor de x 0 -1
 movq -8(%rbp), %rax # x
    movq %rax, %rdx
 movq $8, %rax
    addq %rdx, %rax
    movq %rax, -16(%rbp) # y
.section .rodata
printf_fmt_0: .string "hola\n"
.text
    pushq %rbp # salvar frame pointer para alineación
    leaq printf_fmt_0(%rip), %rdi
    xorq %rax, %rax # 0 registros vectoriales usados
    call printf@PLT
    popq %rbp # restaurar frame pointer
 movq $0, %rax
    leave
    ret
.section .note.GNU-stack,"",@progbits
