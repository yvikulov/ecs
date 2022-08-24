#include "ECS.hpp"

namespace ECS
{
    class ComponentManager
    {
    private:
        std::unordered_map<const char*, std::shared_ptr<IComponentArray>> _componentArrays;
        std::unordered_map<const char*, ComponentType> _componentTypes;
	    ComponentType _nextComponentType;

        template<typename T>
        std::shared_ptr<ComponentArray<T>> getComponentArray(void);

    public:
        // ComponentManager(void);
        // ComponentManager(const ComponentManager& manager);
        // ComponentManager& operator=(const ComponentManager& manager);
        // ~ComponentManager();

        template<typename T>
	    void registerComponent(void);

        template<typename T>
	    ComponentType getComponentType(void);

        template<typename T>
	    void addComponent(Entity entity, T component);

        template<typename T>
	    void removeComponent(Entity entity);

        template<typename T>
	    T& getComponent(Entity entity);

        void entityDestroyed(Entity entity);
    };
}