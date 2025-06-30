.data
print_fmt: .string "%ld\n"
.text
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp
#offset calculado de -8 para la variable x
#offset calculado de -16 para la variable ptr
    movq $50, %rax
    movq %rax, -8(%rbp)  # x
    movq $0, -16(%rbp)  # NULL para puntero
# Cargando valor de x 0 -1
    movq -8(%rbp), %rax  # x
    leaq -8(%rbp), %rax  # &x
    pushq %rax
    popq %rax
    movq %rax, -16(%rbp)  # guardar en local ptr
.section .rodata
printf_fmt_0: .string "El valor de x es: %d\n"
.text
    leaq printf_fmt_0(%rip), %rdi
# Cargando valor de ptr 0 -1
    movq -16(%rbp), %rax  # ptr
    movq (%rax), %rax  # *ptr
    movq %rax, %rsi
    movl $0, %eax
    call printf
    movq $0, %rax
    leave
    ret
.section .note.GNU-stack,"",@progbits
