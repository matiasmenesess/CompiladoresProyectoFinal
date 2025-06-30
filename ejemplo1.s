.data
print_fmt: .string "%ld\n"
.text
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
 # debug de init
    movq $0, %rax
    movl %eax, -8(%rbp)  # i
    # Padding de 4 bytes para alineación
.Lfor1:
# Cargando valor de i 0 -1
    movq -8(%rbp), %rax  # i
    pushq %rax
    movq $10, %rax
    movq %rax, %rcx
    popq %rax
    # Operación binaria: <
    cmpq %rcx, %rax
    movl $0, %eax
    setl %al
    movzbq %al, %rax
    testq %rax, %rax
    jz .Lendfor2
.section .rodata
printf_fmt_0: .string "hola\n"
.text
    leaq printf_fmt_0(%rip), %rdi
    movl $0, %eax
    call printf
# Cargando valor de i 0 -1
    movq -8(%rbp), %rax  # i
    incq %rax
    movq %rax, -8(%rbp)
    jmp .Lfor1
.Lendfor2:
    movq $0, %rax
    leave
    ret
.section .note.GNU-stack,"",@progbits
