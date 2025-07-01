.data
print_fmt: .string "%ld\n"
a: .quad 0
b: .quad 0
c: .quad 0
x: .quad 0
y: .quad 0
z: .quad 0
u: .quad 0
v: .quad 0
w: .quad 0
flag1: .quad 0
flag2: .quad 0
num1: .quad 0
num2: .quad 0
big1: .quad 0
big2: .quad 0
uns1: .quad 0
uns2: .quad 0
check: .quad 0
.text
 .globl main
main:
 pushq %rbp
 movq %rsp, %rbp
 movq $10, %rax
 movq %rax, a(%rip)
 movq $20, %rax
 negq %rax
 movq %rax, b(%rip)
 movq a(%rip), %rax
 pushq %rax
 movq b(%rip), %rax
 movq %rax, %rcx
 popq %rax
 addq %rcx, %rax
 movq %rax, c(%rip)
 movq $1000000000, %rax
 movq %rax, x(%rip)
 movq $2000000000, %rax
 negq %rax
 movq %rax, y(%rip)
 movq x(%rip), %rax
 pushq %rax
 movq $2, %rax
 movq %rax, %rcx
 popq %rax
 imulq %rcx, %rax
 movq %rax, z(%rip)
 movq $42, %rax
 movq %rax, u(%rip)
 movq $100, %rax
 movq %rax, v(%rip)
 movq v(%rip), %rax
 pushq %rax
 movq u(%rip), %rax
 movq %rax, %rcx
 popq %rax
 subq %rcx, %rax
 movq %rax, w(%rip)
 movq $1, %rax
 movq %rax, flag1(%rip)
 movq $0, %rax
 movq %rax, flag2(%rip)
 movq flag1(%rip), %rax
 pushq %rax
 movq flag2(%rip), %rax
 movq %rax, %rcx
 popq %rax
 andq %rcx, %rax
 movq %rax, check(%rip)
 movq $50, %rax
 movq %rax, num1(%rip)
 movq $30, %rax
 negq %rax
 movq %rax, num2(%rip)
 movq $3000000000, %rax
 movq %rax, big1(%rip)
 movq big1(%rip), %rax
 negq %rax
 movq %rax, big2(%rip)
 movq $65535, %rax
 movq %rax, uns1(%rip)
 movq uns1(%rip), %rax
 pushq %rax
 movq $2, %rax
 movq %rax, %rcx
 popq %rax
 cqto
 idivq %rcx
 movq %rax, uns2(%rip)
 movq a(%rip), %rax
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 xorl %eax, %eax
 call printf@PLT
 movq b(%rip), %rax
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 xorl %eax, %eax
 call printf@PLT
 movq c(%rip), %rax
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 xorl %eax, %eax
 call printf@PLT
 movq x(%rip), %rax
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 xorl %eax, %eax
 call printf@PLT
 movq y(%rip), %rax
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 xorl %eax, %eax
 call printf@PLT
 movq z(%rip), %rax
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 xorl %eax, %eax
 call printf@PLT
 movq u(%rip), %rax
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 xorl %eax, %eax
 call printf@PLT
 movq v(%rip), %rax
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 xorl %eax, %eax
 call printf@PLT
 movq w(%rip), %rax
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 xorl %eax, %eax
 call printf@PLT
 movq flag1(%rip), %rax
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 xorl %eax, %eax
 call printf@PLT
 movq flag2(%rip), %rax
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 xorl %eax, %eax
 call printf@PLT
 movq check(%rip), %rax
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 xorl %eax, %eax
 call printf@PLT
 movq num1(%rip), %rax
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 xorl %eax, %eax
 call printf@PLT
 movq num2(%rip), %rax
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 xorl %eax, %eax
 call printf@PLT
 movq big1(%rip), %rax
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 xorl %eax, %eax
 call printf@PLT
 movq big2(%rip), %rax
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 xorl %eax, %eax
 call printf@PLT
 movq uns1(%rip), %rax
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 xorl %eax, %eax
 call printf@PLT
 movq uns2(%rip), %rax
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 xorl %eax, %eax
 call printf@PLT
.end_main:
leave
ret
.section .note.GNU-stack,"",@progbits
