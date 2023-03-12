#include "gui_cfg.h"

namespace Othello::Gui {
    Cfg::Window::Window(Cfg& cfg) : cfg(&cfg) {}

    void Cfg::Window::display() {
        static const ImGuiWindowFlags WINDOW_FLAGS = ImGuiWindowFlags_AlwaysAutoResize |
                                                     ImGuiWindowFlags_NoResize;

        if (cfg->enabled.cfgWindow) {
            if (ImGui::Begin("Config", &cfg->enabled.cfgWindow, WINDOW_FLAGS)) {
                static const char IF[]           = "%d";
                static const char FF[]           = "%.2f";
                static const ImGuiSliderFlags SF = ImGuiSliderFlags_AlwaysClamp;

                bool adjusted = false;

                ImGui::Text("Disk");
                adjusted |= ImGui::DragInt("Segments", &diskSegments, 0.1f, 3, 128, IF, SF);
                adjusted |= ImGui::DragInt("Border Width", &diskBorderWidth, 0.1f, 1, 6, IF, SF);
                adjusted |= ImGui::DragInt("Radius", &diskRadius, 0.1f, 28, 100, IF, SF);
                adjusted |= ImGui::Checkbox("Black Border", &diskBlackBorder);
                ImGui::SameLine();
                adjusted |= ImGui::Checkbox("White Border", &diskWhiteBorder);

                ImGui::Separator();

                adjusted |= ImGui::DragFloat("Edge Width Mult", &edgeWidthMult, 0.001f, 0.34f, 1.0f, FF, SF);

                ImGui::Separator();

                adjusted |= ImGui::DragInt("Target FPS", &targetFPS, 0.1f, 30, 600, IF, SF);

                ImGui::Separator();

                if (ImGui::Button("New Game")) {
                    board.reset();
                    cfg->enabled.gameEndWindow = false;
                }

                ImGui::SameLine();

                if (ImGui::Button("Reset Config")) {
                    cfg->reset();
                }

                if (adjusted) cfg->update();
            }

            ImGui::End();
        }
    }

    Cfg::Cfg() { reset(); }

    void Cfg::reset() {
        this->window = std::make_unique<Window>(*this);
        this->update();
    }

    void Cfg::update() {
        enabled.diskBlackBorder = window->diskBlackBorder;
        enabled.diskWhiteBorder = window->diskWhiteBorder;

        diskSegments    = window->diskSegments;
        diskBorderWidth = window->diskBorderWidth;
        diskRadius      = window->diskRadius;
        diskDiameter    = 2 * diskRadius;

        edgeWidth = diskDiameter * window->edgeWidthMult;

        targetFPS = window->targetFPS;

        cellDimensions   = {diskDiameter, diskDiameter};
        cornerDimensions = {edgeWidth, edgeWidth};
    }

    void Cfg::save(const std::string& path, const std::string& name, const std::string& extension) {
        try {
            if (name.empty()) return;
            if (!boost::filesystem::exists(path)) boost::filesystem::create_directories(path);

            std::string fullPath = path + name + extension;
            std::ofstream ofs(fullPath, std::ofstream::out);

            if (ofs.fail()) return;

            boost::archive::text_oarchive oa(ofs);
            oa << *this->window;
            ofs.close();
        } catch (std::exception& e) {
            std::cerr << "EXCEPTION: Cfg::save(): " << e.what() << '\n';
            reset();
        }
    }

    void Cfg::load(const std::string& path, const std::string& name, const std::string& extension) {
        try {
            if (name.empty()) return;

            std::string fullPath = path + name + extension;
            std::ifstream ifs(fullPath, std::ifstream::in);

            if (ifs.fail()) return;

            boost::archive::text_iarchive ia(ifs);
            ia >> *this->window;
            ifs.close();

            this->update();
        } catch (std::exception& e) {
            std::cerr << "EXCEPTION: Cfg::load(): " << e.what() << '\n';
            reset();
        }
    }
} // namespace Othello::Gui