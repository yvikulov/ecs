#include "ECS.hpp"

namespace ECS
{
    class ComponentManager
    {
    private:
        std::unordered_map<const char*, ComponentType> _componentTypes{};
        std::unordered_map<const char*, std::shared_ptr<IComponentArray>> _componentArrays{};
	    ComponentType _nextComponentType{};

        template<typename T>
        std::shared_ptr<ComponentArray<T>> GetComponentArray(void);

    public:
        template<typename T>
	    void RegisterComponent(void);

        template<typename T>
	    ComponentType GetComponentType(void);

        template<typename T>
	    void AddComponent(Entity entity, T component);

        template<typename T>
	    void RemoveComponent(Entity entity);

        template<typename T>
	    T& GetComponent(Entity entity);

        void EntityDestroyed(Entity entity);
    };
}