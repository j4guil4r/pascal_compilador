.data
print_fmt: .string "%ld\n"
i: .quad 0
j: .quad 0
.text
 .globl main
main:
 pushq %rbp
 movq %rsp, %rbp
 movq $1, %rax
 movq %rax, i(%rip)
while_0:
 movq i(%rip), %rax
 pushq %rax
 movq $3, %rax
 movq %rax, %rcx
 popq %rax
 cmpq %rcx, %rax
 setle %al
 movzbq %al, %rax
 cmpq $0, %rax
 je endwhile_0
 movq $1, %rax
 movq %rax, j(%rip)
while_1:
 movq j(%rip), %rax
 pushq %rax
 movq $3, %rax
 movq %rax, %rcx
 popq %rax
 cmpq %rcx, %rax
 setle %al
 movzbq %al, %rax
 cmpq $0, %rax
 je endwhile_1
 movq j(%rip), %rax
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 xorl %eax, %eax
 call printf@PLT
 movq j(%rip), %rax
 pushq %rax
 movq $1, %rax
 movq %rax, %rcx
 popq %rax
 addq %rcx, %rax
 movq %rax, j(%rip)
 jmp while_1
endwhile_1:
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
