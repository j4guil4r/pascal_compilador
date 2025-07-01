.data
print_fmt: .string "%ld\n"
.text
 .globl main
main:
 pushq %rbp
 movq %rsp, %rbp
 movq $123456789, %rax
 movq %rax, %rdi
 call square
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 xorl %eax, %eax
 call printf@PLT
.end_main:
leave
ret
.globl square
square:
 pushq %rbp
 movq %rsp, %rbp
 mov %rdi, -8(%rbp)
 subq $16, %rsp
 movq -8(%rbp), %rax
 pushq %rax
 movq -8(%rbp), %rax
 movq %rax, %rcx
 popq %rax
 imulq %rcx, %rax
 movq %rax, -16(%rbp)
 movq -16(%rbp), %rax
.end_square:
leave
ret
.section .note.GNU-stack,"",@progbits
