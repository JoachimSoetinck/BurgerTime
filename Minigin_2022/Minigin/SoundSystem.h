#pragma once
#include <mutex>
#include <queue>
#include <string>

#include "Sound.h"


namespace  dae
{
	class BaseSoundSystem
	{
	public:
		virtual ~BaseSoundSystem() = default;
		virtual void RegisterSound(const std::string& path) = 0;
		virtual void CheckQueue() = 0;

	protected:
		std::vector<Sound*> m_soundsPlayed{};
		std::queue<Sound*> m_Sounds{};
		std::mutex mutex;
		std::thread thread;
		bool m_Continue = true;
	};

	class Null_SoundSystem final : public BaseSoundSystem
	{
	public:
		void RegisterSound(const std::string& path) override;
		void CheckQueue() override;
	};

	class SoundSystem final : public BaseSoundSystem
	{
	public:
		SoundSystem();
		~SoundSystem();
		SoundSystem(const SoundSystem& other) = default;
		SoundSystem(SoundSystem&& other) = default;
		SoundSystem& operator=(const SoundSystem& other) = default;
		SoundSystem& operator=(SoundSystem&& other) = default;

		void RegisterSound(const std::string& path) override;
		void CheckQueue() override;

	private:

	};

	class SoundSystemDebug final : public BaseSoundSystem
	{
	public:
		SoundSystemDebug();
		~SoundSystemDebug();
		SoundSystemDebug(const SoundSystemDebug& other) = delete;
		SoundSystemDebug(SoundSystemDebug&& other) noexcept = delete;
		SoundSystemDebug& operator=(const SoundSystemDebug& other) = delete;
		SoundSystemDebug& operator=(SoundSystemDebug&& other) noexcept = delete;

		void RegisterSound(const std::string& path) override;
		void CheckQueue();

\

	};

}