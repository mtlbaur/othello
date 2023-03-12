#ifndef GUI_BOARD_H_GUARD
#define GUI_BOARD_H_GUARD

#include <imgui.h>

#include "game_board.h"
#include "gui_cfg.h"
#include "gui_disk.h"

extern Othello::Game::Board board;
extern Othello::Gui::Cfg cfg;

namespace Othello::Gui::Board {
    inline void display() {
        static const ImGuiWindowFlags WINDOW_FLAGS = ImGuiWindowFlags_NoTitleBar |
                                                     ImGuiWindowFlags_NoResize |
                                                     ImGuiWindowFlags_NoScrollbar |
                                                     ImGuiWindowFlags_AlwaysAutoResize;

        if (ImGui::Begin("BOARD_WINDOW", nullptr, WINDOW_FLAGS)) {
            static const ImGuiTableFlags TABLE_FLAGS = ImGuiTableFlags_Borders |
                                                       ImGuiTableFlags_SizingFixedFit |
                                                       ImGuiTableFlags_NoHostExtendX;

            ImDrawList* drawList = ImGui::GetWindowDrawList();

            const auto drawColoredSquare = [&]() {
                auto [x1, y1] = ImGui::GetCursorScreenPos();
                float x2 = x1 + cfg.edgeWidth, y2 = y1 + cfg.edgeWidth;

                drawList->AddRectFilled({x1, y1}, {x2, y2}, (board.turnSide == Game::Side::BLACK ? cfg.COLOR_BLACK : cfg.COLOR_WHITE));
                ImGui::Dummy(cfg.cornerDimensions);
            };

            if (ImGui::BeginTable("BOARD_TABLE", 10, TABLE_FLAGS)) {
                { // FIRST ROW
                    {
                        ImGui::TableNextColumn(); // top-left cell
                        drawColoredSquare();
                    }
                    for (int col = 0; col < 8; col++) {
                        ImGui::TableNextColumn();
                        ImGui::Button(cfg.COL_LABELS[col], {cfg.diskDiameter, cfg.edgeWidth});
                    }
                    {
                        ImGui::TableNextColumn(); // top-right cell
                        drawColoredSquare();
                    }
                }
                { // INNER ROWS
                    for (int row = 0; row < 8; row++) {
                        ImGui::TableNextRow();

                        {
                            ImGui::TableNextColumn();
                            ImGui::Button(cfg.ROW_LABELS[row], {cfg.edgeWidth, cfg.diskDiameter});
                        }
                        for (int col = 0; col < 8; col++) {
                            ImGui::TableNextColumn();

                            auto [x, y] = ImGui::GetCursorScreenPos();

                            {
                                std::string label(std::string("##") + cfg.COL_LABELS[col] + cfg.ROW_LABELS[row]);

                                if (ImGui::Button(label.data(), cfg.cellDimensions)) {
                                    if (board.place(row, col) == Game::Move::END) {
                                        cfg.enabled.gameEndWindow = true;
                                    }
                                }
                            }

                            Disk::draw(board.side(row, col), drawList, {x + cfg.diskRadius, y + cfg.diskRadius}, cfg.diskRadius);
                        }
                        {
                            ImGui::TableNextColumn();
                            ImGui::Button(cfg.ROW_LABELS[row], {cfg.edgeWidth, cfg.diskDiameter});
                        }
                    }
                }
                { // LAST ROW
                    {
                        ImGui::TableNextColumn(); // bottom-left cell
                        drawColoredSquare();
                    }
                    for (int col = 0; col < 8; col++) {
                        ImGui::TableNextColumn();
                        ImGui::Button(cfg.COL_LABELS[col], {cfg.diskDiameter, cfg.edgeWidth});
                    }
                    {
                        ImGui::TableNextColumn(); // bottom-right cell
                        drawColoredSquare();
                    }
                }
            }

            ImGui::EndTable();
        }

        ImGui::End();
    }
} // namespace Othello::Gui::Board

#endif