.data
print_fmt: .string "%ld\n"
# Miembro: x tipo: int offset: 0 tamaño: 8
# Miembro: y tipo: int offset: 8 tamaño: 8
# Struct Punto tamaño total: 16
# Campo y: offset 8
# Campo x: offset 0
.text
.globl main
.globl duplica_y
duplica_y:
    pushq %rbp
    movq %rsp, %rbp
# Parámetro: pt reg_index: 0 is_reference: false
# Cargando valor de pt 0 0
 movq %rdi, %rax # Valor de pt
 addq $0, %rax # offset del miembro x
 movq (%rax), %rax # cargar valor del miembro
    movq %rax, %rdx
 movq $2, %rax
    imulq %rdx, %rax
 pushq %rax
 popq %rax # recuperar valor a asignar
 pushq %rax # guardar valor temporalmente
# Cargando valor de pt 0 0
 movq %rdi, %rax # Valor de pt
 addq $8, %rax # dirección de y
 movq %rax, %rbx # guardar dirección
 popq %rax # recuperar valor
 movq %rax, (%rbx) # escribir valor en member
    leave
    ret
main:
 pushq %rbp
 movq %rsp, %rbp
 subq $16, %rsp
# Declarando variable: p en offset -16
    movq $0, -16(%rbp) # inicializar p a 0
 movq $5, %rax
 pushq %rax
 popq %rax # recuperar valor a asignar
 pushq %rax # guardar valor temporalmente
 leaq -16(%rbp), %rax # dirección de x en struct local
 movq %rax, %rbx # guardar dirección
 popq %rax # recuperar valor
 movq %rax, (%rbx) # escribir valor en member
# Cargando valor de p 0 -1
 movq -16(%rbp), %rax # p
    leaq -16(%rbp), %rax  # &p
    movq %rax, %rdi
    call duplica_y
.section .rodata
printf_fmt_0: .string "p.y deberia ser 10: %d\n"
.text
    leaq printf_fmt_0(%rip), %rdi
 movq -8(%rbp), %rax # y de struct local
    movq %rax, %rsi
    xorq %rax, %rax # 0 registros vectoriales usados
    call printf@PLT
 movq $0, %rax
    leave
    ret
.section .note.GNU-stack,"",@progbits
