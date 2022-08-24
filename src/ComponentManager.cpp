#include "ECS.hpp"

template<typename T>
void ECS::ComponentManager::registerComponent()
{
    const char* typeName = typeid(T).name();

    assert(this->_componentTypes.find(typeName) == this->_componentTypes.end() &&
        "Registering component type more than once");

    /* Add this component type to the component type map */
    this->_componentTypes.insert({typeName, this->_nextComponentType});

    /* Create a ComponentArray pointer and add it to the component arrays map */
    this->_componentArrays.insert({typeName, std::make_shared<ComponentArray<T>>()});

    /* Increment the value so that the next component registered will be different */
    this->_nextComponentType++;
}

template<typename T>
ECS::ComponentType ECS::ComponentManager::getComponentType()
{
    const char* typeName = typeid(T).name();

    assert(this->_componentTypes.find(typeName) != this->_componentTypes.end() &&
        "Component not registered before use");

    /* Return this component's type - used for creating signatures */
    return this->_componentTypes[typeName];
}

template<typename T>
void ECS::ComponentManager::addComponent(Entity entity, T component)
{
    /* Add a component to the array for an entity */
    this->getComponentArray<T>()->insertData(entity, component);
}

template<typename T>
void ECS::ComponentManager::removeComponent(Entity entity)
{
    /* Remove a component from the array for an entity */
    this->getComponentArray<T>()->removeData(entity);
}

template<typename T>
T& ECS::ComponentManager::getComponent(Entity entity)
{
    /* Get a reference to a component from the array for an entity */
    return this->getComponentArray<T>()->getData(entity);
}

void ECS::ComponentManager::entityDestroyed(Entity entity)
{
    /* Notify each component array that an entity has been destroyed */
    /* If it has a component for that entity, it will remove it */
    for (auto const& pair : this->_componentArrays)
    {
        auto const& component = pair.second;

        component->entityDestroyed(entity);
    }
}

template<typename T>
std::shared_ptr<ECS::ComponentArray<T>> ECS::ComponentManager::getComponentArray()
{
    const char* typeName = typeid(T).name();

    assert(this->_componentTypes.find(typeName) != this->_componentTypes.end() &&
        "Component not registered before use");

    return std::static_pointer_cast<ComponentArray<T>>(this->_componentArrays[typeName]);
}