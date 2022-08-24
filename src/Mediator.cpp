#include "ECS.hpp"

void ECS::Mediator::init(void)
{
    this->_componentManager = std::unique_ptr<ComponentManager>(new ComponentManager());
    this->_entityManager = std::unique_ptr<EntityManager>(new EntityManager());
    this->_systemManager = std::unique_ptr<SystemManager>(new SystemManager());
    
}

ECS::Entity ECS::Mediator::createEntity(void)
{
    return this->_entityManager->createEntity();
}

void ECS::Mediator::destroyEntity(Entity entity)
{
    this->_entityManager->destroyEntity(entity);
    this->_componentManager->entityDestroyed(entity);
    this->_systemManager->entityDestroyed(entity);
}

template<typename T>
void ECS::Mediator::registerComponent()
{
    this->_componentManager->registerComponent<T>();
}

template<typename T>
void ECS::Mediator::addComponent(Entity entity, T component)
{
    this->_componentManager->addComponent<T>(entity, component);

    auto signature = this->_entityManager->getSignature(entity);
    signature.set(this->_componentManager->getComponentType<T>(), true);
    this->_entityManager->setSignature(entity, signature);

    this->_systemManager->entitySignatureChanged(entity, signature);
}

template<typename T>
void ECS::Mediator::removeComponent(Entity entity)
{
    this->_componentManager->removeComponent<T>(entity);

    auto signature = this->_entityManager->getSignature(entity);
    signature.set(this->_componentManager->getComponentType<T>(), false);
    this->_entityManager->setSignature(entity, signature);

    this->_systemManager->entitySignatureChanged(entity, signature);
}

template<typename T>
T& ECS::Mediator::getComponent(Entity entity)
{
    return this->_componentManager->getComponent<T>(entity);
}

template<typename T>
ECS::ComponentType ECS::Mediator::getComponentType()
{
    return this->_componentManager->getComponentType<T>();
}

template<typename T>
std::shared_ptr<T> ECS::Mediator::registerSystem()
{
    return this->_systemManager->registerSystem<T>();
}

template<typename T>
void ECS::Mediator::setSystemSignature(Signature signature)
{
    this->_systemManager->setSignature<T>(signature);
}
