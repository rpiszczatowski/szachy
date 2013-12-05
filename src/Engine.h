#pragma once
#include <list>

#include "Board.h"
#include "Move.h"

class Engine {
public:
    using PairList = std::list<std::pair<uint8_t, uint8_t>>;
    Board board;
    Move moves[1024];
    static Move *generateMoves(Board &board, Move *startMove);
    static Move *movesOfShortDistancePiece(Board &board, uint8_t square, uint64_t mask, Move *startMove);
    static Move *movesOfLongDistancePiece(Board &board, uint8_t square, uint64_t mask[64][4], Move *startMove);
    template <Color color>
    static Move *generatePawnMoves(Board &board, uint8_t square, Move *startMove);
    static Move *generateKnightMoves(Board &board, uint8_t square, Move *startMove);
    static Move *generateBishopMoves(Board &board, uint8_t square, Move *startMove);
    static Move *generateRookMoves(Board &board, uint8_t square, Move *startMove);
    static Move *generateQueenMoves(Board &board, uint8_t square, Move *startMove);
    static Move *generateKingMoves(Board &board, uint8_t square, Move *startMove);

    static void fillMoveFlags(Board &board, Move &m);

    static uint64_t knightBitmask[64];
    static uint64_t bishopBitmask[64][4];
    static uint64_t rookBitmask[64][4];
    static uint64_t kingBitmask[64];
    static uint64_t pawnBitmask[2][64];
    static uint64_t maskOfShortDistancePiece(uint8_t square, const PairList &list);
    static void maskOfLongDistancePiece(uint8_t square, uint64_t array[4], const PairList &list);
    static uint64_t knightMask(uint8_t square);
    static uint64_t pawnMask(uint8_t square, Color pawnColor);
    static void bishopMask(uint8_t square, uint64_t array[4]);
    static void rookMask(uint8_t square, uint64_t array[4]);
    static uint64_t kingMask(uint8_t square);
    // do not check if king is attaking square
    static bool isSquareAttacked(Board &board, uint8_t square, Color color);
    static void setupFenPosition(Board &board, std::list<std::string> fenPosition);
    void setupFenPosition(std::list<std::string> fenPosition);
    static void initBitmasks();
public:
    static void init();
    void reset();
    // assume that from, to are set, rest fields will be set by engine
    void move(const std::string &move);
    void move(const std::list<std::string> &moves);
    static bool isMoveValid(Board &board, const Move &m);
    Move go();
};
