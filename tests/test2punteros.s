.data
print_fmt: .string "%ld\n"
.text
.globl main
main:
 pushq %rbp
 movq %rsp, %rbp
 subq $16, %rsp
# Declarando variable: x en offset -8
# Declarando variable: ptr en offset -16
 movq $10, %rax
    movq %rax, -8(%rbp) # x
# Cargando valor de x 0 -1
 movq -8(%rbp), %rax # x
    leaq -8(%rbp), %rax  # &x
    movq %rax, -16(%rbp) # ptr
.section .rodata
printf_fmt_0: .string "La direccion de x es: %p\n"
.text
    leaq printf_fmt_0(%rip), %rdi
# Cargando valor de ptr 0 -1
 movq -16(%rbp), %rax # ptr
    movq %rax, %rsi
    xorq %rax, %rax # 0 registros vectoriales usados
    call printf@PLT
 movq $0, %rax
    leave
    ret
.section .note.GNU-stack,"",@progbits
