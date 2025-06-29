.data
print_fmt: .string "%ld\n"
.text
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $8, %rsp
    movq $5, %rax
    movq %rax, -8(%rbp)  # contador
.section .rodata
printf_fmt_0: .string "Iniciando bucle while (cuenta regresiva):\n"
.text
    leaq printf_fmt_0(%rip), %rdi
    movl $0, %eax
    call printf
.Lwhile1:
    movq -8(%rbp), %rax  # contador
    pushq %rax
    movq $0, %rax
    movq %rax, %rcx
    popq %rax
    cmpq %rcx, %rax
    movl $0, %eax
    setg %al
    movzbq %al, %rax
    testq %rax, %rax
    jz .Lendwhile2
.section .rodata
printf_fmt_1: .string "%d...\n"
.text
    leaq printf_fmt_1(%rip), %rdi
    movq -8(%rbp), %rax  # contador
    movq %rax, %rsi
    movl $0, %eax
    call printf
    movq -8(%rbp), %rax  # contador
    pushq %rax
    movq $1, %rax
    movq %rax, %rcx
    popq %rax
    subq %rcx, %rax
    pushq %rax
    popq %rax
    movq %rax, -8(%rbp)  # contador = valor
    jmp .Lwhile1
.Lendwhile2:
.section .rodata
printf_fmt_2: .string "¡Despegue!\n"
.text
    leaq printf_fmt_2(%rip), %rdi
    movl $0, %eax
    call printf
    movq $0, %rax
    leave
    ret
    movl $0, %eax
    leave
    ret
.section .note.GNU-stack,"",@progbits
