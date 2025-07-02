.data
print_fmt: .string "%ld\n"
# Miembro: x tipo: int offset: 0 tamaño: 8
# Miembro: y tipo: int offset: 8 tamaño: 8
# Struct Punto tamaño total: 16
# Campo y: offset 8
# Campo x: offset 0
# Miembro: pendiente tipo: int offset: 0 tamaño: 8
# Miembro: interseccion tipo: int offset: 8 tamaño: 8
# Struct Recta tamaño total: 16
# Campo interseccion: offset 8
# Campo pendiente: offset 0
# Miembro: radio tipo: int offset: 0 tamaño: 8
# Miembro: centro_x tipo: int offset: 8 tamaño: 8
# Miembro: centro_y tipo: int offset: 16 tamaño: 8
# Struct Circulo tamaño total: 24
# Campo centro_y: offset 16
# Campo centro_x: offset 8
# Campo radio: offset 0
.text
.globl main
main:
 pushq %rbp
 movq %rsp, %rbp
 subq $80, %rsp
# Declarando variable: p1 en offset -16
# Declarando variable: p2 en offset -32
# Declarando variable: r1 en offset -48
# Declarando variable: c1 en offset -72
    movq $0, -16(%rbp) # inicializar p1 a 0
    movq $0, -32(%rbp) # inicializar p2 a 0
    movq $0, -48(%rbp) # inicializar r1 a 0
    movq $0, -72(%rbp) # inicializar c1 a 0
 movq $10, %rax
 pushq %rax
 popq %rax # recuperar valor a asignar
 pushq %rax # guardar valor temporalmente
 leaq -16(%rbp), %rax # dirección de x en struct local
 movq %rax, %rbx # guardar dirección
 popq %rax # recuperar valor
 movq %rax, (%rbx) # escribir valor en member
 movq $20, %rax
 pushq %rax
 popq %rax # recuperar valor a asignar
 pushq %rax # guardar valor temporalmente
 leaq -8(%rbp), %rax # dirección de y en struct local
 movq %rax, %rbx # guardar dirección
 popq %rax # recuperar valor
 movq %rax, (%rbx) # escribir valor en member
 movq $5, %rax
    negq %rax
 pushq %rax
 popq %rax # recuperar valor a asignar
 pushq %rax # guardar valor temporalmente
 leaq -32(%rbp), %rax # dirección de x en struct local
 movq %rax, %rbx # guardar dirección
 popq %rax # recuperar valor
 movq %rax, (%rbx) # escribir valor en member
 movq $15, %rax
 pushq %rax
 popq %rax # recuperar valor a asignar
 pushq %rax # guardar valor temporalmente
 leaq -24(%rbp), %rax # dirección de y en struct local
 movq %rax, %rbx # guardar dirección
 popq %rax # recuperar valor
 movq %rax, (%rbx) # escribir valor en member
 movq $2, %rax
 pushq %rax
 popq %rax # recuperar valor a asignar
 pushq %rax # guardar valor temporalmente
 leaq -48(%rbp), %rax # dirección de pendiente en struct local
 movq %rax, %rbx # guardar dirección
 popq %rax # recuperar valor
 movq %rax, (%rbx) # escribir valor en member
 movq $3, %rax
 pushq %rax
 popq %rax # recuperar valor a asignar
 pushq %rax # guardar valor temporalmente
 leaq -40(%rbp), %rax # dirección de interseccion en struct local
 movq %rax, %rbx # guardar dirección
 popq %rax # recuperar valor
 movq %rax, (%rbx) # escribir valor en member
 movq $7, %rax
 pushq %rax
 popq %rax # recuperar valor a asignar
 pushq %rax # guardar valor temporalmente
 leaq -72(%rbp), %rax # dirección de radio en struct local
 movq %rax, %rbx # guardar dirección
 popq %rax # recuperar valor
 movq %rax, (%rbx) # escribir valor en member
 movq $0, %rax
 pushq %rax
 popq %rax # recuperar valor a asignar
 pushq %rax # guardar valor temporalmente
 leaq -64(%rbp), %rax # dirección de centro_x en struct local
 movq %rax, %rbx # guardar dirección
 popq %rax # recuperar valor
 movq %rax, (%rbx) # escribir valor en member
 movq $0, %rax
 pushq %rax
 popq %rax # recuperar valor a asignar
 pushq %rax # guardar valor temporalmente
 leaq -56(%rbp), %rax # dirección de centro_y en struct local
 movq %rax, %rbx # guardar dirección
 popq %rax # recuperar valor
 movq %rax, (%rbx) # escribir valor en member
.section .rodata
printf_fmt_0: .string "Punto 1: (%d, %d)\n"
.text
    leaq printf_fmt_0(%rip), %rdi
 movq -16(%rbp), %rax # x de struct local
    movq %rax, %rsi
 movq -8(%rbp), %rax # y de struct local
    movq %rax, %rdx
    xorq %rax, %rax # 0 registros vectoriales usados
    call printf@PLT
.section .rodata
printf_fmt_1: .string "Punto 2: (%d, %d)\n"
.text
    leaq printf_fmt_1(%rip), %rdi
 movq -32(%rbp), %rax # x de struct local
    movq %rax, %rsi
 movq -24(%rbp), %rax # y de struct local
    movq %rax, %rdx
    xorq %rax, %rax # 0 registros vectoriales usados
    call printf@PLT
.section .rodata
printf_fmt_2: .string "Recta: pendiente=%d, interseccion=%d\n"
.text
    leaq printf_fmt_2(%rip), %rdi
 movq -48(%rbp), %rax # pendiente de struct local
    movq %rax, %rsi
 movq -40(%rbp), %rax # interseccion de struct local
    movq %rax, %rdx
    xorq %rax, %rax # 0 registros vectoriales usados
    call printf@PLT
.section .rodata
printf_fmt_3: .string "Circulo: radio=%d, centro=(%d, %d)\n"
.text
    leaq printf_fmt_3(%rip), %rdi
 movq -72(%rbp), %rax # radio de struct local
    movq %rax, %rsi
 movq -64(%rbp), %rax # centro_x de struct local
    movq %rax, %rdx
 movq -56(%rbp), %rax # centro_y de struct local
    movq %rax, %rcx
    xorq %rax, %rax # 0 registros vectoriales usados
    call printf@PLT
 movq $0, %rax
    leave
    ret
.section .note.GNU-stack,"",@progbits
