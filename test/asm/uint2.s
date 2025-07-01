.data
print_fmt: .string "%ld\n"
x: .quad 0
y: .quad 0
.text
 .globl main
main:
 pushq %rbp
 movq %rsp, %rbp
 movq $40000, %rax
 movq %rax, x(%rip)
 movq $50000, %rax
 movq %rax, y(%rip)
 movq x(%rip), %rax
 pushq %rax
 movq y(%rip), %rax
 movq %rax, %rcx
 popq %rax
 cmpq %rcx, %rax
 setl %al
 movzbq %al, %rax
 cmpq $0, %rax
 je else_0
 movq $1, %rax
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 xorl %eax, %eax
 call printf@PLT
 jmp endif_0
 else_0:
endif_0:
.end_main:
leave
ret
.section .note.GNU-stack,"",@progbits
