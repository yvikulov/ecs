#pragma once

#include <unordered_map>
#include <cstdint>
#include <bitset>
#include <queue>
#include <array>
#include <set>

namespace ECS
{
    using Entity = std::uint32_t;
    static const Entity MAX_ENTITIES = 5000;

    using ComponentType = std::uint8_t;
    static const ComponentType MAX_COMPONENTS = 32;

    using Signature = std::bitset<MAX_COMPONENTS>;
}

#include "EntityManager.hpp"

#include "ComponentArray.hpp"
#include "ComponentManager.hpp"

#include "System.hpp"
#include "SystemManager.hpp"

#include "Mediator.hpp"