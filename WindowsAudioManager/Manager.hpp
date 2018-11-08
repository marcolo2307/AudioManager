#ifndef WINDOWS_AUDIO_MANAGER_MANAGER_HPP
#define WINDOWS_AUDIO_MANAGER_MANAGER_HPP

#include "../AudioManager/AudioManager.hpp"

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

		virtual std::vector<IDevicePtr> getAllDevices() override;

		virtual IDevicePtr getMasterOutputDevice() override;
		virtual IDevicePtr getMasterInputDevice() override;

		virtual void setMasterOutputDevice(IDevicePtr device) override;
		virtual void setMasterInputDevice(IDevicePtr device) override;
	};
}

#endif // WINDOWS_AUDIO_MANAGER_MANAGER_HPP