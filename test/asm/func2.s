.data
print_fmt: .string "%ld\n"
.text
 .globl main
main:
 pushq %rbp
 movq %rsp, %rbp
 movq $20, %rax
 movq %rax, %rdi
 call factorial
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 xorl %eax, %eax
 call printf@PLT
.end_main:
leave
ret
.globl factorial
factorial:
 pushq %rbp
 movq %rsp, %rbp
 mov %rdi, -8(%rbp)
 subq $16, %rsp
 movq -8(%rbp), %rax
 pushq %rax
 movq $1, %rax
 movq %rax, %rcx
 popq %rax
 cmpq %rcx, %rax
 setle %al
 movzbq %al, %rax
 cmpq $0, %rax
 je else_0
 movq $1, %rax
 movq %rax, -16(%rbp)
 jmp endif_0
 else_0:
 movq -8(%rbp), %rax
 pushq %rax
 movq -8(%rbp), %rax
 pushq %rax
 movq $1, %rax
 movq %rax, %rcx
 popq %rax
 subq %rcx, %rax
 movq %rax, %rdi
 call factorial
 movq %rax, %rcx
 popq %rax
 imulq %rcx, %rax
 movq %rax, -16(%rbp)
endif_0:
 movq -16(%rbp), %rax
.end_factorial:
leave
ret
.section .note.GNU-stack,"",@progbits
