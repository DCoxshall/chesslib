#include <stdio.h>

#include "unittest.h"
#include "../src/Position.h"

char *
test_piece_init()
{
	// Idea here is to test that each token in `tokens` produces the correct
	// piece.
	Piece_t piece;
	int flag = 0;
	char *tokens = "PRNBQKprnbqk";
    for (int i = 0; i < 12; i++) {
        int res = piece_init(&piece, tokens[i]);
        flag += res;
        if (piece.team != i / 6 || piece.type != i % 6)
            flag++;
    }
	ASSERT("test_piece_init", flag == 0);
	return 0;
}

char *
position_test_suite()
{
	RUN_TEST(test_piece_init);
	return 0;
}