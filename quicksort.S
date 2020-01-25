.global main
.data
bad_input: .string "bad input"
printfmt: .string "%ld\n"
loop_printfmt: .string "%ld "
newline: .string "\n"
scanfmt: .string "%ld"
teststring: .string "got here\n"

.text

/*
	Variable Mappings:
		xs = %rdi
		ii = %rsi
		jj = %rdx
		tmp = %r9
		tmp2 = %r10
*/
swap:
  enter $0, $0

  cmp %rdx, %rsi
  je swap_end

  lea (%rdi, %rsi, 8), %r9
  lea (%rdi, %rdx, 8), %r10

  mov %r10, (%rdi, %rsi, 8)
  mov %r9, (%rdi, %rdx, 8)
  

swap_end:

  leave
  ret

/*
	Variable Mappings:
		xs = %r12
		lo = %r13
		hi = %r14
		ii = %r15
		jj = %rbx
		pivot = %r9
*/
partition:
  push %r12
  push %r13
  push %r14
  push %r15
  push %rbx
  enter $8, $0

  mov %rdi, %r12
  mov %rsi, %r13
  mov %rdx, %r14

  dec %r14

  lea (%r12, %r14, 8), %r10
  mov (%r10), %r9
  
  mov %r13, %r15
  mov %r13, %rbx

pivot_loop_cond:
  cmp %r14, %rbx
  jge pivot_loop_end

  lea (%r12, %rbx, 8), %r10
  cmp %r9, (%r10)
  jge pivot_outer_loop

  mov %r12, %rdi
  mov %r15, %rsi
  mov %rbx, %rdx
  call swap

  inc %r15

pivot_outer_loop:
  inc %rbx
  jmp pivot_loop_cond

pivot_loop_end:

  mov %r12, %rdi
  mov %r15, %rsi
  mov %r14, %rdx
  call swap

  mov %r15, %rax

  leave
  pop %rbx
  pop %r15
  pop %r14
  pop %r13
  pop %r12
  ret

/*
	Variable Mappings:
		xs = %r12
		lo = %r13
		hi = %r14
		pp = %r15
*/
quicksort:
  push %r12
  push %r13
  push %r14
  push %r15
  enter $16, $0

  mov %rdi, %r12
  mov %rsi, %r13
  mov %rdx, %r14

  /*Subtract lo from hi, perform comparison, then add it back*/
  sub %r13, %r14
  cmp $1, %r14
  jl quicksort_end
  add %r13, %r14

  /*xs, lo, and hi are still in rdi, rsi, rdx, so can call directly*/
  call partition
  mov %rax, %r15

  /*mov xs, lo,  pp into calling registers*/
  mov %r12, %rdi
  mov %r13, %rsi
  mov %r15, %rdx
  call quicksort

  /*move xs, move/increase pp and move hi*/
  mov %r12, %rdi
  inc %r15
  mov %r15, %rsi
  mov %r14, %rdx
  call quicksort
  

quicksort_end: 
  leave
  pop %r15
  pop %r14
  pop %r13
  pop %r12
  ret

/*
	Variable Mappings:
		ptr = %rdi --> %r10 --> %rax
*/
read_int:
  enter $0, $0

  mov %rdi, %r10

  mov $scanfmt, %rdi
  mov %r10, %rsi 
  mov $0, %al
  call scanf 

  cmp $1, %rax
  je args_good

  mov $bad_input, %rdi
  call puts

  mov $1, %rdi
  call exit 
  

args_good:

  leave
  ret

/*
	Variable Mappings:
		nn = on stack --> %r12
		xs = %r13
		ii = %r14
		temp var for storing const 8 --> %r10
*/
main:
  push %r12
  push %r13
  push %r14
  enter $8, $0

  /*Getting the first input*/
  lea (%rsp), %rdi 
  call read_int
  mov %rsp, %r12
  mov (%r12), %rax

  /*Calculating size of a long*/
  mov $8, %r10
  imul %r10 

  /*Allocating heap space for array*/
  mov %rax, %rdi
  call malloc
  mov %rax, %r13 

  /*Loop to get inputs for array*/
  mov $0, %r14
read_loop_cond:
  cmp (%r12), %r14
  jge read_loop_done

  lea (%r13, %r14, 8), %rdi  
  call read_int

  inc %r14
  jmp read_loop_cond

read_loop_done:
  
  lea (%r13), %rdi
  mov $0, %rsi
  mov (%r12), %rdx
  call quicksort

  mov $printfmt, %rdi
  mov (%r12), %rsi
  mov $0, %al
  call printf

  /*Print loop*/
mov $0, %r14
print_loop_cond:

  cmp (%r12), %r14
  jge print_loop_done

  mov $loop_printfmt, %rdi
  lea (%r13, %r14, 8), %r9
  mov (%r9), %rsi
  mov $0, %al
  call printf

  inc %r14
  jmp print_loop_cond
  

print_loop_done:

  mov $newline, %rdi
  mov $0, %al
  call printf 

  mov %r13, %rdi
  call free

  mov $0, %rax


  leave
  pop %r14
  pop %r13
  pop %r12
  ret

