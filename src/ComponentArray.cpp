#include "ECS.hpp"

// Insert a component into an array of components ------------------------------
template<typename T>
void ECS::ComponentArray<T>::insertData(Entity entity, T component)
{
    assert(this->_entityToIndexMap.find(entity) == this->_entityToIndexMap.end() &&
        "Component added to same entity more than once");

    /* Put new entry at end and update the maps */
    std::size_t index = this->_size;
    this->_entityToIndexMap[entity] = index;
    this->_indexToEntityMap[index] = entity;
    this->_componentArray[index] = component;
    this->_size++;
}

// Remove entity from component array ------------------------------------------
template<typename T>
void ECS::ComponentArray<T>::removeData(Entity entity)
{
    assert(this->_entityToIndexMap.find(entity) != this->_entityToIndexMap.end() &&
        "Removing non-existent component");

    /* Copy element at end into deleted element's place to maintain density */
    std::size_t indexRemovedEntity = this->_entityToIndexMap[entity];
    std::size_t indexLastElement = this->_size - 1;
    this->_componentArray[indexRemovedEntity] = this->_componentArray[indexLastElement];

    /* Update map to point to moved spot */
    Entity entityOfLastElement = this->_indexToEntityMap[indexLastElement];
    this->_entityToIndexMap[entityOfLastElement] = indexRemovedEntity;
    this->_indexToEntityMap[indexRemovedEntity] = entityOfLastElement;

    this->_entityToIndexMap.erase(entity);
    this->_indexToEntityMap.erase(indexLastElement);

    this->_size--;
}

// Get a component from an array of components ---------------------------------
template<typename T>
T& ECS::ComponentArray<T>::getData(Entity entity)
{
    assert(this->_entityToIndexMap.find(entity) != this->_entityToIndexMap.end() &&
        "Retrieving non-existent component");

    /* Return a reference to the entity's component */
    return this->_componentArray[this->_entityToIndexMap[entity]];
}

template<typename T>
void ECS::ComponentArray<T>::entityDestroyed(Entity entity)
{
    /* Remove the entity's component if it existed */
    if (this->_entityToIndexMap.find(entity) != this->_entityToIndexMap.end())
        this->removeData(entity);
}
