#include "SoundSystem.h"
#include <SDL_mixer.h>
#include <cassert>
#include <iostream>
#include <filesystem>
#include "ResourceManager.h"
#include <SDL.h>
#include <regex>
namespace dae
{
	// SDL Sound System
	SDLSoundSystem::SDLSoundSystem()
	{
		SDL_Init(SDL_INIT_AUDIO);
		Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);
		m_Thread = std::jthread(&SDLSoundSystem::doQueue, this);
	}
	void SDLSoundSystem::playSound(unsigned int id, const int volume)
	{
		if (m_pChunks.contains(id))
		{
			int channel = Mix_GroupAvailable(-1);
			if (channel == -1)
			{
				std::cerr << "No available channels to play sound" << std::endl;
				return;
			}
			else
			{
				Mix_Volume(channel, volume);
				Mix_PlayChannel(channel, *(m_pChunks[id]), 0);
				return;
			}
		}
		else if (m_pMusic.contains(id))
		{
			Mix_VolumeMusic(volume);
			Mix_PlayMusic(*(m_pMusic[id]), -1);
			return;
		}
		else
		{
			std::cout << "Sound ID not found: " << id << std::endl;
			return;
		}
	}
	void SDLSoundSystem::stopSound()
	{
		Mix_HaltChannel(-1);
	}
	void SDLSoundSystem::loadSound(const std::string& filePath, unsigned int id)
	{
		const auto filename = std::filesystem::path(filePath).filename().string();

		if (m_pChunks.contains(id) || m_pMusic.contains(id))
		{
			std::cerr << "Sound ID already exists: " << id << std::endl;
			return;
		}

		static const std::regex pattern(R"(\.(wav|mp3)$)", std::regex::icase);
		if (std::regex_match(filename, pattern))
		{
			m_pMusic[id] = std::make_unique<Mix_Music*>(Mix_LoadMUS(filePath.c_str()));
			return;
		}
		else
		{
			m_pChunks[id] = std::make_unique<Mix_Chunk*>(Mix_LoadWAV(filePath.c_str()));
			return;
		}
	}
	void SDLSoundSystem::doQueue()
	{
		std::unique_lock<std::mutex> lock(m_Mutex);
		while (!m_Queue.empty())
		{
			auto [id, volume, loops] = m_Queue.front();
			m_Queue.pop_front();
			lock.unlock();
			playSound(id, volume);
			lock.lock();
		}
	}




	// Debug Sound System
	void DebugSoundSystem::playSound(unsigned int id, const int volume)
	{
		std::cout << "Playing sound with ID: " << id << " at volume: " << volume << std::endl;
		m_pSoundSystem->playSound(id, volume);
	}

	void DebugSoundSystem::stopSound()
	{
		std::cout << "Stopping sound" << std::endl;
		m_pSoundSystem->stopSound();
	}
}
