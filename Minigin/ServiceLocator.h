#pragma once  
#include <memory>  
#include "SoundSystem.h"  
#include "ColliderManager.h"

namespace dae
{
	class ServiceLocator final
	{
		static std::unique_ptr<SoundSystem> m_pSSInstance;
		static std::unique_ptr<NullSoundSystem> m_pNullSSInstance;
		static std::unique_ptr<ColliderManager> m_pColManagerInstance;

	public:
		ServiceLocator() = default;
		~ServiceLocator() = default;
		ServiceLocator(const ServiceLocator&) = delete;
		ServiceLocator(ServiceLocator&&) = delete;
		ServiceLocator& operator=(const ServiceLocator&) = delete;
		ServiceLocator& operator=(ServiceLocator&&) = delete;

		static SoundSystem& GetSoundSystem()
		{
			return m_pSSInstance.get() == nullptr ? *m_pNullSSInstance.get() : *m_pSSInstance.get();
		}

		static ColliderManager& GetColliderManager()
		{
			return *m_pColManagerInstance.get();
		}

		static void RegisterSoundSystem(std::unique_ptr<SoundSystem>&& pSSInstance)
		{
			if(pSSInstance != nullptr)
				m_pSSInstance = std::move(pSSInstance);
		}
		static void RegisterColliderManager(std::unique_ptr<ColliderManager> manager)
		{
			m_pColManagerInstance = std::move(manager);
		}
	};
}

