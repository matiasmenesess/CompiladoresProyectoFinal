.data
print_fmt: .string "%ld\n"
.text
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp
# Cantidad de globales: 0
    leaq array_1(%rip), %rax
.section .rodata
string_2: .string ""C Programming""
.text
    leaq string_2(%rip), %rax
    movq %rax, 0(%rbp)  # Inicializando elemento 0
    movq $1978, %rax
    movq %rax, 8(%rbp)  # Inicializando elemento 1
    movq %rax, -8(%rbp)  # mi_libro
.section .rodata
printf_fmt_0: .string "Libro: %s, Publicado en: %d\n"
.text
    leaq printf_fmt_0(%rip), %rdi
    movq -8(%rbp), %rax  # mi_libro
    addq $8, %rax  # offset del miembro titulo
    movq (%rax), %rax
    movq %rax, %rsi
    movq -8(%rbp), %rax  # mi_libro
    addq $8, %rax  # offset del miembro anio
    movq (%rax), %rax
    movq %rax, %rdx
    movl $0, %eax
    call printf
    movq $0, %rax
    leave
    ret
.section .note.GNU-stack,"",@progbits
