.data
print_fmt: .string "%ld\n"
i: .quad 0
j: .quad 0
k: .quad 0
counter: .quad 0
flag: .quad 0
.text
 .globl main
main:
 pushq %rbp
 movq %rsp, %rbp
 movq $1, %rax
 movq %rax, i(%rip)
 movq $0, %rax
 movq %rax, counter(%rip)
 movq $1, %rax
 movq %rax, flag(%rip)
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
 movq %rax, %r12
 movq $4, %rax
 movq %rax, %r13
for_loop_1:
 cmpq %r13, %r12
 jg for_end_1
 movq %r12, j(%rip)
 movq $5, %rax
 movq %rax, k(%rip)
while_2:
 movq k(%rip), %rax
 pushq %rax
 movq $1, %rax
 movq %rax, %rcx
 popq %rax
 cmpq %rcx, %rax
 setge %al
 movzbq %al, %rax
 cmpq $0, %rax
 je endwhile_2
 movq i(%rip), %rax
 pushq %rax
 movq $2, %rax
 movq %rax, %rcx
 popq %rax
 cqto
 idivq %rcx
 movq %rdx, %rax
 pushq %rax
 movq $0, %rax
 movq %rax, %rcx
 popq %rax
 cmpq %rcx, %rax
 sete %al
 movzbq %al, %rax
 pushq %rax
 movq flag(%rip), %rax
 movq %rax, %rcx
 popq %rax
 andq %rcx, %rax
 cmpq $0, %rax
 je else_3
 movq counter(%rip), %rax
 pushq %rax
 movq i(%rip), %rax
 pushq %rax
 movq j(%rip), %rax
 movq %rax, %rcx
 popq %rax
 imulq %rcx, %rax
 pushq %rax
 movq k(%rip), %rax
 movq %rax, %rcx
 popq %rax
 imulq %rcx, %rax
 movq %rax, %rcx
 popq %rax
 addq %rcx, %rax
 movq %rax, counter(%rip)
 movq counter(%rip), %rax
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 xorl %eax, %eax
 call printf@PLT
 jmp endif_3
 else_3:
 movq counter(%rip), %rax
 pushq %rax
 movq $1, %rax
 movq %rax, %rcx
 popq %rax
 addq %rcx, %rax
 movq %rax, counter(%rip)
 movq counter(%rip), %rax
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 xorl %eax, %eax
 call printf@PLT
endif_3:
 movq k(%rip), %rax
 pushq %rax
 movq $1, %rax
 movq %rax, %rcx
 popq %rax
 subq %rcx, %rax
 movq %rax, k(%rip)
 jmp while_2
endwhile_2:
 movq flag(%rip), %rax
 notq %rax
 movq %rax, flag(%rip)
 incq %r12
 jmp for_loop_1
for_end_1:
 movq i(%rip), %rax
 pushq %rax
 movq $1, %rax
 movq %rax, %rcx
 popq %rax
 addq %rcx, %rax
 movq %rax, i(%rip)
 jmp while_0
endwhile_0:
 movq $3, %rax
 movq %rax, %r12
 movq $1, %rax
 movq %rax, %r13
for_loop_4:
 cmpq %r13, %r12
 jl for_end_4
 movq %r12, i(%rip)
 movq i(%rip), %rax
 movq %rax, j(%rip)
while_5:
 movq j(%rip), %rax
 pushq %rax
 movq $0, %rax
 movq %rax, %rcx
 popq %rax
 cmpq %rcx, %rax
 setg %al
 movzbq %al, %rax
 cmpq $0, %rax
 je endwhile_5
 movq i(%rip), %rax
 pushq %rax
 movq j(%rip), %rax
 movq %rax, %rcx
 popq %rax
 imulq %rcx, %rax
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 xorl %eax, %eax
 call printf@PLT
 movq j(%rip), %rax
 pushq %rax
 movq $1, %rax
 movq %rax, %rcx
 popq %rax
 subq %rcx, %rax
 movq %rax, j(%rip)
 jmp while_5
endwhile_5:
 decq %r12
 jmp for_loop_4
for_end_4:
.end_main:
leave
ret
.section .note.GNU-stack,"",@progbits
