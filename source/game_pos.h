#ifndef GAME_POS_H_GUARD
#define GAME_POS_H_GUARD

namespace Othello::Game {
    struct Pos {
        int i = 0;
        int j = 0;

        Pos(int i, int j) : i(i), j(j){};

        void operator+=(const Pos& p) {
            i += p.i;
            j += p.j;
        }
    };
    struct N : Pos {
        N() : Pos(-1, 0){};
    };
    struct NE : Pos {
        NE() : Pos(-1, 1){};
    };
    struct E : Pos {
        E() : Pos(0, 1){};
    };
    struct SE : Pos {
        SE() : Pos(1, 1){};
    };
    struct S : Pos {
        S() : Pos(1, 0){};
    };
    struct SW : Pos {
        SW() : Pos(1, -1){};
    };
    struct W : Pos {
        W() : Pos(0, -1){};
    };
    struct NW : Pos {
        NW() : Pos(-1, -1){};
    };
} // namespace Othello::Game

#endif