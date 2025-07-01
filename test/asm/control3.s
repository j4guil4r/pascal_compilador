.data
print_fmt: .string "%ld\n"
c: .quad 0
.text
 .globl main
main:
 pushq %rbp
 movq %rsp, %rbp
 movq $15, %rax
 movq %rax, c(%rip)
 movq c(%rip), %rax
 pushq %rax
 movq $10, %rax
 movq %rax, %rcx
 popq %rax
 cmpq %rcx, %rax
 setg %al
 movzbq %al, %rax
 cmpq $0, %rax
 je else_0
 movq c(%rip), %rax
 pushq %rax
 movq $20, %rax
 movq %rax, %rcx
 popq %rax
 cmpq %rcx, %rax
 setl %al
 movzbq %al, %rax
 cmpq $0, %rax
 je else_1
 movq $25, %rax
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 xorl %eax, %eax
 call printf@PLT
 jmp endif_1
 else_1:
endif_1:
 jmp endif_0
 else_0:
endif_0:
.end_main:
leave
ret
.section .note.GNU-stack,"",@progbits
