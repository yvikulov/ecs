#include "ECS.hpp"

// Default constructor ---------------------------------------------------------
ECS::EntityManager::EntityManager(void)
{
    /* Initialize the queue with all possible entity IDs */
    for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
        this->_availableEntities.push(entity);
}

// EntityManager create the new entity -----------------------------------------
ECS::Entity ECS::EntityManager::CreateEntity(void)
{
    assert(this->_livingEntityCount < MAX_ENTITIES &&
        "Too many entities in existence");

    /* Take an ID from the front of the queue */
    Entity id = this->_availableEntities.front();
    this->_availableEntities.pop();
    this->_livingEntityCount++;

    return id;
}

// EntityManager destroy the entity --------------------------------------------
void ECS::EntityManager::DestroyEntity(Entity entity)
{
    assert(entity < MAX_ENTITIES && "Entity out of range");

    /* Invalidate the destroyed entity's signature */
    this->_signatures[entity].reset();

    /* Put the destroyed ID at the back of the queue */
    this->_availableEntities.push(entity);
    this->_livingEntityCount--;
}

// Set the signature of used components for an entity --------------------------
void ECS::EntityManager::SetSignature(Entity entity, Signature signature)
{
    assert(entity < MAX_ENTITIES && "Entity out of range");

    /* Put this entity's signature into the array */
    this->_signatures[entity] = signature;
}

ECS::EntityManager::~EntityManager(void) { }