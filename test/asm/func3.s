.data
print_fmt: .string "%ld\n"
.text
 .globl main
main:
 pushq %rbp
 movq %rsp, %rbp
 movq $10, %rax
 movq %rax, %rdi
 movq $20, %rax
 movq %rax, %rsi
 movq $15, %rax
 movq %rax, %rdx
 call max
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 xorl %eax, %eax
 call printf@PLT
.end_main:
leave
ret
.globl max
max:
 pushq %rbp
 movq %rsp, %rbp
 mov %rdi, -8(%rbp)
 mov %rsi, -16(%rbp)
 mov %rdx, -24(%rbp)
 subq $32, %rsp
 movq -8(%rbp), %rax
 pushq %rax
 movq -16(%rbp), %rax
 movq %rax, %rcx
 popq %rax
 cmpq %rcx, %rax
 setge %al
 movzbq %al, %rax
 pushq %rax
 movq -8(%rbp), %rax
 pushq %rax
 movq -24(%rbp), %rax
 movq %rax, %rcx
 popq %rax
 cmpq %rcx, %rax
 setge %al
 movzbq %al, %rax
 movq %rax, %rcx
 popq %rax
 andq %rcx, %rax
 cmpq $0, %rax
 je else_0
 movq -8(%rbp), %rax
 movq %rax, -32(%rbp)
 jmp endif_0
 else_0:
 movq -16(%rbp), %rax
 pushq %rax
 movq -24(%rbp), %rax
 movq %rax, %rcx
 popq %rax
 cmpq %rcx, %rax
 setge %al
 movzbq %al, %rax
 cmpq $0, %rax
 je else_1
 movq -16(%rbp), %rax
 movq %rax, -32(%rbp)
 jmp endif_1
 else_1:
 movq -24(%rbp), %rax
 movq %rax, -32(%rbp)
endif_1:
endif_0:
 movq -32(%rbp), %rax
.end_max:
leave
ret
.section .note.GNU-stack,"",@progbits
