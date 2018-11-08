#define WINDOWS_AUDIO_MANAGER_EXPORTS

#include "WindowsAudioManager.hpp"
#include "Manager.hpp"

#ifdef _cplusplus
extern "C" 
#endif

WINDOWS_AUDIO_MANAGER_API IAudioManager* CreateAudioManager()
{
	return new WindowsAudioManager::Manager();
}