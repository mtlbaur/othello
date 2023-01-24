#ifndef GUI_CFG_H_GUARD
#define GUI_CFG_H_GUARD

#include <iostream>
#include <fstream>
#include <memory>
#include <string>

#include <imgui.h>

// https://www.boost.org/doc/libs/1_79_0/libs/filesystem/doc/tutorial.html
#include <boost/filesystem.hpp>

// https://www.boost.org/doc/libs/1_79_0/libs/serialization/doc/index.html
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include "game_board.h"

extern Othello::Game::Board board;

namespace Othello::Gui {
    struct Cfg {
        class Window {
            friend Cfg;

            Cfg* cfg;

            int pieceSegments    = 64;
            int pieceBorderWidth = 2;
            int pieceRadius      = 32;

            float edgeWidthMult = 0.34f;

            int targetFPS = 150;

            bool pieceBlackBorder = false;
            bool pieceWhiteBorder = false;

          public:
            Window(Cfg& cfg);

            void display();

            template <class Archive>
            void serialize(Archive& a, const unsigned v) {
                a& pieceSegments;
                a& pieceBorderWidth;
                a& pieceRadius;

                a& edgeWidthMult;

                a& targetFPS;

                a& pieceBlackBorder;
                a& pieceWhiteBorder;
            }
        };

        std::unique_ptr<Window> window;

        const ImU32 COLOR_BLACK = ImColor(0.0f, 0.0f, 0.0f, 1.0f);
        const ImU32 COLOR_WHITE = ImColor(1.0f, 1.0f, 1.0f, 1.0f);

        const std::array<const char*, 8> ROW_LABELS{"1", "2", "3", "4", "5", "6", "7", "8"};
        const std::array<const char*, 8> COL_LABELS{"a", "b", "c", "d", "e", "f", "g", "h"};

        int pieceSegments = 1;

        float pieceBorderWidth = 1.0f;
        float pieceRadius      = 1.0f;
        float pieceDiameter    = 1.0f;

        float edgeWidth = 1.0f;

        ImVec2 cellDimensions{1.0f, 1.0f};
        ImVec2 cornerDimensions{1.0f, 1.0f};

        double targetFPS = 1.0;

        struct {
            bool cfgWindow        = false;
            bool gameEndWindow    = false;
            bool pieceBlackBorder = false;
            bool pieceWhiteBorder = false;
        } enabled;

        Cfg();

        void reset();
        void update();
        void save(const std::string& path, const std::string& name, const std::string& extension);
        void load(const std::string& path, const std::string& name, const std::string& extension);
    };
} // namespace Othello::Gui

#endif