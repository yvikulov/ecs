#include "ECS.hpp"

namespace ECS
{
    class SystemManager
    {
    private:
        std::unordered_map<const char*, Signature> _signatures{};
        std::unordered_map<const char*, std::shared_ptr<System>> _systems{};

    public:
        template<typename T>
	    std::shared_ptr<T> RegisterSystem(void);

        template<typename T>
	    void SetSignature(Signature signature);

        void EntityDestroyed(Entity entity);

        void EntitySignatureChanged(Entity entity, Signature entitySignature);

    };
}