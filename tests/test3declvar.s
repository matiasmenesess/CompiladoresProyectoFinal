.data
print_fmt: .string "%ld\n"
.text
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp
#offset calculado de -8 para la variable x
    movb $0, -8(%rbp)  # Inicializar a 0
    # Padding de 7 bytes para alineación
    movq $120, %rax
    pushq %rax
    popq %rax
    movq %rax, -8(%rbp)  # guardar en local x
.section .rodata
printf_fmt_0: .string " %d\n"
.text
    leaq printf_fmt_0(%rip), %rdi
# Cargando valor de x 0 -1
    movq -8(%rbp), %rax  # x
    movq %rax, %rsi
    movl $0, %eax
    call printf
    movq $0, %rax
    leave
    ret
.section .note.GNU-stack,"",@progbits
