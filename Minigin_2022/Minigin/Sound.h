#pragma once
class Sound final
{
public:
	Sound(const std::string& path);
	~Sound();

	void Load();
	bool Play();

	void SetVolume(int volume);
	int GetVolume() const;
	bool IsLoaded() const;


private:

	class SoundImpl;
	SoundImpl* pImpl{};
};