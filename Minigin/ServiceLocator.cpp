#include "ServiceLocator.h"
namespace dae
{
	std::unique_ptr<SoundSystem> ServiceLocator::m_pSSInstance = nullptr;
	std::unique_ptr<NullSoundSystem> ServiceLocator::m_pNullSSInstance = std::make_unique<NullSoundSystem>();
	std::unique_ptr<ColliderManager> ServiceLocator::m_pColManagerInstance = std::make_unique<ColliderManager>();
}