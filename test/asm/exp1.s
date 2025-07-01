.data
print_fmt: .string "%ld\n"
a: .quad 0
b: .quad 0
c: .quad 0
.text
 .globl main
main:
 pushq %rbp
 movq %rsp, %rbp
 movq $10, %rax
 movq %rax, a(%rip)
 movq $20, %rax
 movq %rax, b(%rip)
 movq $30, %rax
 movq %rax, c(%rip)
 movq a(%rip), %rax
 pushq %rax
 movq b(%rip), %rax
 pushq %rax
 movq c(%rip), %rax
 movq %rax, %rcx
 popq %rax
 imulq %rcx, %rax
 movq %rax, %rcx
 popq %rax
 addq %rcx, %rax
 pushq %rax
 movq a(%rip), %rax
 pushq %rax
 movq $2, %rax
 movq %rax, %rcx
 popq %rax
 cqto
 idivq %rcx
 movq %rax, %rcx
 popq %rax
 subq %rcx, %rax
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 xorl %eax, %eax
 call printf@PLT
.end_main:
leave
ret
.section .note.GNU-stack,"",@progbits
