.global main 

.text 

/*
	Variable Mappings: 
	argc = %rdi 
	argv = %rsi -> %r15
	x = %r12
	y = %r13
	op = %r14
	result = %r10

*/
main: 

  push %r15
  push %r14
  push %r13
  push %r12
  enter $16, $0

  /*Check for right number of args*/
  cmp $4, %rdi 
  jne main_bad_args

  mov %rsi, %r15

  /*Get x and y from argv*/
  mov 8(%r15), %rdi 
  call atol 
  mov %rax, %r12
  
  mov 24(%r15), %rdi
  call atol
  mov %rax, %r13 

  /*Get op from argv*/
  mov 16(%r15), %r14 

  /*Use strcmp to compare the operations*/

  mov %r14, %rdi
  mov $plus, %rsi
  call strcmp
  cmp $0, %rax 
  je add_op

  mov %r14, %rdi 
  mov $minus, %rsi 
  call strcmp 
  cmp $0, %rax
  je sub_op

  mov %r14, %rdi
  mov $mult, %rsi
  call strcmp
  cmp $0, %rax
  je mult_op

  mov %r14, %rdi
  mov $div, %rsi
  call strcmp
  cmp $0, %rax
  je div_op

main_bad_args:
  mov $usagefmt, %rdi
  call puts
  mov $1, %rax
  jmp main_done

add_op:
  mov %r12, %r10
  add %r13, %r10
  jmp main_good_args

sub_op:
  mov %r12, %r10
  sub %r13, %r10
  jmp main_good_args

mult_op:
  mov %r12, %r10
  imul %r13, %r10
  jmp main_good_args

div_op:
  mov %r12, %rax
  mov %r13, %r10
  idiv %r10
  mov %rax, %r10

main_good_args:
  
  mov $printfmt, %rdi
  mov %r12, %rsi 
  mov %r14, %rdx
  mov %r13, %rcx
  mov %r10, %r8
  mov $0, %al
  call printf

  mov $0, %rax

main_done: 

  leave
  pop %r12
  pop %r13
  pop %r14
  pop %r15 
  ret

.data 
usagefmt: .string "Usage:\n ./acalc N op N"
printfmt: .string "%ld %s %ld = %ld\n" 
plus: .string "+"
minus: .string "-"
mult: .string "*"
div: .string "/"
