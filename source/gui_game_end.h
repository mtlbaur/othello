#ifndef GUI_GAME_END_H_GUARD
#define GUI_GAME_END_H_GUARD

#include <imgui.h>

#include "game_board.h"
#include "gui_cfg.h"

extern Othello::Game::Board board;
extern Othello::Gui::Cfg cfg;

namespace Othello::Gui::GameEnd {
    inline void display() {
        static const ImGuiWindowFlags WINDOW_FLAGS = ImGuiWindowFlags_AlwaysAutoResize |
                                                     ImGuiWindowFlags_NoResize;

        if (cfg.enabled.gameEndWindow) {
            if (ImGui::Begin("Results", &cfg.enabled.gameEndWindow, WINDOW_FLAGS)) {
                static const ImGuiTableFlags TABLE_FLAGS = ImGuiTableFlags_Borders |
                                                           ImGuiTableFlags_SizingFixedFit |
                                                           ImGuiTableFlags_NoHostExtendX;

                if (ImGui::BeginTable("GAME_END_TABLE", 2, TABLE_FLAGS)) {
                    {
                        ImGui::TableNextColumn();
                        ImGui::Text("Black");

                        ImGui::TableNextColumn();
                        ImGui::Text("White");
                    }
                    {
                        ImGui::TableNextColumn();
                        ImGui::Text("%d", board.stats.black);

                        ImGui::TableNextColumn();
                        ImGui::Text("%d", board.stats.white);
                    }
                }

                ImGui::EndTable();

                if (ImGui::Button("New Game")) {
                    board.reset();
                    cfg.enabled.gameEndWindow = false;
                }
            }

            ImGui::End();
        }
    }
} // namespace Othello::Gui::GameEnd

#endif