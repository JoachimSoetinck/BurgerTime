#include "MiniginPCH.h"
#include "SoundSystem.h"

#include <mutex>
#include <queue>
#include <SDL_mixer.h>
#include <thread>

#include "Sound.h"


class dae::BaseSoundSystem::SoundSystemImpl
{
private:
	std::vector<Sound*> m_soundsPlayed{};
	std::queue<Sound*> m_Sounds{};
	std::mutex mutex;
	std::thread thread;
	bool m_Continue = true;

	void CheckQueue()
	{
		while (m_Continue)
		{
			if (m_Sounds.size() > 0)
			{
				mutex.lock();

				m_Sounds.front()->Load();
				m_Sounds.front()->Play();
				m_soundsPlayed.emplace_back(m_Sounds.front());

				mutex.unlock();
				m_Sounds.pop();
			}

		}
	}

public:
	SoundSystemImpl()
	{
		Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, MIX_CHANNELS);
		thread = std::thread([this] { this->CheckQueue(); });

	}

	~SoundSystemImpl()
	{
		m_Continue = false;

		thread.join();
		for (size_t i = 0; i < m_soundsPlayed.size(); i++)
		{
			delete m_soundsPlayed[i];
		}

		//Closing SDL Mix
		Mix_CloseAudio();
	}

	void RegisterSound(const std::string& path)
	{
		m_Sounds.emplace(new Sound(path));
	}


};

dae::SoundSystem::SoundSystem() 
{
	m_pImpl = new SoundSystemImpl();
}

dae::SoundSystem::~SoundSystem()
{
	delete m_pImpl;
}

void dae::SoundSystem::RegisterSound(const std::string& path)
{
	m_pImpl->RegisterSound(path);
}

void dae::Null_SoundSystem::RegisterSound(const std::string& )
{

}

dae::SoundSystemDebug::SoundSystemDebug()
{
	m_pImpl = new SoundSystemImpl();
}

dae::SoundSystemDebug::~SoundSystemDebug()
{
	delete m_pImpl;
}

void dae::SoundSystemDebug::RegisterSound(const std::string& path)
{
	m_pImpl->RegisterSound(path);
	std::size_t botDirPos = path.find_last_of("/");
	// get directory
	std::string dir = path.substr(botDirPos+1, path.length());
	std::cout << "Played Sound: " << dir << std::endl;
}
