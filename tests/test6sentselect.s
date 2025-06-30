.data
print_fmt: .string "%ld\n"
.text
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp
#offset calculado de -8 para la variable contador
    movq $5, %rax
    movq %rax, -8(%rbp)  # contador
.section .rodata
printf_fmt_0: .string "Iniciando bucle while (cuenta regresiva):\n"
.text
    leaq printf_fmt_0(%rip), %rdi
    movl $0, %eax
    call printf
.Lwhile1:
# Cargando valor de contador 0 -1
    movq -8(%rbp), %rax  # contador
    pushq %rax
    movq $0, %rax
    movq %rax, %rcx
    popq %rax
    # Operación binaria: >
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
# Cargando valor de contador 0 -1
    movq -8(%rbp), %rax  # contador
    movq %rax, %rsi
    movl $0, %eax
    call printf
# Cargando valor de contador 0 -1
    movq -8(%rbp), %rax  # contador
    pushq %rax
    movq $1, %rax
    movq %rax, %rcx
    popq %rax
    # Operación binaria: -
    subq %rcx, %rax
    pushq %rax
    popq %rax
    movq %rax, -8(%rbp)  # guardar en local contador
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
.section .note.GNU-stack,"",@progbits
