.data
print_fmt: .string "%ld\n"
x: .quad 0
y: .quad 0
z: .quad 0
.text
 .globl main
main:
 pushq %rbp
 movq %rsp, %rbp
 movq $10, %rax
 movq %rax, x(%rip)
 movq $20, %rax
 movq %rax, y(%rip)
 movq $30, %rax
 movq %rax, z(%rip)
 movq x(%rip), %rax
 pushq %rax
 movq y(%rip), %rax
 movq %rax, %rcx
 popq %rax
 cmpq %rcx, %rax
 setl %al
 movzbq %al, %rax
 pushq %rax
 movq y(%rip), %rax
 pushq %rax
 movq z(%rip), %rax
 movq %rax, %rcx
 popq %rax
 cmpq %rcx, %rax
 setle %al
 movzbq %al, %rax
 movq %rax, %rcx
 popq %rax
 andq %rcx, %rax
 pushq %rax
 movq z(%rip), %rax
 pushq %rax
 movq $0, %rax
 movq %rax, %rcx
 popq %rax
 cmpq %rcx, %rax
 setg %al
 movzbq %al, %rax
 movq %rax, %rcx
 popq %rax
 orq %rcx, %rax
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
