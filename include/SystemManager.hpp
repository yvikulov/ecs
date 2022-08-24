#include "ECS.hpp"

namespace ECS
{
    class SystemManager
    {
    private:
        std::unordered_map<const char*, Signature> _signatures;
        std::unordered_map<const char*, std::shared_ptr<System>> _systems;

    public:
        // SystemManager(void);
        // SystemManager(const SystemManager& manager);
        // SystemManager& operator=(const SystemManager& manager);
        // ~SystemManager();

        template<typename T>
	    std::shared_ptr<T> registerSystem(void);

        template<typename T>
	    void setSignature(Signature signature);

        void entityDestroyed(Entity entity);

        void entitySignatureChanged(Entity entity, Signature entitySignature);

    };
}