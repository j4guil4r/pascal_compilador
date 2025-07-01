.data
print_fmt: .string "%ld\n"
u: .quad 0
i: .quad 0
.text
 .globl main
main:
 pushq %rbp
 movq %rsp, %rbp
 movq $10, %rax
 movq %rax, u(%rip)
 movq $5, %rax
 negq %rax
 movq %rax, i(%rip)
 movq u(%rip), %rax
 pushq %rax
 movq i(%rip), %rax
 movq %rax, %rcx
 popq %rax
 addq %rcx, %rax
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 xorl %eax, %eax
 call printf@PLT
.end_main:
leave
ret
.section .note.GNU-stack,"",@progbits
