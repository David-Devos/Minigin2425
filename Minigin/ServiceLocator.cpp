#include "ServiceLocator.h"
namespace dae
{
	std::unique_ptr<dae::SoundSystem> ServiceLocator::m_pSSInstance = nullptr;
}