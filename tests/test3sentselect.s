.data
print_fmt: .string "%ld\n"
.text
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp
#offset calculado de -8 para la variable c
    movq $98, %rax
    movb %al, -8(%rbp)  # c
    # Padding de 7 bytes para alineación
# Cargando valor de c 0 -1
    movq -8(%rbp), %rax  # c
    pushq %rax
    movq $97, %rax
    movq %rax, %rcx
    popq %rax
    # Operación binaria: ==
    cmpq %rcx, %rax
    movl $0, %eax
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    jz .Lelse2
.section .rodata
printf_fmt_0: .string "Es 'a'\n"
.text
    leaq printf_fmt_0(%rip), %rdi
    movl $0, %eax
    call printf
    jmp .Lendif3
.Lelse2:
# Cargando valor de c 0 -1
    movq -8(%rbp), %rax  # c
    pushq %rax
    movq $98, %rax
    movq %rax, %rcx
    popq %rax
    # Operación binaria: ==
    cmpq %rcx, %rax
    movl $0, %eax
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    jz .Lelse2
.section .rodata
printf_fmt_1: .string "Es 'b'\n"
.text
    leaq printf_fmt_1(%rip), %rdi
    movl $0, %eax
    call printf
    jmp .Lendif3
.Lelse2:
.section .rodata
printf_fmt_2: .string "Es otro caracter\n"
.text
    leaq printf_fmt_2(%rip), %rdi
    movl $0, %eax
    call printf
.Lendif3:
    movq $0, %rax
    leave
    ret
.section .note.GNU-stack,"",@progbits
