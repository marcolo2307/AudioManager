#include "Manager.hpp"

namespace WindowsAudioManager
{
	Manager::Manager()
	{

	}

	Manager::~Manager()
	{

	}

	bool Manager::isLoaded()
	{
		return true;
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