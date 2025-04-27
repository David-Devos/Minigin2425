#pragma once
#include <memory>
#include "SoundSystem.h"
namespace dae
{
	class ServiceLocator final
	{
		static std::unique_ptr<SoundSystem> m_pSSInstance ;
	public:
		ServiceLocator() = default;
		~ServiceLocator() = default;
		ServiceLocator(const ServiceLocator&) = delete;
		ServiceLocator(ServiceLocator&&) = delete;
		ServiceLocator& operator=(const ServiceLocator&) = delete;
		ServiceLocator& operator=(ServiceLocator&&) = delete;

		static SoundSystem& GetSoundSystem()
		{
			return *m_pSSInstance;
		}
		static void RegisterSoundSystem(std::unique_ptr<SoundSystem>&& pSSInstance)
		{
			m_pSSInstance = std::move(pSSInstance);
		}
	};
}
