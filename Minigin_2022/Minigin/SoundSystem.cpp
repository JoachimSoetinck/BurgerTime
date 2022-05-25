#include "MiniginPCH.h"
#include "SoundSystem.h"

#include <mutex>
#include <queue>
#include <SDL_mixer.h>
#include <thread>

#include "Sound.h"



dae::SoundSystem::SoundSystem()
{
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, MIX_CHANNELS);
	thread = std::thread([this] { this->CheckQueue(); });
}

dae::SoundSystem::~SoundSystem()
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

void dae::SoundSystem::RegisterSound(const std::string& path)
{
	m_Sounds.emplace(new Sound(path));
}

void dae::SoundSystem::CheckQueue()
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

void dae::Null_SoundSystem::RegisterSound(const std::string& )
{
	
}

void dae::Null_SoundSystem::CheckQueue()
{
	
}

dae::SoundSystemDebug::SoundSystemDebug()
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

dae::SoundSystemDebug::~SoundSystemDebug()
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

void dae::SoundSystemDebug::RegisterSound(const std::string& path)
{
	m_Sounds.emplace(new Sound(path));
	std::size_t botDirPos = path.find_last_of("/");
	// get directory
	std::string dir = path.substr(botDirPos + 1, path.length());
	std::cout << "Played Sound: " << dir << std::endl;
}

void dae::SoundSystemDebug::CheckQueue()
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
