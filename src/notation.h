#pragma once

#include <iostream>
#include <string>

#include "asserts.h"
#include "bit.h"

inline bool inRange(uint_fast8_t _rank, uint_fast8_t _file) {
    return _rank < 8 && _file < 8;
}

inline uint_fast8_t notation2Number(const std::string &s) {
    return (s[0] - 'a') + (s[1] - '1') * 8;
}

// kolumny od 0 do 7
inline uint_fast8_t file(uint_fast8_t number) {
    ASSERT(/*number >= 0 && */number < 64, number);
    return number & 7;
}

// wiersze od 0 do 7 (0 -> 'a', 1 -> 'b' ...)
inline uint_fast8_t rank(uint_fast8_t number) {
    ASSERT(/*number >= 0 && */number < 64, number);
    return number >> 3;
}

inline uint_fast8_t number(uint_fast8_t rank, uint_fast8_t file) {
    ASSERT(/*rank >= 0 && */rank < 8/* && file >= 0 */&& file < 8, rank, file);
    return (rank << 3) + file;
}

inline Color color(uint_fast8_t number) {
    ASSERT(/*number >= 0 && */number < 64, number);
    return number & 1 ? Color::white : Color::black;
}

inline Color color(uint_fast8_t rank, uint_fast8_t file) {
    ASSERT(/*rank >= 0 && */rank < 8/* && file >= 0 */&& file < 8, rank, file);
    return rank + file & 1 ? Color::white : Color::black;
}

inline bool isWhite(uint_fast8_t rank, uint_fast8_t file) {
    ASSERT(/*rank >= 0 &&*/ rank < 8 && /*file >= 0 && */file < 8, rank, file);
    return color(rank, file) == Color::white;
}

inline std::string number2Notation(uint_fast8_t pos) {
    char ans[3] = "\0\0";
    ans[0] = 'a' + rank(pos);
    ans[1] = '1' + file(pos);
    return ans;
}

inline char piece2Notation(Piece piece, Color color) {
    char ret;
    switch (piece) {
    case Piece::pawn:
        ret = 'P';
        break;
    case Piece::knight:
        ret = 'N';
        break;
    case Piece::bishop:
        ret = 'B';
        break;
    case Piece::rook:
        ret = 'R';
        break;
    case Piece::queen:
        ret = 'Q';
        break;
    case Piece::king:
        ret = 'K';
        break;
    default:
        ASSERT(false, piece);
        ret = ' ';
    }
    if (color == Color::white) {
        ret += 'a' - 'A';
    }
    return ret;
}

inline Piece notation2Piece(char notation) {
    switch (notation) {
    case 'p':
    case 'P':
        return Piece::pawn;
    case 'n':
    case 'N':
        return Piece::knight;
    case 'b':
    case 'B':
        return Piece::bishop;
    case 'r':
    case 'R':
        return Piece::rook;
    case 'q':
    case 'Q':
        return Piece::queen;
    case 'k':
    case 'K':
        return Piece::king;
    }
    ASSERT(false, notation);
    return Piece::empty;
}

inline Move parseMove(const std::string &move) {
    Move m;
    m.from = notation2Number(move.substr(0, 2));
    m.to = notation2Number(move.substr(2, 2));
    if (move.length() == 5) {
        ASSERT(m.to > 56 && m.to < 64, move);
        m.flags = piece2promotion(notation2Piece(move[4]));
    }
    return m;
}

inline void printBitmaskAsBoard(uint64_t bitmask, std::ostream &stream) {
    for (uint_fast8_t rank = 7; rank < 8; --rank) {
        for (uint_fast8_t file = 0; file < 8; ++file) {
            stream << (bit::isSet(bitmask, number(rank, file)) ? "1" : "0");
        }
        stream << std::endl;
    }
}