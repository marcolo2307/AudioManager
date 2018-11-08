#ifndef WINDOWS_AUDIO_MANAGER_MANAGER_HPP
#define WINDOWS_AUDIO_MANAGER_MANAGER_HPP

#include "Base.hpp"

#include "WindowsAudioManager.hpp"

namespace WindowsAudioManager
{
	class Manager : public IAudioManager
	{
	public:
		Manager();
		virtual ~Manager();

		virtual bool isLoaded() override;

		virtual int getVolume() override;
		virtual void setVolume(int volume) override;

		virtual bool getMute() override;
		virtual void setMute(bool mute) override;

		virtual std::vector<IAudioDevicePtr> getAllDevices() override;

		virtual IAudioDevicePtr getMasterOutputDevice() override;
		virtual IAudioDevicePtr getMasterInputDevice() override;

		virtual void setMasterOutputDevice(IAudioDevicePtr device) override;
		virtual void setMasterInputDevice(IAudioDevicePtr device) override;
	};
}

#endif // WINDOWS_AUDIO_MANAGER_MANAGER_HPP