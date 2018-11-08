#include "Manager.hpp"
#include "Device.hpp"

namespace WindowsAudioManager
{
	Manager::Manager()
	{
		m_isLoaded = false;
		m_volume = nullptr;
		m_enumerator = nullptr;

		HRESULT result = CoInitialize(NULL);
		if (result != 0)
			return;
		result = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (LPVOID*)&m_enumerator);
		if (result != 0)
			return;
	}

	Manager::~Manager()
	{
		if (m_volume != nullptr)
		{
			m_volume->Release();
			m_volume = nullptr;
		}

		if (m_enumerator != nullptr)
		{
			m_enumerator->Release();
			m_enumerator = nullptr;
		}

		CoUninitialize();
	}

	bool Manager::isLoaded()
	{
		return m_isLoaded;
	}

	int Manager::getVolume()
	{
		return 0;
	}

	void Manager::setVolume(int volume)
	{

	}

	bool Manager::getMute()
	{
		return false;
	}

	void Manager::setMute(bool mute)
	{

	}

	std::vector<IAudioDevicePtr> Manager::getAllDevices()
	{
		return std::vector<IAudioDevicePtr>();
	}

	IAudioDevicePtr Manager::getMasterOutputDevice()
	{
		return IAudioDevicePtr();
	}

	IAudioDevicePtr Manager::getMasterInputDevice()
	{
		return IAudioDevicePtr();
	}

	void Manager::setMasterOutputDevice(IAudioDevicePtr device)
	{

	}

	void Manager::setMasterInputDevice(IAudioDevicePtr device)
	{

	}
}