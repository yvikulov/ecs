#include "ECS.hpp"

namespace ECS
{
    class IComponentArray
    {
    public:
        virtual ~IComponentArray() = default;
        virtual void EntityDestroyed(Entity entity) = 0;
    };

    template<typename T>
    class ComponentArray : public IComponentArray
    {
    private:
        std::array<T, MAX_ENTITIES> _componentArray;
        std::unordered_map<Entity, std::size_t> _entityToIndexMap;
        std::unordered_map<std::size_t, Entity> _indexToEntityMap;
        std::size_t _size;
        
    public:
        void InsertData(Entity entity, T component);
        void RemoveData(Entity entity);
        T& GetData(Entity entity);

        void EntityDestroyed(Entity Entity) override;
    };
}