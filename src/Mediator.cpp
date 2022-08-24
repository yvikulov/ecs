#include "ECS.hpp"

void ECS::Mediator::Init(void)
{
    this->_componentManager = std::unique_ptr<ComponentManager>(new ComponentManager());
    this->_entityManager = std::unique_ptr<EntityManager>(new EntityManager());
    this->_systemManager = std::unique_ptr<SystemManager>(new SystemManager());
    
}

ECS::Entity ECS::Mediator::CreateEntity(void)
{
    return this->_entityManager->CreateEntity();
}

void ECS::Mediator::DestroyEntity(Entity entity)
{
    this->_entityManager->DestroyEntity(entity);
    this->_componentManager->EntityDestroyed(entity);
    this->_systemManager->EntityDestroyed(entity);
}

template<typename T>
void ECS::Mediator::RegisterComponent()
{
    this->_componentManager->RegisterComponent<T>();
}

template<typename T>
void ECS::Mediator::AddComponent(Entity entity, T component)
{
    this->_componentManager->AddComponent<T>(entity, component);

    auto signature = this->_entityManager->GetSignature(entity);
    signature.set(this->_componentManager->GetComponentType<T>(), true);
    this->_entityManager->SetSignature(entity, signature);

    this->_systemManager->EntitySignatureChanged(entity, signature);
}

template<typename T>
void ECS::Mediator::RemoveComponent(Entity entity)
{
    this->_componentManager->RemoveComponent<T>(entity);

    auto signature = this->_entityManager->GetSignature(entity);
    signature.set(this->_componentManager->GetComponentType<T>(), false);
    this->_entityManager->SetSignature(entity, signature);

    this->_systemManager->EntitySignatureChanged(entity, signature);
}

template<typename T>
T& ECS::Mediator::GetComponent(Entity entity)
{
    return this->_componentManager->GetComponent<T>(entity);
}

template<typename T>
ECS::ComponentType ECS::Mediator::GetComponentType()
{
    return this->_componentManager->GetComponentType<T>();
}

template<typename T>
std::shared_ptr<T> ECS::Mediator::RegisterSystem()
{
    return this->_systemManager->RegisterSystem<T>();
}

template<typename T>
void ECS::Mediator::SetSystemSignature(Signature signature)
{
    this->_systemManager->SetSignature<T>(signature);
}
