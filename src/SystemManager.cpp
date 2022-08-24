#include "ECS.hpp"

template<typename T>
std::shared_ptr<T> ECS::SystemManager::registerSystem()
{
    const char* typeName = typeid(T).name();

    assert(this->_systems.find(typeName) == this->_systems.end() &&
        "Registering system more than once");

    /* Create a pointer to the system and return it so it can be used externally */
    auto system = std::make_shared<T>();
    this->_systems.insert({typeName, system});
    return system;
}

template<typename T>
void ECS::SystemManager::setSignature(Signature signature)
{
    const char* typeName = typeid(T).name();

    assert(this->_systems.find(typeName) != this->_systems.end() && "System used before registered.");

    /* Set the signature for this system */
    this->_signatures.insert({typeName, signature});
}

void ECS::SystemManager::entityDestroyed(Entity entity)
{
    /* Erase a destroyed entity from all system lists */
    /* mEntities is a set so no check needed */
    for (auto const& pair : this->_systems)
    {
        auto const& system = pair.second;

        system->entities.erase(entity);
    }
}

void ECS::SystemManager::entitySignatureChanged(Entity entity, Signature entitySignature)
{
    /* Notify each system that an entity's signature changed */
    for (auto const& pair : this->_systems)
    {
        auto const& type = pair.first;
        auto const& system = pair.second;
        auto const& systemSignature = this->_signatures[type];

        /* Entity signature matches system signature - insert into set */
        /* Entity signature does not match system signature - erase from set */
        if ((entitySignature & systemSignature) == systemSignature)
            system->entities.insert(entity);
        else
            system->entities.erase(entity);
    }
}
