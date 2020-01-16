#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char* argv[])
{
	if (argc != 4) {
		printf("Usage:\n %s N op N\n", argv[0]);
		return 1;
	}

	long result;
	long x = atol(argv[1]);
	long y = atol(argv[3]);

	if (strcmp(argv[2], "+") == 0) {
		result = x + y;
	}

	else if (strcmp(argv[2], "-") == 0) {
		result = x - y;
	}

	else if (strcmp(argv[2], "*") == 0) {
		result = x * y;
	}

	else if (strcmp(argv[2], "/") == 0) {
		result = x / y;
	}

	else {
		printf("Usage:\n %s N op N\n", argv[2]);
		return 1;
	}

	printf("%ld %s %ld = %ld\n", x, argv[2], y, result);
	return 0;
}
