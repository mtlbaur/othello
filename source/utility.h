#ifndef UTILITY_H_GUARD
#define UTILITY_H_GUARD

#include <iostream>

#include <imgui.h>

namespace Othello::Utility {
    inline void require(bool condition) {
        if (!condition) {
            std::cerr << "REQUIRED CONDITION FAILED\n";
            abort();
        }
    }

    template <typename T>
    void write(std::ostream& out, const T& t) {
        out << t;
    }

    template <typename... A>
    void write(std::ostream& out, const A&... a) {
        (write(out, a), ...);
    }

    template <typename... A>
    void writeln(std::ostream& out, const A&... a) {
        write(out, a..., '\n');
    }

    template <typename... A>
    void print(const A&... a) {
        write(std::cout, a...);
    }

    template <typename... A>
    void println(const A&... a) {
        write(std::cout, a..., '\n');
    }
} // namespace Othello::Utility

#endif