.data
print_fmt: .string "%ld\n"
string_Juan: .string "Juan"  # Cadena constante

.text
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp          # Espacio para la estructura (8 + 4 + padding)

    # Inicialización de la estructura
    leaq string_Juan(%rip), %rax
    movq %rax, -16(%rbp)    # Campo nombre (offset 0)
    movq $20, -8(%rbp)      # Campo edad (offset 8)

    # Preparar llamada a printf
    leaq printf_fmt(%rip), %rdi     # Formato
    movq -16(%rbp), %rsi            # Campo nombre
    movq -8(%rbp), %rdx             # Campo edad
    movl $0, %eax                   # Para variádicas
    call printf

    movq $0, %rax                   # return 0
    leave
    ret

.section .rodata
printf_fmt: .string "Persona: %s, %d anos\n"
.section .note.GNU-stack,"",@progbits