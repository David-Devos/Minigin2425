#include "SoundSystem.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <regex>
#include <iostream>
#include "ResourceManager.h"
namespace dae
{
	// SDL Sound System
	SDLSoundSystem::SDLSoundSystem()
	{
		SDL_Init(SDL_INIT_AUDIO);
		Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);
		m_Thread = std::jthread(&SDLSoundSystem::doQueue, this);
	}
	void SDLSoundSystem::playSoundFromQueue(unsigned int id, const int volume)
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
	void SDLSoundSystem::loadSoundFromQueue(const std::string& filePath, unsigned int id)
	{
		if (m_pChunks.contains(id) || m_pMusic.contains(id))
		{
			std::cerr << "Sound ID already exists: " << id << std::endl;
			return;
		}

		static const std::regex patternWAV(R"(.*\.wav)", std::regex::icase);
		static const std::regex patternMP3(R"(.*\.mp3)", std::regex::icase);
		if (std::regex_match(filePath, patternMP3))
		{
			m_pMusic[id] = std::make_unique<Mix_Music*>(Mix_LoadMUS(filePath.c_str()));
			return;
		}
		else if (std::regex_match(filePath, patternWAV))
		{
			m_pChunks[id] = std::make_unique<Mix_Chunk*>(Mix_LoadWAV(filePath.c_str()));
			return;
		}
	}
	void SDLSoundSystem::doQueue()
	{
		std::unique_lock<std::mutex> lock(m_Mutex);
		while (true)
		{
			while (!m_LoadQueue.empty())
			{
				auto [id, filePath] = m_LoadQueue.front();
				m_LoadQueue.pop_front();
				lock.unlock();
				loadSoundFromQueue(filePath, id);
				lock.lock();
			}
			while (!m_PlayQueue.empty())
			{
				auto [id, volume, loops] = m_PlayQueue.front();
				m_PlayQueue.pop_front();
				lock.unlock();
				playSoundFromQueue(id, volume);
				lock.lock();
			}
		}
	}

	void SDLSoundSystem::playSound(unsigned int id, const int volume)
	{
		m_PlayQueue.push_back(std::tuple<unsigned int, int, int>(id, volume, 0));
	}
	void SDLSoundSystem::loadSound(const std::string& filePath, unsigned int id)
	{
		m_LoadQueue.push_back(std::tuple<unsigned int, std::string>(id, filePath));
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
