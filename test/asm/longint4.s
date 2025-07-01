.data
print_fmt: .string "%ld\n"
l: .quad 0
i: .quad 0
.text
 .globl main
main:
 pushq %rbp
 movq %rsp, %rbp
 movq $1000000000, %rax
 movq %rax, l(%rip)
 movq $100, %rax
 movq %rax, i(%rip)
 movq l(%rip), %rax
 pushq %rax
 movq i(%rip), %rax
 movq %rax, %rcx
 popq %rax
 imulq %rcx, %rax
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 xorl %eax, %eax
 call printf@PLT
.end_main:
leave
ret
.section .note.GNU-stack,"",@progbits
