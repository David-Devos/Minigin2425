#pragma once
#include <SDL_mixer.h>
#include <vector>
#include <memory>
#include <map>
#include <mutex>
#include <deque>
namespace dae
{

	class SoundSystem
	{
	public:
		SoundSystem() = default;
		virtual ~SoundSystem() = default;
		SoundSystem(const SoundSystem&) = delete;
		SoundSystem(SoundSystem&&) = delete;
		SoundSystem& operator=(const SoundSystem&) = delete;
		SoundSystem& operator=(SoundSystem&&) = delete;
		/*void Initialize();
		void Shutdown();
		void Update();*/
		virtual void playSound(unsigned int id, const int volume) = 0;
		virtual void stopSound() = 0;
		virtual void loadSound(const std::string& filePath, unsigned int id) = 0;
	};
	class DefaultSoundSystem final : public SoundSystem
	{
	public:
		DefaultSoundSystem() = default;
		~DefaultSoundSystem() override = default;
		DefaultSoundSystem(const DefaultSoundSystem&) = delete;
		DefaultSoundSystem(DefaultSoundSystem&&) = delete;
		DefaultSoundSystem& operator=(const DefaultSoundSystem&) = delete;
		DefaultSoundSystem& operator=(DefaultSoundSystem&&) = delete;

		void playSound(unsigned int , const int ) override {};
		void stopSound() override {}
		void loadSound(const std::string& , unsigned int ) override {};
	};

	class SDLSoundSystem final : public SoundSystem
	{
	private:
		std::vector<std::unique_ptr<Mix_Chunk>> m_pSound{};
		const float m_Volume{ 1.f };

		std::map<unsigned int, std::unique_ptr<Mix_Chunk*>> m_pChunks{};
		std::map<unsigned int, std::unique_ptr<Mix_Music*>> m_pMusic{};
		std::mutex m_Mutex{};
		std::jthread m_Thread{};
		// id, volume, loops
		std::deque<std::tuple<unsigned int, int, int>> m_Queue{};
	public:
		SDLSoundSystem();
		~SDLSoundSystem() override = default;
		SDLSoundSystem(const SDLSoundSystem&) = delete;
		SDLSoundSystem(SDLSoundSystem&&) = delete;
		SDLSoundSystem& operator=(const SDLSoundSystem&) = delete;
		SDLSoundSystem& operator=(SDLSoundSystem&&) = delete;

		void doQueue();
		void playSound(unsigned int id, const int volume) override;

		void stopSound() override;

		void loadSound(const std::string& filePath, unsigned int id) override;

	};

	class DebugSoundSystem final : public SoundSystem
	{
	public:
		DebugSoundSystem() = default;
		~DebugSoundSystem() override = default;
		DebugSoundSystem(const DebugSoundSystem&) = delete;
		DebugSoundSystem(DebugSoundSystem&&) = delete;
		DebugSoundSystem& operator=(const DebugSoundSystem&) = delete;
		DebugSoundSystem& operator=(DebugSoundSystem&&) = delete;
		void playSound(unsigned int id, const int volume) override;
		void stopSound() override;
	private:
		std::unique_ptr<SoundSystem> m_pSoundSystem{ std::make_unique<DefaultSoundSystem>() };
	};
}