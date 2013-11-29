#include "unitTests.h"
#include "Board.h"
#include "Move.h"
#include "notation.h"
#include "Engine.h"
#include <list>
#include <iostream>

void testMove(Board &b, const Move &m) {
    std::cerr << std::endl << "make move" << m << std::endl;
    b.makeMove(m);
    b.dump(std::cerr);
    b.checkIntegrity();
    std::cerr << "unmake move" << m << std::endl;
    b.unmakeMove(m);
    b.dump(std::cerr);
    b.checkIntegrity();
    std::cerr << std::endl << "make move" << m << std::endl;
    b.makeMove(m);
    b.dump(std::cerr);
}

void boardUnitTest() {
    Board b;
    b.dump(std::cerr);
    b.checkIntegrity();
    std::list<Move> moveList = {
        {notation2Number("e2"), notation2Number("e4"), 0, Piece::empty},
        {notation2Number("c7"), notation2Number("c5"), 0, Piece::empty},
        {notation2Number("e4"), notation2Number("e5"), 0, Piece::empty},
        {notation2Number("f7"), notation2Number("f5"), 0, Piece::empty},
        {notation2Number("e5"), notation2Number("f6"), notation2Number("f5"), Piece::empty, MoveFlags::enPassantCapture},
        {notation2Number("g7"), notation2Number("f6"), 0, Piece::pawn},
        {notation2Number("f1"), notation2Number("a6"), 0, Piece::empty},
        {notation2Number("g8"), notation2Number("h6"), 0, Piece::empty},
        {notation2Number("g1"), notation2Number("f3"), 0, Piece::empty},
        {notation2Number("d8"), notation2Number("a5"), 0, Piece::empty},
        {notation2Number("e1"), notation2Number("g1"), 0, Piece::empty, MoveFlags::castling | MoveFlags::w_king_first | MoveFlags::w_k_rook_first},
        {notation2Number("b7"), notation2Number("a6"), 0, Piece::bishop},
        {notation2Number("g2"), notation2Number("g4"), 0, Piece::empty},
        {notation2Number("c8"), notation2Number("b7"), notation2Number("g4")},
        {notation2Number("g4"), notation2Number("g5"), 0, Piece::empty},
        {notation2Number("b8"), notation2Number("c6"), 0, Piece::empty},
        {notation2Number("g5"), notation2Number("g6"), 0, Piece::empty},
        {notation2Number("e8"), notation2Number("c8"), 0, Piece::empty, MoveFlags::castling | MoveFlags::b_king_first | MoveFlags::b_q_rook_first},
        {notation2Number("g6"), notation2Number("g7"), 0, Piece::empty},
        {notation2Number("a5"), notation2Number("a4"), 0, Piece::empty},
        {notation2Number("g7"), notation2Number("g8"), 0, Piece::empty, MoveFlags::queenPromotion}
    };
    for (const auto &move : moveList) {
        testMove(b, move);
    }

}

void engineMasksTest() {
    for (int i = 0; i < 64; ++i) {
        std::cerr << i << ", knight: " << std::endl;
        printBitmaskAsBoard(Engine::knightBitmask[i], std::cerr);
        std::cerr << std::endl;
        std::cerr << i << ", bishop[1]: " << std::endl;
        printBitmaskAsBoard(Engine::bishopBitmask[i][1], std::cerr);
        std::cerr << std::endl;
        std::cerr << i << ", rook[2]: " << std::endl;
        printBitmaskAsBoard(Engine::rookBitmask[i][2], std::cerr);
        std::cerr << std::endl;
        std::cerr << i << ", king: " << std::endl;
        printBitmaskAsBoard(Engine::kingBitmask[i], std::cerr);
        std::cerr << std::endl;
    }
}

void testEngine() {
    Engine engine;
    std::list<std::string> moves{"e2e4", "a7a6", "d1h5"};

    std::cerr << "possible moves in start position" << std::endl;
    engine.go();
    for (auto &m : moves) {
        engine.move(m);
        std::cerr << "possible moves after: " << m << std::endl;
        engine.go();
    }
}