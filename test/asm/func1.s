.data
print_fmt: .string "%ld\n"
.text
 .globl main
main:
 pushq %rbp
 movq %rsp, %rbp
 movq $5, %rax
 movq %rax, %rdi
 movq $3, %rax
 movq %rax, %rsi
 call suma
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 xorl %eax, %eax
 call printf@PLT
.end_main:
leave
ret
.globl suma
suma:
 pushq %rbp
 movq %rsp, %rbp
 mov %rdi, -8(%rbp)
 mov %rsi, -16(%rbp)
 subq $24, %rsp
 movq -8(%rbp), %rax
 pushq %rax
 movq -16(%rbp), %rax
 movq %rax, %rcx
 popq %rax
 addq %rcx, %rax
 movq %rax, -24(%rbp)
 movq -24(%rbp), %rax
.end_suma:
leave
ret
.section .note.GNU-stack,"",@progbits
