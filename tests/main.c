#include <stdio.h>

#include "../src/Position.h"
#include "position_test.h"
#include "unittest.h"

int tests_run = 0;

void
run_suite(char *(*suite_function)(), char *suite_name)
{
	printf("Running suite %s\n", POSITION_SUITE_NAME);
	char *result = suite_function();
	printf("Number of tests ran: %d\n", tests_run);
	if (result) {
		printf("FAILED: %s\n", result);
	} else {
		printf("All tests in suite %s ran successfully.\n",
		    POSITION_SUITE_NAME);
	}
	tests_run = 0;
}

int
main(int ac, char **av)
{
	run_suite(position_test_suite, POSITION_SUITE_NAME);
}
