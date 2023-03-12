This program simulates Othello:
- You play against yourself, black always starts first, and the starting configuration is always the same.
- On game end a window with the score and a new game button will appear.
- A config menu can be accessed via the `Esc` key.
    - Options:
        - Board disks:
            - Segments (how smooth the circles are).
            - Size.
            - Border toggle.
            - Border width.
        - Board edge width.
        - Target FPS.
        - Start a new game.
        - Reset the config.
    - The config menu is automatically saved/loaded on program start/shutdown to `./data/system.cfg`.
        - Saving will overwrite without prompt.

See [this](https://en.wikipedia.org/wiki/Reversi) for more information on what Othello is.

A demo can be found [here](https://youtu.be/P3qYu4ozxhI).

***

This program uses:
- [OpenGL 4.6](https://www.opengl.org/).
- [GLFW 3.3.2](https://www.glfw.org/).
- [Glad 2 in core configuration for OpenGL 4.6](https://github.com/Dav1dde/glad/tree/glad2) as the [OpenGL Loader Library](https://www.khronos.org/opengl/wiki/OpenGL_Loading_Library).
- [Dear ImGui 1.89.2](https://github.com/ocornut/imgui).
- [Boost 1.79.0](https://www.boost.org/).

See [LICENSE.md](LICENSE.md) for information on the licenses relating to this project.