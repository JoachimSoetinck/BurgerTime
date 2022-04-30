#include "MiniginPCH.h"
#include "Sound.h"
#include "SDL_mixer.h"

class Sound::SoundImpl
{
	Mix_Chunk* m_pChunk{};
	std::string m_Path;

public:
	SoundImpl(const std::string& path)
		:m_Path(path)
	{}

	~SoundImpl()
	{
		if (m_pChunk)
			Mix_FreeChunk(m_pChunk);
	}

	void Load()
	{
		m_pChunk = Mix_LoadWAV(m_Path.c_str());
		if (m_pChunk == nullptr)
		{
			std::cout << "could not find path: " << m_Path << "\n";
		}
	}

	bool IsLoaded() const
	{
		if (m_pChunk == nullptr)
			return false;

		return true;
	}

	bool Play()
	{
		if (!IsLoaded())
			return false;

		int channel = Mix_PlayChannel(-1, m_pChunk,0);
		return channel == -1 ? false : true;
	}

	void SetVolume(int volume)
	{
		if (IsLoaded())
		{
			Mix_Volume(-1, volume);
		}
	}

	int GetVolume() const
	{
		if (IsLoaded())
		{
			return Mix_VolumeChunk(m_pChunk, -1);
		}
		return 0;
	}
};

Sound::Sound(const std::string& path)
{
	pImpl = new SoundImpl(path);
}

Sound::~Sound()
{
	delete pImpl;
}

void Sound::Load()
{
	pImpl->Load();
}

bool Sound::Play()
{
	return pImpl->Play();
}

void Sound::SetVolume(int volume)
{
	pImpl->SetVolume(volume);
}

bool Sound::IsLoaded() const
{
	return pImpl->IsLoaded();
}

int Sound::GetVolume() const
{
	return pImpl->GetVolume();
}
