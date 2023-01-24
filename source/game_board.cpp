#include "game_board.h"

namespace Othello::Game {
    Board::Board() {
        reset();
    };

    void Board::reset() {
        turnSide = Side::BLACK;

        board = {
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 2, 1, 0, 0, 0},
            {0, 0, 0, 1, 2, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0}
        };

        stats = Stats();
    }

    Move Board::place(int i, int j) {
        Pos pos{i, j};

        // if the place-position is empty AND the number of placement-turned-pieces is greater than zero
        if (empty(pos) && turnPieces(pos, turnSide) > 0) {
            // place turn-side piece in the placement-position
            board[pos.i][pos.j] = turnSide;

            int oppositeSide = switchSides(turnSide);

            // if the opposite side has a possible move, give them their turn
            if (hasPossibleMove(oppositeSide)) {
                turnSide = static_cast<Side>(oppositeSide);
                return Move::VALID;
            }

            // if the opposite side DOESN'T have a move, give the current side another turn
            if (hasPossibleMove(turnSide)) {
                return Move::VALID;
            }

            // if neither side has a possible move, the game is over
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    switch (board[i][j]) {
                        using enum Side;

                        case BLACK:
                            stats.black++;
                            break;
                        case WHITE:
                            stats.white++;
                            break;
                        default:
                            break;
                    }
                }
            }

            return Move::END;
        }

        // if the place-position wasn't empty OR the number of turned pieces from placement was zero, then it is an invalid move
        return Move::INVALID;
    }

    Side Board::side(int i, int j) {
        return static_cast<Side>(board[i][j]);
    }

    bool Board::valid(Pos p) {
        return p.i >= 0 && p.i < 8 && p.j >= 0 && p.j < 8;
    }

    bool Board::empty(Pos p) {
        return board[p.i][p.j] == 0;
    }

    int Board::switchSides(int side) {
        return (side & 1) + 1;
    }

    int Board::turnPieces(Pos pos, int turnSide) {
        int turned       = 0;
        int oppositeSide = switchSides(turnSide);

        for (const Pos& shift : SHIFTS) { // for all valid directions: N, NE, E, SE, S, SW, W, NW
            [&](Pos pos, const Pos& shift) {
                // take one step in the current direction
                pos += shift;

                std::vector<Pos> found;

                // while there are pieces of the opposite side's color in the current direction, store their board positions
                while (valid(pos) && board[pos.i][pos.j] == oppositeSide) {
                    found.emplace_back(pos);
                    pos += shift;
                }

                // if there is an ending piece of the turn side's color, turn any opposite side pieces that lie between the starting position and the ending piece
                // NOTE: the number of turned pieces can be zero if there were no bounded opposite side pieces
                if (valid(pos) && board[pos.i][pos.j] == turnSide) {
                    for (Pos p : found) {
                        board[p.i][p.j] = turnSide;
                    }

                    turned += found.size();
                }
            }(pos, shift);
        }

        // return the total number of turned pieces
        return turned;
    }

    bool Board::hasPossibleMove(int turnSide) {
        int oppositeSide = switchSides(turnSide);

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                for (const Pos& shift : SHIFTS) { // for all valid directions: N, NE, E, SE, S, SW, W, NW
                    Pos pos{i, j};

                    if ([&](Pos pos, const Pos& shift) -> bool { // if the turn side has a possible move...
                            if (!empty(pos)) return false;

                            // take one step in the current direction
                            pos += shift;

                            // if there is no piece of the opposite color (adjacent to the starting position), the turn side has no possible move
                            if (!valid(pos) || !(board[pos.i][pos.j] == oppositeSide)) {
                                return false;
                            }

                            // take a second step in the current direction
                            pos += shift;

                            // while there are additional pieces of the opposite color in the current direction, follow them
                            while (valid(pos) && board[pos.i][pos.j] == oppositeSide) {
                                pos += shift;
                            }

                            // if there is an ending piece of the turn side's color, that follows at least one piece of the opposite color, the turn side has a possible move
                            if (valid(pos) && board[pos.i][pos.j] == turnSide) {
                                return true;
                            }

                            return false;
                        }(pos, shift)) { // ...return true
                        return true;
                    }
                }
            }
        }

        return false;
    }
} // namespace Othello::Game