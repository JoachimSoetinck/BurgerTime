#include "MiniginPCH.h"
#include "ServiceLocator.h"

dae::BaseSoundSystem* dae::ServiceLocator::m_SoundSystem{};
dae::Null_SoundSystem dae::ServiceLocator::m_DefaultSystem{};

dae::ServiceLocator::~ServiceLocator()
{
	delete m_SoundSystem;
}

dae::BaseSoundSystem& dae::ServiceLocator::GetSoundSystem()
{
	return *m_SoundSystem;
}

void dae::ServiceLocator::RegisterSoundSystem(BaseSoundSystem* soundSystem)
{
	//Deleting current system ->else causes memory leak
	if(soundSystem != &m_DefaultSystem)
	delete m_SoundSystem;

	m_SoundSystem = soundSystem == nullptr ? &m_DefaultSystem : soundSystem;
}
