#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/Position.h"
#include "unittest.h"

#define POSITION_SUITE_NAME "POSITION"

static char *
test_piece_init()
{
	// Idea here is to test that each token in `tokens` produces the correct
	// piece - iterate through tokens and compare to each piece.
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

static char *
test_piece_to_char()
{
	Piece_t piece;
	char *tokens = "PRNBQKprnbqk";
	int flag = 0;
	for (int i = 0; i < 12; i++) {
		piece_init(&piece, tokens[i]);
		char c = piece_to_char(piece);
		if (c != tokens[i])
			flag++;
	}
	ASSERT("test_piece_to_char", flag == 0);
	return 0;
}

static char *
test_square_to_string()
{
	char ranks[] = "abcdefgh";
	char files[] = "12345678";
	int flag = 0;
	for (Square_t square = A1; square <= H8; square++) {
		char *res = square_to_string(square);
		char should[3];
		should[0] = ranks[square % 8];
		should[1] = files[square / 8];
		should[2] = 0;
		if (strcmp(res, should))
			flag++;
	}
	ASSERT("test_square_to_string", flag == 0);
	return 0;
}

static char *
test_move_to_string()
{
	// e2e4
	Move_t move = { .destination = E4,
		.start = E2,
		.promotion_piece.present = false };
	char *res = move_to_string(move);
	ASSERT("test_move_to_string", !strcmp("e2e4", res));
	free(res);

	// e7e8q
	move.destination = E8;
	move.start = E7;
	move.promotion_piece.present = true;
	move.promotion_piece.value = QUEEN;
	res = move_to_string(move);
	printf("%s\n", res);
	ASSERT("test_move_to_string", !strcmp("e7e8q", res));
	free(res);
	return 0;
}

static char *
test_position_parse_fen()
{
	// Starting position
	Position_t *position = position_init();
	position_parse_fen(position,
	    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    bool flag = false;

    Bitboard_t target_bitboards[12] = {
        0x000000000000FF00,
        0x0000000000000081,
        0x0000000000000042,
        0x0000000000000024,
        0x0000000000000008,
        0x0000000000000010,
        0xFF00000000000000,
        
    };

    for (int i = 0; i < 12; i++)
        printf("%lu\n", position->piece_bitboards[i]);

    return 0;
}

char *
position_test_suite()
{
	RUN_TEST(test_piece_init);
	RUN_TEST(test_piece_to_char);
	RUN_TEST(test_square_to_string);
	RUN_TEST(test_move_to_string);
    RUN_TEST(test_position_parse_fen);
	return 0;
}