#include "ECS.hpp"

namespace ECS
{
    class IComponentArray
    {
    public:
        virtual ~IComponentArray() = default;
        virtual void entityDestroyed(Entity entity) = 0;
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
        // ComponentArray(void);
        // ComponentArray(const ComponentArray& array);
        // ComponentArray& operator=(const ComponentArray& array);
        // ~ComponentArray();

        void insertData(Entity entity, T component);
        void removeData(Entity entity);
        T& getData(Entity entity);

        void entityDestroyed(Entity Entity) override;
    };
}