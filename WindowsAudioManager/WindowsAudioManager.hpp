#ifndef WINDOWS_AUDIO_MANAGER_HPP
#define WINDOWS_AUDIO_MANAGER_HPP

#include "Base.hpp"

#ifndef __WIN32
#	ifdef WINDOWS_AUDIO_MANAGER_EXPORTS
#		define WINDOWS_AUDIO_MANAGER_API __declspec(dllexport)
#	else
#		define WINDOWS_AUDIO_MANAGER_API __declspec(dllimport)
#	endif
#else
#	define WINDOWS_AUDIO_MANAGER_API
#endif

#ifdef __cplusplus
extern "C" {
#endif

WINDOWS_AUDIO_MANAGER_API IAudioManager* CreateAudioManager();

#ifdef __cplusplus
}
#endif

#endif // WINDOWS_AUDIO_MANAGER_HPP