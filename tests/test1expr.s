.data
print_fmt: .string "%ld\n"
.text
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp
#offset calculado de -8 para la variable x
    movq $0, -8(%rbp)  # Inicializar a 0
    movq $5, %rax
    pushq %rax
    movq $3, %rax
    pushq %rax
    movq $2, %rax
    movq %rax, %rcx
    popq %rax
    # Operación binaria: *
    imulq %rcx, %rax
    movq %rax, %rcx
    popq %rax
    # Operación binaria: +
    addq %rcx, %rax
    pushq %rax
    popq %rax
    movq %rax, -8(%rbp)  # guardar en local x
.section .rodata
printf_fmt_0: .string "Resultado: %d\n"
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
