.data
print_fmt: .string "%ld\n"
.text
.globl main
.globl factorial
factorial:
    pushq %rbp
    movq %rsp, %rbp
    movq %rdi, -8(%rbp)
    movq -8(%rbp), %rax  # n
    pushq %rax
    movq $1, %rax
    movq %rax, %rcx
    popq %rax
    cmpq %rcx, %rax
    movl $0, %eax
    setle %al
    movzbq %al, %rax
    testq %rax, %rax
    jz .Lelse2
    movq $1, %rax
    leave
    ret
    jmp .Lendif3
.Lelse2:
    movq -8(%rbp), %rax  # n
    pushq %rax
    movq -8(%rbp), %rax  # n
    pushq %rax
    movq $1, %rax
    movq %rax, %rcx
    popq %rax
    subq %rcx, %rax
    movq %rax, %rdi
    call factorial
    movq %rax, %rcx
    popq %rax
    imulq %rcx, %rax
    leave
    ret
.Lendif3:
    leave
    ret
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp
.section .rodata
string_1: .string ""Hola mundo!""
.text
    leaq string_1(%rip), %rax
    movb %al, -8(%rbp)  # mensaje
    # Padding de 7 bytes para alineación
    movq $5, %rax
    pushq %rax
    movq $1, %rax
    movq %rax, %rcx
    popq %rax
    cqo
    idivq %rcx
    movq %rax, -16(%rbp)  # x
    movq -16(%rbp), %rax  # x
    leaq -16(%rbp), %rax  # &x
    movq %rax, -24(%rbp)  # ptr
    leaq array_2(%rip), %rax
.section .rodata
string_3: .string ""Juan""
.text
    leaq string_3(%rip), %rax
    movq %rax, 0(%rbp)  # Inicializando elemento 0
    movq $20, %rax
    movq %rax, 8(%rbp)  # Inicializando elemento 1
    movq %rax, -32(%rbp)  # p
.section .rodata
printf_fmt_0: .string "Mensaje: %s\n"
.text
    leaq printf_fmt_0(%rip), %rdi
    movq -8(%rbp), %rax  # mensaje
    movq %rax, %rsi
    movl $0, %eax
    call printf
.section .rodata
printf_fmt_1: .string "Factorial de %d es %d\n"
.text
    leaq printf_fmt_1(%rip), %rdi
    movq -16(%rbp), %rax  # x
    movq %rax, %rsi
    movq -16(%rbp), %rax  # x
    movq %rax, %rdi
    call factorial
    movq %rax, %rdx
    movl $0, %eax
    call printf
.section .rodata
printf_fmt_2: .string "Persona: %s, %d anos\n"
.text
    leaq printf_fmt_2(%rip), %rdi
    movq -32(%rbp), %rax  # p
    addq $8, %rax  # offset del miembro nombre
    movq (%rax), %rax
    movq %rax, %rsi
    movq -32(%rbp), %rax  # p
    addq $8, %rax  # offset del miembro edad
    movq (%rax), %rax
    movq %rax, %rdx
    movl $0, %eax
    call printf
