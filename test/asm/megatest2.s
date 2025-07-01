.data
print_fmt: .string "%ld\n"
n: .quad 0
i: .quad 0
fib1: .quad 0
fib2: .quad 0
limit: .quad 0
isPrimeFlag: .quad 0
.text
 .globl main
main:
 pushq %rbp
 movq %rsp, %rbp
 movq $30, %rax
 movq %rax, limit(%rip)
 movq limit(%rip), %rax
 movq %rax, %rdi
 call printPrimes
 movq $15, %rax
 movq %rax, %rdi
 call printFibonacci
 movq $10, %rax
 movq %rax, %rdi
 call fibonacci
 movq %rax, fib1(%rip)
 movq $15, %rax
 movq %rax, %rdi
 call fibonacci
 movq %rax, fib2(%rip)
 movq fib1(%rip), %rax
 movq %rax, %rdi
 call isPalindrome
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 xorl %eax, %eax
 call printf@PLT
 movq fib2(%rip), %rax
 movq %rax, %rdi
 call isPalindrome
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 xorl %eax, %eax
 call printf@PLT
 movq $20, %rax
 movq %rax, n(%rip)
 movq n(%rip), %rax
 movq %rax, %rdi
 call isPrime
 movq %rax, isPrimeFlag(%rip)
 movq isPrimeFlag(%rip), %rax
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
 movq %rax, i(%rip)
while_1:
 movq i(%rip), %rax
 pushq %rax
 movq $5, %rax
 movq %rax, %rcx
 popq %rax
 cmpq %rcx, %rax
 setl %al
 movzbq %al, %rax
 cmpq $0, %rax
 je endwhile_1
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
 jmp while_1
endwhile_1:
 movq $1, %rax
 movq %rax, %r12
 movq $0, %rax
 movq %rax, %r13
for_loop_2:
 cmpq %r13, %r12
 jl for_end_2
 movq %r12, i(%rip)
 movq i(%rip), %rax
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 xorl %eax, %eax
 call printf@PLT
 decq %r12
 jmp for_loop_2
for_end_2:
.end_main:
leave
ret
.globl isPrime
isPrime:
 pushq %rbp
 movq %rsp, %rbp
 mov %rdi, -8(%rbp)
 subq $24, %rsp
 movq -8(%rbp), %rax
 pushq %rax
 movq $1, %rax
 movq %rax, %rcx
 popq %rax
 cmpq %rcx, %rax
 setle %al
 movzbq %al, %rax
 cmpq $0, %rax
 je else_3
 movq $0, %rax
 movq %rax, -16(%rbp)
 jmp endif_3
 else_3:
 movq $1, %rax
 movq %rax, -16(%rbp)
 movq $2, %rax
 movq %rax, -24(%rbp)
while_4:
 movq -24(%rbp), %rax
 pushq %rax
 movq -24(%rbp), %rax
 movq %rax, %rcx
 popq %rax
 imulq %rcx, %rax
 pushq %rax
 movq -8(%rbp), %rax
 movq %rax, %rcx
 popq %rax
 cmpq %rcx, %rax
 setle %al
 movzbq %al, %rax
 cmpq $0, %rax
 je endwhile_4
 movq -8(%rbp), %rax
 pushq %rax
 movq -24(%rbp), %rax
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
 je else_5
 movq $0, %rax
 movq %rax, -16(%rbp)
 movq -8(%rbp), %rax
 movq %rax, -24(%rbp)
 jmp endif_5
 else_5:
endif_5:
 movq -24(%rbp), %rax
 pushq %rax
 movq $1, %rax
 movq %rax, %rcx
 popq %rax
 addq %rcx, %rax
 movq %rax, -24(%rbp)
 jmp while_4
endwhile_4:
endif_3:
 movq -16(%rbp), %rax
.end_isPrime:
leave
ret
.globl printPrimes
printPrimes:
 pushq %rbp
 movq %rsp, %rbp
 mov %rdi, -8(%rbp)
 subq $16, %rsp
 movq $2, %rax
 movq %rax, %r12
 movq -8(%rbp), %rax
 movq %rax, %r13
for_loop_6:
 cmpq %r13, %r12
 jg for_end_6
 movq %r12, -16(%rbp)
 movq -16(%rbp), %rax
 movq %rax, %rdi
 call isPrime
 cmpq $0, %rax
 je else_7
 movq -16(%rbp), %rax
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 xorl %eax, %eax
 call printf@PLT
 jmp endif_7
 else_7:
endif_7:
 incq %r12
 jmp for_loop_6
for_end_6:
.end_printPrimes:
leave
ret
.globl fibonacci
fibonacci:
 pushq %rbp
 movq %rsp, %rbp
 mov %rdi, -8(%rbp)
 subq $48, %rsp
 movq -8(%rbp), %rax
 pushq %rax
 movq $0, %rax
 movq %rax, %rcx
 popq %rax
 cmpq %rcx, %rax
 setle %al
 movzbq %al, %rax
 cmpq $0, %rax
 je else_8
 movq $0, %rax
 movq %rax, -16(%rbp)
 jmp endif_8
 else_8:
 movq -8(%rbp), %rax
 pushq %rax
 movq $1, %rax
 movq %rax, %rcx
 popq %rax
 cmpq %rcx, %rax
 sete %al
 movzbq %al, %rax
 cmpq $0, %rax
 je else_9
 movq $1, %rax
 movq %rax, -16(%rbp)
 jmp endif_9
 else_9:
 movq $0, %rax
 movq %rax, -24(%rbp)
 movq $1, %rax
 movq %rax, -32(%rbp)
 movq $2, %rax
 movq %rax, %r12
 movq -8(%rbp), %rax
 movq %rax, %r13
for_loop_10:
 cmpq %r13, %r12
 jg for_end_10
 movq %r12, -48(%rbp)
 movq -24(%rbp), %rax
 pushq %rax
 movq -32(%rbp), %rax
 movq %rax, %rcx
 popq %rax
 addq %rcx, %rax
 movq %rax, -40(%rbp)
 movq -32(%rbp), %rax
 movq %rax, -24(%rbp)
 movq -40(%rbp), %rax
 movq %rax, -32(%rbp)
 incq %r12
 jmp for_loop_10
for_end_10:
 movq -32(%rbp), %rax
 movq %rax, -16(%rbp)
endif_9:
endif_8:
 movq -16(%rbp), %rax
.end_fibonacci:
leave
ret
.globl printFibonacci
printFibonacci:
 pushq %rbp
 movq %rsp, %rbp
 mov %rdi, -8(%rbp)
 subq $16, %rsp
 movq $0, %rax
 movq %rax, %r12
 movq -8(%rbp), %rax
 pushq %rax
 movq $1, %rax
 movq %rax, %rcx
 popq %rax
 subq %rcx, %rax
 movq %rax, %r13
for_loop_11:
 cmpq %r13, %r12
 jg for_end_11
 movq %r12, -16(%rbp)
 movq -16(%rbp), %rax
 movq %rax, %rdi
 call fibonacci
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 xorl %eax, %eax
 call printf@PLT
 incq %r12
 jmp for_loop_11
for_end_11:
.end_printFibonacci:
leave
ret
.globl isPalindrome
isPalindrome:
 pushq %rbp
 movq %rsp, %rbp
 mov %rdi, -8(%rbp)
 subq $40, %rsp
 movq -8(%rbp), %rax
 movq %rax, -24(%rbp)
 movq $0, %rax
 movq %rax, -32(%rbp)
while_12:
 movq -8(%rbp), %rax
 pushq %rax
 movq $0, %rax
 movq %rax, %rcx
 popq %rax
 cmpq %rcx, %rax
 setg %al
 movzbq %al, %rax
 cmpq $0, %rax
 je endwhile_12
 movq -8(%rbp), %rax
 pushq %rax
 movq $10, %rax
 movq %rax, %rcx
 popq %rax
 cqto
 idivq %rcx
 movq %rdx, %rax
 movq %rax, -40(%rbp)
 movq -32(%rbp), %rax
 pushq %rax
 movq $10, %rax
 movq %rax, %rcx
 popq %rax
 imulq %rcx, %rax
 pushq %rax
 movq -40(%rbp), %rax
 movq %rax, %rcx
 popq %rax
 addq %rcx, %rax
 movq %rax, -32(%rbp)
 movq -8(%rbp), %rax
 pushq %rax
 movq $10, %rax
 movq %rax, %rcx
 popq %rax
 cqto
 idivq %rcx
 movq %rax, -8(%rbp)
 jmp while_12
endwhile_12:
 movq -24(%rbp), %rax
 pushq %rax
 movq -32(%rbp), %rax
 movq %rax, %rcx
 popq %rax
 cmpq %rcx, %rax
 sete %al
 movzbq %al, %rax
 movq %rax, -16(%rbp)
 movq -16(%rbp), %rax
.end_isPalindrome:
leave
ret
.section .note.GNU-stack,"",@progbits
