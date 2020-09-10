#pragma once
#include <glm/glm.hpp>


struct Rect {
    glm::vec2 topleft, botright;
    Rect(glm::vec2 topleft, glm::vec2 botright)
        : topleft(topleft), botright(botright)
    {
    }
};

