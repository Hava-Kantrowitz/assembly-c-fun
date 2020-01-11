
#include <stdio.h>
#include <stdlib.h>

long fib(long);

int
main(int argc, char* argv[])
{
    if (argc != 2) {
        printf("Usage:\n  %s N, where N > 0\n", argv[0]);
        return 0;
    }

    long x = atol(argv[1]);

    long fibResult = fib(x);

    printf("fib(%ld) = %ld\n", x, fibResult);
    return 0;

}

long fib(long fibNum) {
	if (fibNum == 0) {
		return 0;
	}
	if (fibNum == 1) {
		return 1;
	}
	long firstFib = fib(fibNum - 1);
	long secondFib = fib(fibNum - 2);
	return firstFib + secondFib;
}


