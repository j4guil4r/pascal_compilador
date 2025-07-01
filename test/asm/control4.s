.data
print_fmt: .string "%ld\n"
i: .quad 0
.text
 .globl main
main:
 pushq %rbp
 movq %rsp, %rbp
 movq $0, %rax
 movq %rax, i(%rip)
while_0:
 movq i(%rip), %rax
 pushq %rax
 movq $5, %rax
 movq %rax, %rcx
 popq %rax
 cmpq %rcx, %rax
 setl %al
 movzbq %al, %rax
 cmpq $0, %rax
 je endwhile_0
 movq i(%rip), %rax
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 xorl %eax, %eax
 call printf@PLT
 movq i(%rip), %rax
 pushq %rax
 movq $1, %rax
 movq %rax, %rcx
 popq %rax
 addq %rcx, %rax
 movq %rax, i(%rip)
 jmp while_0
endwhile_0:
.end_main:
leave
ret
.section .note.GNU-stack,"",@progbits
