#ifndef _POSITION_H_
#define _POSITION_H_

#include <stdbool.h>
#include <stdint.h>

#define Bitboard_t uint64_t

typedef enum PieceType {
	PAWN,
	ROOK,
	KNIGHT,
	BISHOP,
	QUEEN,
	KING,
} PieceType_t;

/* The enum index represents the bitshift necessary to reach that square. */
typedef enum Square {
	NONE = -1,
	// clang-format off
	A1, A2, A3, A4, A5, A6, A7, A8, 
	B1, B2, B3, B4, B5, B6, B7, B8, 
	C1, C2, C3, C4, C5, C6, C7, C8, 
	D1, D2, D3, D4, D5, D6, D7, D8, 
	E1, E2, E3, E4, E5, E6, E7, E8, 
	F1, F2, F3, F4, F5, F6, F7, F8, 
	G1, G2, G3, G4, G5, G6, G7, G8, 
	H1, H2, H3, H4, H5, H6, H7, H8,
	// clang-format on
} Square_t;

enum CastlingIndices {
	KINGSIDE,
	QUEENSIDE,
};

typedef enum Team {
	WHITE,
	BLACK,
} Team;

typedef struct Move {
	Square_t start;
	Square_t destination;
	PieceType_t promotion_piece;
} Move_t;

/* Encodes all information necessary to represent a single position. */
typedef struct Position {
	Bitboard_t piece_bitboards[12];
	Team turn;
	bool castling_rights[2][2];
	Square_t en_passant_target;
	int half_moves;
	int full_moves;
} Position_t;

/* Initialises an empty board with no pieces on it. */
Position_t position_init();

int position_place_piece(Position_t *position, Square_t square, char piece);

#endif