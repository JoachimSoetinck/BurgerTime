#pragma once
#include <string>


namespace  dae
{
	class BaseSoundSystem
	{
	public:
		virtual ~BaseSoundSystem() = default;
		virtual void RegisterSound(const std::string& path) = 0;

	protected:
		class SoundSystemImpl;
		SoundSystemImpl* m_pImpl;
	};

	class Null_SoundSystem final : public BaseSoundSystem
	{
	public:
		void RegisterSound(const std::string& path) override;
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

	private:

	};

}
