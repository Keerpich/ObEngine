#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

namespace obe
{
    namespace System
    {
        enum class WindowContext
        {
            GameWindow,
            EditorWindow
        };

        extern sf::RenderWindow MainWindow;

        void InitWindow(WindowContext context);
    }
}