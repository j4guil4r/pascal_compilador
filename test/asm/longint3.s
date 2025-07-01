.data
print_fmt: .string "%ld\n"
min: .quad 0
max: .quad 0
.text
 .globl main
main:
 pushq %rbp
 movq %rsp, %rbp
 movq $9223372036854775807, %rax
 negq %rax
 movq %rax, min(%rip)
 movq $9223372036854775807, %rax
 movq %rax, max(%rip)
 movq min(%rip), %rax
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 xorl %eax, %eax
 call printf@PLT
 movq max(%rip), %rax
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 xorl %eax, %eax
 call printf@PLT
.end_main:
leave
ret
.section .note.GNU-stack,"",@progbits
