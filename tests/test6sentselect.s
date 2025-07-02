.data
print_fmt: .string "%ld\n"
# Miembro: nombre tipo: char offset: 0 tamaño: 8
# Miembro: edad tipo: int offset: 8 tamaño: 8
# Struct Persona tamaño total: 16
# Campo edad: offset 8
# Campo nombre: offset 0
.text
.globl main
main:
 pushq %rbp
 movq %rsp, %rbp
 subq $48, %rsp
# Declarando variable: p1 en offset -16
# Declarando variable: p2 en offset -32
# Declarando variable: i en offset -40
    movq $0, -16(%rbp) # inicializar p1 a 0
    movq $0, -32(%rbp) # inicializar p2 a 0
.section .rodata
string_1: .string "Ana"
.text
 leaq string_1(%rip), %rax
 pushq %rax
 popq %rax # recuperar valor a asignar
 pushq %rax # guardar valor temporalmente
 leaq -16(%rbp), %rax # dirección de nombre en struct local
 movq %rax, %rbx # guardar dirección
 popq %rax # recuperar valor
 movq %rax, (%rbx) # escribir valor en member
 movq $17, %rax
 pushq %rax
 popq %rax # recuperar valor a asignar
 pushq %rax # guardar valor temporalmente
 leaq -8(%rbp), %rax # dirección de edad en struct local
 movq %rax, %rbx # guardar dirección
 popq %rax # recuperar valor
 movq %rax, (%rbx) # escribir valor en member
.section .rodata
string_2: .string "Luis"
.text
 leaq string_2(%rip), %rax
 pushq %rax
 popq %rax # recuperar valor a asignar
 pushq %rax # guardar valor temporalmente
 leaq -32(%rbp), %rax # dirección de nombre en struct local
 movq %rax, %rbx # guardar dirección
 popq %rax # recuperar valor
 movq %rax, (%rbx) # escribir valor en member
 movq $22, %rax
 pushq %rax
 popq %rax # recuperar valor a asignar
 pushq %rax # guardar valor temporalmente
 leaq -24(%rbp), %rax # dirección de edad en struct local
 movq %rax, %rbx # guardar dirección
 popq %rax # recuperar valor
 movq %rax, (%rbx) # escribir valor en member
 movq $1, %rax
    movq %rax, -40(%rbp) # i
.Lwhile3:
# Cargando valor de i 0 -1
 movq -40(%rbp), %rax # i
    movq %rax, %rdx
 movq $2, %rax
    cmpq %rax, %rdx
    movq $0, %rax
    setle %al
    movzbq %al, %rax
    testq %rax, %rax
    jz .Lendwhile4
# Declarando variable: persona en offset -48
    movq $0, -48(%rbp) # inicializar persona a 0
# Cargando valor de i 0 -1
 movq -40(%rbp), %rax # i
    movq %rax, %rdx
 movq $1, %rax
    cmpq %rax, %rdx
    movq $0, %rax
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    jz .Lelse5
# Cargando valor de p1 0 -1
 movq -16(%rbp), %rax # p1
    leaq -16(%rbp), %rax  # &p1
 pushq %rax
 popq %rax
 movq %rax, -48(%rbp) # guardar en local persona
    jmp .Lendif6
.Lelse5:
# Cargando valor de p2 0 -1
 movq -32(%rbp), %rax # p2
    leaq -32(%rbp), %rax  # &p2
 pushq %rax
 popq %rax
 movq %rax, -48(%rbp) # guardar en local persona
.Lendif6:
.section .rodata
printf_fmt_0: .string "Persona: %s, Edad: %d - "
.text
    leaq printf_fmt_0(%rip), %rdi
# Cargando valor de persona 0 -1
 movq -48(%rbp), %rax # persona
 addq $0, %rax # offset del miembro nombre
 movq (%rax), %rax # cargar valor del miembro
    movq %rax, %rsi
# Cargando valor de persona 0 -1
 movq -48(%rbp), %rax # persona
 addq $8, %rax # offset del miembro edad
 movq (%rax), %rax # cargar valor del miembro
    movq %rax, %rdx
    xorq %rax, %rax # 0 registros vectoriales usados
    call printf@PLT
# Cargando valor de persona 0 -1
 movq -48(%rbp), %rax # persona
 addq $8, %rax # offset del miembro edad
 movq (%rax), %rax # cargar valor del miembro
    movq %rax, %rdx
 movq $18, %rax
    cmpq %rax, %rdx
    movq $0, %rax
    setge %al
    movzbq %al, %rax
    testq %rax, %rax
    jz .Lelse7
.section .rodata
printf_fmt_1: .string "Mayor de edad\n"
.text
    leaq printf_fmt_1(%rip), %rdi
    xorq %rax, %rax # 0 registros vectoriales usados
    call printf@PLT
    jmp .Lendif8
.Lelse7:
.section .rodata
printf_fmt_2: .string "Menor de edad\n"
.text
    leaq printf_fmt_2(%rip), %rdi
    xorq %rax, %rax # 0 registros vectoriales usados
    call printf@PLT
.Lendif8:
# Cargando valor de i 0 -1
 movq -40(%rbp), %rax # i
    movq %rax, %rcx
    incq %rcx
    movq %rcx, -40(%rbp)
    jmp .Lwhile3
.Lendwhile4:
 movq $0, %rax
    leave
    ret
.section .note.GNU-stack,"",@progbits
