#include "ECS.hpp"

namespace ECS
{
    class Mediator
    {
    private:
        std::unique_ptr<ComponentManager> _componentManager;
        std::unique_ptr<EntityManager> _entityManager;
        std::unique_ptr<SystemManager> _systemManager;

    public:

        void Init(void);
        Entity CreateEntity(void);
        void DestroyEntity(Entity entity);

        template<typename T>
        void RegisterComponent(void);

        template<typename T>
	    void AddComponent(Entity entity, T component);

        template<typename T>
	    void RemoveComponent(Entity entity);

        template<typename T>
	    T& GetComponent(Entity entity);

        template<typename T>
	    ComponentType GetComponentType(void);

        template<typename T>
	    std::shared_ptr<T> RegisterSystem(void);

        template<typename T>
	    void SetSystemSignature(Signature signature);

    };
}