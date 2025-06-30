.data
print_fmt: .string "%ld\n"
.text
.globl main
.globl llenar
llenar:
    pushq %rbp
    movq %rsp, %rbp
# Registrando variable: arr reg_index: 0 offset: 0 is_global: false is_reference: true
# Registrando variable: n reg_index: 1 offset: 0 is_global: false is_reference: false
