#pragma once
#include "SoundSystem.h"

 namespace dae
{
	 class ServiceLocator final
	 {
	 public:

		 ServiceLocator() = default;
		 ~ServiceLocator();
		 ServiceLocator(const ServiceLocator& other) = delete;
		 ServiceLocator(ServiceLocator&& other) = delete;
		 ServiceLocator& operator=(const ServiceLocator& other) = delete;
		 ServiceLocator& operator=(ServiceLocator&& other) = delete;

		 static dae::BaseSoundSystem& GetSoundSystem();
		 static void RegisterSoundSystem(BaseSoundSystem* soundSystem);

	 private:
		 static BaseSoundSystem* m_SoundSystem;
		 static Null_SoundSystem m_DefaultSystem;
	 };
}


