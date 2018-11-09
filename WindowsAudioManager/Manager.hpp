#ifndef WINDOWS_AUDIO_MANAGER_MANAGER_HPP
#define WINDOWS_AUDIO_MANAGER_MANAGER_HPP

#include "Base.hpp"

#include "WindowsAudioManager.hpp"

#include <endpointvolume.h>
#include <mmdeviceapi.h>

namespace WindowsAudioManager
{
	class Device;

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

		virtual IAudioDevicePtr getDefaultOutputDevice() override;
		virtual IAudioDevicePtr getDefaultInputDevice() override;

		virtual void setDefaultOutputDevice(IAudioDevicePtr device) override;
		virtual void setDefaultInputDevice(IAudioDevicePtr device) override;
	private:
		IAudioDevicePtr findWindowsDeviceById(std::wstring id);

		void updateDevices();
		std::vector<std::shared_ptr<Device>> getDevices(IMMDeviceCollection* devices, EDataFlow dataFlow);

		bool m_isLoaded;

		IMMDeviceEnumerator* m_enumerator;
		IAudioEndpointVolume* m_volume;

		std::vector<std::shared_ptr<Device>> m_devices;
	};
}

#endif // WINDOWS_AUDIO_MANAGER_MANAGER_HPP