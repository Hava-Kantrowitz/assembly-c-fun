.global main 

.text

main:

  /* 
	Variable Mappings: 
	argc = %rdi
	argv = %rsi -> %r15
	x = %rbx
	fibResult = %r14

*/

  push %r15
  push %rbx
  push %r14
  enter $16, $0

  mov %rsi, %r15

  /*

  int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("Usage:...)
		return 0;
	}

	long x = atol(argv[1]);
	long fibResult = fib(x);
	printf("...");
	return 0;
	
  */

/*
	Checking args 
*/

  cmp $2, %rdi
  jne main_bad_args

/*
	Store argv[1] in variable, check if okay
*/

  mov 8(%r15), %rdi
  call atol
  mov %rax, %rbx

  cmp $0, %rbx 
  jge main_good_args
  
main_bad_args:
  mov $usagefmt, %rdi 
  call puts
  mov $1, %rax
  jmp main_done 


main_good_args:

/*Calling fibonacci*/

  mov %rbx, %rdi 
  call fib
  mov %rax, %r14

/*Print result */

  mov $printfmt, %rdi
  mov %rbx, %rsi
  mov %r14, %rdx
  mov $0, %al
  call printf

  mov $0, %rax


main_done:
  

  leave
  pop %r14
  pop %rbx
  pop %r15
  ret	

 
/*
	Variable Mappings:
	fibNum: %rdi --> %r12 --> %r11 (for temporary fib values)
	firstFib: %r13
*/

fib:
  push %r12
  push %r13
  enter $8, $0

  mov %rdi, %r12

  cmp $0, %r12
  je fib_is_zero

  cmp $1, %r12 
  je fib_is_one 


  /*If we get here, it is a num other than 1 or zero
  so we need the first and second fibonacci numbers*/

  /*First number*/

  mov %r12, %r11
  sub $1, %r11
  mov %r11, %rdi
  call fib 

  mov %rax, %r13

  mov %r12, %r11
  sub $2, %r11
  mov %r11, %rdi
  call fib 

  add %r13, %rax
  jmp fib_done


fib_is_zero:
  mov $0, %rax
  jmp fib_done

fib_is_one:
  mov $1, %rax

fib_done:
  leave
  pop %r13
  pop %r12
  ret 
  



.data
scanfmt: .string "%ld"
printfmt: .string "fib(%ld) = %ld\n"
usagefmt: .string "Usage:\n ./afib N, where N >= 0"
testfmt: .string "Testing\n"
