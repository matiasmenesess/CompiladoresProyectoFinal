.data
print_fmt: .string "%ld\n"
.text
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp
#offset calculado de -8 para la variable y
#offset calculado de -16 para la variable z
#offset calculado de -24 para la variable f
#offset calculado de -32 para la variable g
    movq $5, %rax
    movq %rax, -8(%rbp)  # y
# Cargando valor de y 0 -1
    movq -8(%rbp), %rax  # y
    incq %rax
    movq %rax, -8(%rbp)
    movq %rax, -16(%rbp)  # z
    movq $1, %rax
    movb %al, -24(%rbp)  # f
    andb $1, -24(%rbp)  # Asegurar 0/1
    # Padding de 7 bytes para alineación
    movq $0, %rax
    movb %al, -32(%rbp)  # g
    andb $1, -32(%rbp)  # Asegurar 0/1
    # Padding de 7 bytes para alineación
# Cargando valor de f 0 -1
    movq -24(%rbp), %rax  # f
    pushq %rax
# Cargando valor de g 0 -1
    movq -32(%rbp), %rax  # g
    movq %rax, %rcx
    popq %rax
    # Operación binaria: &&
    testq %rax, %rax
    jz .Lfalse1
    testq %rcx, %rcx
    movl $1, %eax
    jnz .Lend2
.Lfalse1:
    movl $0, %eax
.Lend2:
    testq %rax, %rax
    jz .Lelse6
    movq $1, %rax
    pushq %rax
    movq $8, %rax
    movq %rax, %rcx
    popq %rax
    # Operación binaria: >
    cmpq %rcx, %rax
    movl $0, %eax
    setg %al
    movzbq %al, %rax
    testq %rax, %rax
    jz .Lelse2
.section .rodata
printf_fmt_0: .string "Resultado: %d\n"
.text
    leaq printf_fmt_0(%rip), %rdi
# Cargando valor de z 0 -1
    movq -16(%rbp), %rax  # z
    movq %rax, %rsi
    movl $0, %eax
    call printf
    jmp .Lendif3
.Lelse2:
.section .rodata
printf_fmt_1: .string "Resultado: %d\n"
.text
    leaq printf_fmt_1(%rip), %rdi
# Cargando valor de z 0 -1
    movq -16(%rbp), %rax  # z
    movq %rax, %rsi
    movl $0, %eax
    call printf
.Lendif3:
    jmp .Lendif7
.Lelse6:
# Cargando valor de f 0 -1
    movq -24(%rbp), %rax  # f
    pushq %rax
# Cargando valor de g 0 -1
    movq -32(%rbp), %rax  # g
    movq %rax, %rcx
    popq %rax
    # Operación binaria: ||
    testq %rax, %rax
    jnz .Ltrue3
    testq %rcx, %rcx
    movl $0, %eax
    jz .Lend4
.Ltrue3:
    movl $1, %eax
.Lend4:
    testq %rax, %rax
    jz .Lelse6
    movq $1, %rax
    pushq %rax
    movq $8, %rax
    movq %rax, %rcx
    popq %rax
    # Operación binaria: >
    cmpq %rcx, %rax
    movl $0, %eax
    setg %al
    movzbq %al, %rax
    testq %rax, %rax
    jz .Lelse4
.section .rodata
printf_fmt_2: .string "Resultado: %d\n"
.text
    leaq printf_fmt_2(%rip), %rdi
# Cargando valor de z 0 -1
    movq -16(%rbp), %rax  # z
    movq %rax, %rsi
    movl $0, %eax
    call printf
    jmp .Lendif5
.Lelse4:
.section .rodata
printf_fmt_3: .string "Resultado: %d\n"
.text
    leaq printf_fmt_3(%rip), %rdi
# Cargando valor de z 0 -1
    movq -16(%rbp), %rax  # z
    movq %rax, %rsi
    movl $0, %eax
    call printf
.Lendif5:
    jmp .Lendif7
.Lelse6:
.section .rodata
printf_fmt_4: .string "Resultado: %d\n"
.text
    leaq printf_fmt_4(%rip), %rdi
# Cargando valor de z 0 -1
    movq -16(%rbp), %rax  # z
    movq %rax, %rsi
    movl $0, %eax
    call printf
.Lendif7:
    movq $0, %rax
    leave
    ret
.section .note.GNU-stack,"",@progbits
