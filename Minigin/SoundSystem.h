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
		virtual void stopSound() = 0;
		virtual void loadSound(const std::string& filePath, unsigned int id) = 0;
		virtual void playSound(unsigned int id, const int volume) = 0;
	protected:

	private:
	};
	class NullSoundSystem final : public SoundSystem
	{
	public:
		NullSoundSystem() = default;
		~NullSoundSystem() override = default;
		NullSoundSystem(const NullSoundSystem&) = delete;
		NullSoundSystem(NullSoundSystem&&) = delete;
		NullSoundSystem& operator=(const NullSoundSystem&) = delete;
		NullSoundSystem& operator=(NullSoundSystem&&) = delete;

		void stopSound() override {}
		void loadSound(const std::string& , unsigned int ) override {};
		void playSound(unsigned int , const int ) override {};
	private:
	};

	class SDLSoundSystem final : public SoundSystem
	{
	private:
		const float m_Volume{ 1.f };

		std::map<unsigned int, std::unique_ptr<Mix_Chunk*>> m_pChunks{};
		std::map<unsigned int, std::unique_ptr<Mix_Music*>> m_pMusic{};
		std::mutex m_Mutex{};
		std::jthread m_Thread{};
		// id, volume, loops
		std::deque<std::tuple<unsigned int, int, int>> m_PlayQueue{};
		std::deque<std::tuple<unsigned int, std::string>> m_LoadQueue{};
		void playSoundFromQueue(unsigned int id, const int volume);
		void loadSoundFromQueue(const std::string& filePath, unsigned int id);

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
		void Shutdown() { m_Game = false; };
	private:
		bool m_Game = true;
		//std::condition_variable m_Condition; oftewel moet dit buiten soundsystem liggen, oftewel public getter voor notify?
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
		std::unique_ptr<SoundSystem> m_pSoundSystem{ std::make_unique<NullSoundSystem>() };
	};
}