.data
print_fmt: .string "%ld\n"
.text
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp
#offset calculado de -8 para la variable x
    movl $0, -8(%rbp)  # Inicializar a 0
    movq $10, %rax
    pushq %rax
    popq %rax
    movq %rax, -8(%rbp)  # guardar en local x
    movq $0, %rax
    movl %eax, -4(%rbp)  # i
.Lfor1:
# Cargando valor de i 0 -1
    movq -4(%rbp), %rax  # i
    movl %eax, %edx
    movq $10, %rax
    cmpl %eax, %edx
    movl $0, %eax
    setl %al
    movzbq %al, %rax
    testq %rax, %rax
    jz .Lendfor2
# Cargando valor de x 0 -1
    movq -8(%rbp), %rax  # x
    movq %rax, %rdx
# Cargando valor de i 0 -1
    movq -4(%rbp), %rax  # i
    addq %rdx, %rax
    pushq %rax
    popq %rax
    movq %rax, -8(%rbp)  # guardar en local x
# Cargando valor de i 0 -1
    movq -4(%rbp), %rax  # i
    movq %rax, %rcx
    incq %rcx
    movq %rcx, -4(%rbp)
    jmp .Lfor1
.Lendfor2:
.section .rodata
printf_fmt_0: .string "El valor de x es: %d\n"
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
