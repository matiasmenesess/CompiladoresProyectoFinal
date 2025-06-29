.data
print_fmt: .string "%ld\n"
printf_fmt_0: .string "La suma es: %d\n"  # %d es correcto para int en C++

.text
.globl main
.globl suma

suma:
    pushq %rbp
    movq %rsp, %rbp

    # %rdi contiene la DIRECCIÓN de a (por ser referencia)
    # %rsi contiene el valor de b

    movq (%rdi), %rax    # Cargar valor de a
    addq %rsi, %rax      # Sumar b
    movq %rax, (%rdi)    # Guardar resultado en a (modifica la variable original)

    leave
    ret

main:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp        # Espacio para a (4/8 bytes), b (4/8 bytes)

    movl $22, -8(%rbp)    # a = 22 (32 bits para int)
    movl $3, -12(%rbp)    # b = 3 (32 bits para int)

    # Llamar a suma (pasando dirección de a y valor de b)
    leaq -8(%rbp), %rdi   # Pasar dirección de a (referencia)
    movl -12(%rbp), %esi  # Pasar valor de b (32 bits)
    call suma

    # Imprimir resultado (a fue modificado por referencia)
    leaq printf_fmt_0(%rip), %rdi
    movl -8(%rbp), %esi   # Cargar valor de a (32 bits)
    movl $0, %eax
    call printf

    movl $0, %eax         # return 0
    leave
    ret

.section .note.GNU-stack,"",@progbits