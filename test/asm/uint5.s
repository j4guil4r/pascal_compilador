.data
print_fmt: .string "%ld\n"
.text
 .globl main
main:
 pushq %rbp
 movq %rsp, %rbp
 movq $30000, %rax
 movq %rax, %rdi
 call double
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 xorl %eax, %eax
 call printf@PLT
.end_main:
leave
ret
.globl double
double:
 pushq %rbp
 movq %rsp, %rbp
 mov %rdi, -8(%rbp)
 subq $16, %rsp
 movq -8(%rbp), %rax
 pushq %rax
 movq $2, %rax
 movq %rax, %rcx
 popq %rax
 imulq %rcx, %rax
 movq %rax, -16(%rbp)
 movq -16(%rbp), %rax
.end_double:
leave
ret
.section .note.GNU-stack,"",@progbits
