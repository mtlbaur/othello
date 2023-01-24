#ifndef GUI_PIECE_H_GUARD
#define GUI_PIECE_H_GUARD

#include <imgui.h>

#include "gui_cfg.h"

extern Othello::Gui::Cfg cfg;

namespace Othello::Gui::Piece {
    void draw(Game::Side s, ImDrawList* drawList, const ImVec2& POS, const float RADIUS) {
        switch (s) {
            using enum Game::Side;

            case NONE:
                break;
            case WHITE:
                drawList->AddCircleFilled(POS, RADIUS, cfg.COLOR_WHITE, cfg.pieceSegments);
                if (cfg.enabled.pieceWhiteBorder) drawList->AddCircle(POS, RADIUS - cfg.pieceBorderWidth / 2.0f, cfg.COLOR_BLACK, cfg.pieceSegments, cfg.pieceBorderWidth);
                break;
            case BLACK:
                drawList->AddCircleFilled(POS, RADIUS, cfg.COLOR_BLACK, cfg.pieceSegments);
                if (cfg.enabled.pieceBlackBorder) drawList->AddCircle(POS, RADIUS - cfg.pieceBorderWidth / 2.0f, cfg.COLOR_WHITE, cfg.pieceSegments, cfg.pieceBorderWidth);
                break;
            default:
                abort();
        }
    }
} // namespace Othello::Gui::Piece

#endif