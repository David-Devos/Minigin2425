#pragma once  
#include <memory>  
#include "SoundSystem.h"  

namespace dae
{
	class ServiceLocator final
	{
		static std::unique_ptr<SoundSystem> m_pSSInstance;
		static std::unique_ptr<NullSoundSystem> m_pNullSSInstance;

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

		static void RegisterSoundSystem(std::unique_ptr<SoundSystem>&& pSSInstance)
		{
			if(pSSInstance != nullptr)
				m_pSSInstance = std::move(pSSInstance);
		}
	};
}

