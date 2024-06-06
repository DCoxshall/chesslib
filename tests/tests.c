#include <stdio.h>

#include "../src/Position.h"
#include "minunit.h"

int tests_run = 0;

char *
test_piece_init()
{
	Piece_t piece;
	int res = piece_init(&piece, 'K');
	MU_ASSERT("Test piece_init", res == 1);
    return 0;
}

char *
test_suite()
{
	MU_RUN_TEST(test_piece_init);
    return 0;
}

int
main(int ac, char **av)
{
	char *result = test_suite();
	printf("Number of tests run: %d\n", tests_run);
	if (result)
		printf("FAIL: %s\n", result);
	// return 0 != result;
}
