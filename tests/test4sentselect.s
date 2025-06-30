.data
print_fmt: .string "%ld\n"
.text
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
.section .rodata
printf_fmt_0: .string "Iniciando bucle for:\n"
.text
    leaq printf_fmt_0(%rip), %rdi
    movl $0, %eax
    call printf
