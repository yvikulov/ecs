#include "ECS.hpp"

namespace ECS
{
    class Mediator
    {
    private:
        std::unique_ptr<EntityManager> _entityManager;
        std::unique_ptr<ComponentManager> _componentManager;
        std::unique_ptr<SystemManager> _systemManager;

    public:

        // Mediator(void);
        // Mediator(const Mediator& mediator);
        // Mediator& operator=(const Mediator& mediator);
        // ~Mediator();

        void init(void);

        Entity createEntity(void);
        void destroyEntity(Entity entity);

        template<typename T>
        void registerComponent(void);

        template<typename T>
        void addComponent(Entity entity, T component);

        template<typename T>
        void removeComponent(Entity entity);

        template<typename T>
        T& getComponent(Entity entity);

        template<typename T>
        ComponentType getComponentType(void);

        template<typename T>
        std::shared_ptr<T> registerSystem(void);

        template<typename T>
        void setSystemSignature(Signature signature);

    };
}