.global main 

.text

main:
  enter $16, $0;

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

  mov $scanfmt, %rdi
  lea (%rsp), %rsi
  mov $0, %al
  call scanf

  mov (%rsp), %rdi
  call fib

  mov $printfmt, %rdi



.data
scanfmt: .string "%ld"
printfmt: .string "fib(%ld) = %ld\n"
