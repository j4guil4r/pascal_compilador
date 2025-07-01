.data
print_fmt: .string "%ld\n"
x: .quad 0
y: .quad 0
z: .quad 0
i: .quad 0
counter: .quad 0
flag: .quad 0
.text
 .globl main
main:
 pushq %rbp
 movq %rsp, %rbp
 movq $10, %rax
 movq %rax, x(%rip)
 movq $3, %rax
 movq %rax, y(%rip)
 movq x(%rip), %rax
 pushq %rax
 movq y(%rip), %rax
 movq %rax, %rcx
 popq %rax
 cqto
 idivq %rcx
 movq %rax, z(%rip)
 movq z(%rip), %rax
 movq %rax, %rdi
 call print_result
 movq x(%rip), %rax
 pushq %rax
 movq y(%rip), %rax
 movq %rax, %rcx
 popq %rax
 cqto
 idivq %rcx
 movq %rdx, %rax
 movq %rax, z(%rip)
 movq z(%rip), %rax
 movq %rax, %rdi
 call print_result
 movq x(%rip), %rax
 negq %rax
 pushq %rax
 movq y(%rip), %rax
 movq %rax, %rcx
 popq %rax
 cqto
 idivq %rcx
 movq %rdx, %rax
 movq %rax, z(%rip)
 movq z(%rip), %rax
 movq %rax, %rdi
 call print_result
 movq x(%rip), %rax
 pushq %rax
 movq y(%rip), %rax
 movq %rax, %rcx
 popq %rax
 imulq %rcx, %rax
 pushq %rax
 movq $5, %rax
 movq %rax, %rcx
 popq %rax
 addq %rcx, %rax
 movq %rax, z(%rip)
 movq z(%rip), %rax
 movq %rax, %rdi
 call print_result
 movq x(%rip), %rax
 pushq %rax
 movq y(%rip), %rax
 movq %rax, %rcx
 popq %rax
 cmpq %rcx, %rax
 setg %al
 movzbq %al, %rax
 pushq %rax
 movq z(%rip), %rax
 pushq %rax
 movq $0, %rax
 movq %rax, %rcx
 popq %rax
 cmpq %rcx, %rax
 setne %al
 movzbq %al, %rax
 movq %rax, %rcx
 popq %rax
 andq %rcx, %rax
 movq %rax, flag(%rip)
 movq flag(%rip), %rax
 cmpq $0, %rax
 je else_0
 movq $1, %rax
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 xorl %eax, %eax
 call printf@PLT
 jmp endif_0
 else_0:
 movq $0, %rax
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 xorl %eax, %eax
 call printf@PLT
endif_0:
 movq $0, %rax
 movq %rax, counter(%rip)
 movq $1, %rax
 movq %rax, %r12
 movq $5, %rax
 movq %rax, %r13
for_loop_1:
 cmpq %r13, %r12
 jg for_end_1
 movq %r12, i(%rip)
while_2:
 movq counter(%rip), %rax
 pushq %rax
 movq i(%rip), %rax
 movq %rax, %rcx
 popq %rax
 cmpq %rcx, %rax
 setl %al
 movzbq %al, %rax
 cmpq $0, %rax
 je endwhile_2
 movq counter(%rip), %rax
 pushq %rax
 movq $1, %rax
 movq %rax, %rcx
 popq %rax
 addq %rcx, %rax
 movq %rax, counter(%rip)
 jmp while_2
endwhile_2:
 incq %r12
 jmp for_loop_1
for_end_1:
 movq $5, %rax
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 xorl %eax, %eax
 call printf@PLT
 movq counter(%rip), %rax
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 xorl %eax, %eax
 call printf@PLT
 movq x(%rip), %rax
 movq %rax, %rdi
 movq y(%rip), %rax
 movq %rax, %rsi
 call max
 movq %rax, z(%rip)
 movq z(%rip), %rax
 movq %rax, %rdi
 call print_result
 movq z(%rip), %rax
 movq %rax, %rdi
 movq $100, %rax
 movq %rax, %rsi
 call max
 movq %rax, %rdi
 call print_result
 movq x(%rip), %rax
 pushq %rax
 movq $0, %rax
 movq %rax, %rcx
 popq %rax
 cmpq %rcx, %rax
 setg %al
 movzbq %al, %rax
 cmpq $0, %rax
 je else_3
 movq y(%rip), %rax
 pushq %rax
 movq $5, %rax
 movq %rax, %rcx
 popq %rax
 cmpq %rcx, %rax
 setl %al
 movzbq %al, %rax
 cmpq $0, %rax
 je else_4
 movq $6666, %rax
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 xorl %eax, %eax
 call printf@PLT
 jmp endif_4
 else_4:
 movq $555555, %rax
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 xorl %eax, %eax
 call printf@PLT
endif_4:
 jmp endif_3
 else_3:
 movq $222222, %rax
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 xorl %eax, %eax
 call printf@PLT
endif_3:
 movq $333333333, %rax
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 xorl %eax, %eax
 call printf@PLT
 movq $10, %rax
 negq %rax
 movq %rax, %r12
 movq $10, %rax
 movq %rax, %r13
for_loop_5:
 cmpq %r13, %r12
 jg for_end_5
 movq %r12, i(%rip)
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
 cmpq $0, %rax
 je else_6
 movq i(%rip), %rax
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 xorl %eax, %eax
 call printf@PLT
 movq $0, %rax
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 xorl %eax, %eax
 call printf@PLT
 jmp endif_6
 else_6:
 movq i(%rip), %rax
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 xorl %eax, %eax
 call printf@PLT
 movq $1, %rax
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 xorl %eax, %eax
 call printf@PLT
endif_6:
 incq %r12
 jmp for_loop_5
for_end_5:
.end_main:
leave
ret
.globl max
max:
 pushq %rbp
 movq %rsp, %rbp
 mov %rdi, -8(%rbp)
 mov %rsi, -16(%rbp)
 subq $24, %rsp
 movq -8(%rbp), %rax
 pushq %rax
 movq -16(%rbp), %rax
 movq %rax, %rcx
 popq %rax
 cmpq %rcx, %rax
 setg %al
 movzbq %al, %rax
 cmpq $0, %rax
 je else_7
 movq -8(%rbp), %rax
 movq %rax, -24(%rbp)
 jmp endif_7
 else_7:
 movq -16(%rbp), %rax
 movq %rax, -24(%rbp)
endif_7:
 movq -24(%rbp), %rax
.end_max:
leave
ret
.globl print_result
print_result:
 pushq %rbp
 movq %rsp, %rbp
 mov %rdi, -8(%rbp)
 subq $8, %rsp
 movq -8(%rbp), %rax
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 xorl %eax, %eax
 call printf@PLT
.end_print_result:
leave
ret
.section .note.GNU-stack,"",@progbits
