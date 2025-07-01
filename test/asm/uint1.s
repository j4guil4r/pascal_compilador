.data
print_fmt: .string "%ld\n"
a: .quad 0
b: .quad 0
.text
 .globl main
main:
 pushq %rbp
 movq %rsp, %rbp
 movq $10, %rax
 movq %rax, a(%rip)
 movq $20, %rax
 movq %rax, b(%rip)
 movq a(%rip), %rax
 pushq %rax
 movq b(%rip), %rax
 movq %rax, %rcx
 popq %rax
 addq %rcx, %rax
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 xorl %eax, %eax
 call printf@PLT
 movq a(%rip), %rax
 pushq %rax
 movq b(%rip), %rax
 movq %rax, %rcx
 popq %rax
 subq %rcx, %rax
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 xorl %eax, %eax
 call printf@PLT
 movq a(%rip), %rax
 pushq %rax
 movq b(%rip), %rax
 movq %rax, %rcx
 popq %rax
 imulq %rcx, %rax
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 xorl %eax, %eax
 call printf@PLT
 movq a(%rip), %rax
 pushq %rax
 movq b(%rip), %rax
 movq %rax, %rcx
 popq %rax
 cqto
 idivq %rcx
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 xorl %eax, %eax
 call printf@PLT
.end_main:
leave
ret
.section .note.GNU-stack,"",@progbits
