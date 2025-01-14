#ifndef _POSITION_H_
#define _POSITION_H_

#include <stdbool.h>
#include <stdint.h>

#define Bitboard_t uint64_t

#define Optional(type)        \
	struct {              \
		bool present; \
		type value;   \
	}

typedef enum CastlingRights {
	NO_RIGHTS,
	q,
	k,
	kq,
	Q,
	Qq,
	Qk,
	Qkq,
	K,
	Kq,
	Kk,
	Kkq,
	KQ,
	KQq,
	KQk,
	KQkq,
} CastlingRights_t;

typedef enum PieceType {
	PAWN,
	ROOK,
	KNIGHT,
	BISHOP,
	QUEEN,
	KING,
} PieceType_t;

typedef enum Team {
	WHITE,
	BLACK,
} Team_t;

typedef struct Piece {
	PieceType_t type;
	Team_t team;
} Piece_t;

// Create a new Piece_t from a token in the string "PRNBQKprnbqk". If `token` is
// invalid, returns 1 and does not change `piece`.
int piece_init(Piece_t *piece, const char token);

// Convert a piece into its ASCII representation. Returns 0 if `piece` is invalid.
char piece_to_char(const Piece_t piece);

// The enum index represents the bitshift necessary to reach that square. This
// bitboard implementation follows the scheme listed here:
// https://www.chessprogramming.org/Efficient_Generation_of_Sliding_Piece_Attacks
typedef enum Square {
	// clang-format off
    A1, B1, C1, D1, E1, F1, G1, H1,
    A2, B2, C2, D2, E2, F2, G2, H2,
    A3, B3, C3, D3, E3, F3, G3, H3,
    A4, B4, C4, D4, E4, F4, G4, H4,
    A5, B5, C5, D5, E5, F5, G5, H5,
    A6, B6, C6, D6, E6, F6, G6, H6,
    A7, B7, C7, D7, E7, F7, G7, H7,
    A8, B8, C8, D8, E8, F8, G8, H8,
	// clang-format on
} Square_t;

// Allocate a string representing the square passed in. E4 -> "e4" for example.
char *square_to_string(const Square_t square);

// Unused. Maybe remove? Might turn out to be useful.
enum CastlingIndices {
	KINGSIDE,
	QUEENSIDE,
};

typedef struct Move {
	Square_t start;
	Square_t destination;
	Optional(PieceType_t) promotion_piece;
} Move_t;

// Allocate a string containing the UCI representation of a move.
char *move_to_string(const Move_t move);

// Encodes all information necessary to represent a single position. Each
// position also acts as the final node in a linked list of positions,
// representing a game history.
typedef struct Position {
	Bitboard_t piece_bitboards[12]; // [P, R, N, B, Q, K, p, r, n, b, q, k]
	Team_t turn;
	CastlingRights_t castling_rights;
	Optional(Square_t) en_passant_target;
	int half_moves;
	int full_moves;
	struct Position *prev_position;
} Position_t;

// Initialises an empty board with no pieces on it.
Position_t *position_init();

// Parses a FEN string into a game. This function does not check for board
// validity - it will happily parse a FEN representing an illegal position. If
// the FEN string is rejected for any reason, this function will return a
// number between 1 and 7 inclusive, representing the field of the FEN that
// wouldn't parse, with 7 representing a length/form problem. The original game
// struct will not have been edited in any way unless every field parses
// correctly. On success, it will return 0. It will also reset any move history
// i.e. prev_position is set to NULL.
int position_parse_fen(Position_t *position, const char *orig_fen);

// Pretty-print a representation of `position` to standard output.
void position_show(Position_t *position);

// Flip the turn of a position.
void position_flip_turn(Position_t *position);

#endif