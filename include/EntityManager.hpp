#pragma once

#include "ECS.hpp"

namespace ECS
{
    class EntityManager
    {
    private:
        std::queue<Entity> _availableEntities{};
        std::array<Signature, MAX_ENTITIES> _signatures{};
        uint32_t _livingEntityCount{};
        
    public:
        EntityManager(void);
        EntityManager(const EntityManager & entityManager);
        EntityManager& operator=(const EntityManager & entityManager);

        Entity CreateEntity(void);
        void DestroyEntity(Entity entity);

        void SetSignature(Entity entity, Signature signature);
        Signature GetSignature(Entity entity);

        ~EntityManager();
    };
}
