#include <stdio.h>

#include "../src/Position.h"
#include "unittest.h"

#include "position_test.h"

int tests_run = 0;

int
main(int ac, char **av)
{
	char *result = position_test_suite();
	printf("Number of tests ran: %d\n", tests_run);
	if (result)
		printf("FAILED: %s\n", result);
	else
		printf("All tests ran successfully.\n");
	// return 0 != result;
}
