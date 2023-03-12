#ifndef GUI_DISK_H_GUARD
#define GUI_DISK_H_GUARD

#include <imgui.h>

#include "gui_cfg.h"

extern Othello::Gui::Cfg cfg;

namespace Othello::Gui::Disk {
    void draw(Game::Side s, ImDrawList* drawList, const ImVec2& POS, const float RADIUS) {
        switch (s) {
            using enum Game::Side;

            case NONE:
                break;
            case WHITE:
                drawList->AddCircleFilled(POS, RADIUS, cfg.COLOR_WHITE, cfg.diskSegments);
                if (cfg.enabled.diskWhiteBorder) drawList->AddCircle(POS, RADIUS - cfg.diskBorderWidth / 2.0f, cfg.COLOR_BLACK, cfg.diskSegments, cfg.diskBorderWidth);
                break;
            case BLACK:
                drawList->AddCircleFilled(POS, RADIUS, cfg.COLOR_BLACK, cfg.diskSegments);
                if (cfg.enabled.diskBlackBorder) drawList->AddCircle(POS, RADIUS - cfg.diskBorderWidth / 2.0f, cfg.COLOR_WHITE, cfg.diskSegments, cfg.diskBorderWidth);
                break;
            default:
                abort();
        }
    }
} // namespace Othello::Gui::Disk

#endif