.data
print_fmt: .string "%ld\n"
.text
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp
#offset calculado de -8 para la variable arr
#offset calculado de -16 para la variable p
#offset calculado de -24 para la variable x
#offset calculado de -32 para la variable u
    movq $3, %rax
    imulq $8, %rax  # Elementos * 8 bytes
    movq %rax, %rcx  # Guardar tamaño total
    subq %rcx, %rsp  # Reservar espacio en stack
    movq %rsp, -8(%rbp)  # Guardar puntero al arreglo
    leaq array_1(%rip), %rax
    movq $1, %rax
    movq %rax, 0(%rbp)  # Inicializando elemento 0
    movq $2, %rax
    movq %rax, 8(%rbp)  # Inicializando elemento 1
    movq $3, %rax
    movq %rax, 16(%rbp)  # Inicializando elemento 2
# Cargando valor de arr 0 -1
    movq -8(%rbp), %rax  # arr
    movq %rax, -16(%rbp)  # p
# Cargando valor de p 0 -1
    movq -16(%rbp), %rax  # p
    pushq %rax
    movq $1, %rax
    movq %rax, %rcx
    popq %rax
    # Operación binaria: +
    addq %rcx, %rax
    movq (%rax), %rax  # *ptr
    movq %rax, -24(%rbp)  # x
    movq $10, %rax
    pushq %rax
    movq %rax, -32(%rbp)  # u
    movq $0, %rax
    leave
    ret
.section .note.GNU-stack,"",@progbits
