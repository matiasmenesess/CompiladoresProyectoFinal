.data
print_fmt: .string "%ld\n"
.text
.globl main
main:
 pushq %rbp
 movq %rsp, %rbp
 subq $32, %rsp
# Declarando variable: x en offset -8
# Declarando variable: ptr en offset -16
# Declarando variable: pptr en offset -24
 movq $42, %rax
    movq %rax, -8(%rbp) # x
# Cargando valor de x 0 -1
 movq -8(%rbp), %rax # x
    leaq -8(%rbp), %rax  # &x
    movq %rax, -16(%rbp) # ptr
# Cargando valor de ptr 0 -1
 movq -16(%rbp), %rax # ptr
    movq %rax, -24(%rbp) # pptr
.section .rodata
printf_fmt_0: .string "Valor de x: %d\n"
.text
    pushq %rbp # salvar frame pointer para alineación
    leaq printf_fmt_0(%rip), %rdi
# Cargando valor de x 0 -1
 movq -8(%rbp), %rax # x
    movq %rax, %rsi
    xorq %rax, %rax # 0 registros vectoriales usados
    call printf@PLT
    popq %rbp # restaurar frame pointer
.section .rodata
printf_fmt_1: .string "Valor usando *ptr: %d\n"
.text
    pushq %rbp # salvar frame pointer para alineación
    leaq printf_fmt_1(%rip), %rdi
# Cargando valor de ptr 0 -1
 movq -16(%rbp), %rax # ptr
    movq (%rax), %rax  # *ptr
    movq %rax, %rsi
    xorq %rax, %rax # 0 registros vectoriales usados
    call printf@PLT
    popq %rbp # restaurar frame pointer
.section .rodata
printf_fmt_2: .string "Valor usando **pptr: %d\n"
.text
    pushq %rbp # salvar frame pointer para alineación
    leaq printf_fmt_2(%rip), %rdi
# Cargando valor de pptr 0 -1
 movq -24(%rbp), %rax # pptr
    movq (%rax), %rax  # *ptr
    movq %rax, %rsi
    xorq %rax, %rax # 0 registros vectoriales usados
    call printf@PLT
    popq %rbp # restaurar frame pointer
 movq $99, %rax
 pushq %rax
# Cargando valor de pptr 0 -1
 movq -24(%rbp), %rax # pptr
    movq (%rax), %rax  # *ptr
 movq %rax, %rbx # guardar dirección
 popq %rax # recuperar valor a asignar
 movq %rax, (%rbx) # *ptr = valor
.section .rodata
printf_fmt_3: .string "Nuevo valor de x: %d\n"
.text
    pushq %rbp # salvar frame pointer para alineación
    leaq printf_fmt_3(%rip), %rdi
# Cargando valor de x 0 -1
 movq -8(%rbp), %rax # x
    movq %rax, %rsi
    xorq %rax, %rax # 0 registros vectoriales usados
    call printf@PLT
    popq %rbp # restaurar frame pointer
 movq $0, %rax
    leave
    ret
.section .note.GNU-stack,"",@progbits
