#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#include "Position.h"

Position_t
position_init()
{
	Position_t new_pos;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 6; j++) {
			new_pos.piece_bitboards[i][j] = 0;
		}
	}
	new_pos.turn = WHITE;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			new_pos.castling_rights[i][j] = true;
		}
	}
	new_pos.en_passant_target = NONE;
	new_pos.half_moves = 0;
	new_pos.full_moves = 0;
	return new_pos;
}
