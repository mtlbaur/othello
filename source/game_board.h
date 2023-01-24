#ifndef GAME_BOARD_H_GUARD
#define GAME_BOARD_H_GUARD

#include <vector>

#include "utility.h"
#include "game_pos.h"

namespace Othello::Game {
    enum Side {
        NONE  = 0,
        BLACK = 1,
        WHITE = 2
    };

    enum Move {
        END     = 0,
        VALID   = 1,
        INVALID = 2
    };

    class Board {
        const std::vector<Pos> SHIFTS{N(), NE(), E(), SE(), S(), SW(), W(), NW()};

      public:
        Side turnSide = Side::BLACK;
        std::vector<std::vector<int>> board;

        struct Stats {
            int black = 0;
            int white = 0;
        } stats;

        Board();

        void reset();
        Move place(int i, int j);
        Side side(int i, int j);

      private:
        bool valid(Pos p);
        bool empty(Pos p);
        int switchSides(int side);
        int turnPieces(Pos pos, int turnSide);
        bool hasPossibleMove(int turnSide);
    };
} // namespace Othello::Game

#endif