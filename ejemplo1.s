.data
print_fmt: .string "%ld\n"
.text
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    movq $0, %rax
    movl %eax, -4(%rbp)  # i
    # Padding de 8 bytes para alineación
.Lfor1:
# Cargando valor de i 0 -1
    movl -4(%rbp), %eax  # i
    movl %eax, %edx
    movq $10, %rax
    cmpl %eax, %edx
    movl $0, %eax
    setl %al
    movzbq %al, %rax
    testq %rax, %rax
    jz .Lendfor2
    movq $0, %rax
    movl %eax, -8(%rbp)  # J
    # Padding de 4 bytes para alineación
.Lfor3:
# Cargando valor de J 0 -1
    movl -8(%rbp), %eax  # J
    movl %eax, %edx
    movq $10, %rax
    cmpl %eax, %edx
    movl $0, %eax
    setl %al
    movzbq %al, %rax
    testq %rax, %rax
    jz .Lendfor4
.section .rodata
printf_fmt_0: .string "hola\n"
.text
    leaq printf_fmt_0(%rip), %rdi
    movl $0, %eax
    call printf
# Cargando valor de J 0 -1
    movl -8(%rbp), %eax  # J
    movl %eax, %ecx
    incl %ecx
    movl %ecx, -8(%rbp)
    jmp .Lfor3
.Lendfor4:
# Cargando valor de i 0 -1
    movl -4(%rbp), %eax  # i
    movl %eax, %ecx
    incl %ecx
    movl %ecx, -4(%rbp)
    jmp .Lfor1
.Lendfor2:
    movq $0, %rax
    leave
    ret
.section .note.GNU-stack,"",@progbits
