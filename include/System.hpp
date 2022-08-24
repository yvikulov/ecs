#pragma once

#include "ECS.hpp"

namespace ECS
{
    class System
    {
    public:
        std::set<Entity> entities;
    };
}

