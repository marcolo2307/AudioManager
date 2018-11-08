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

	std::vector<IDevicePtr> Manager::getAllDevices()
	{
		return std::vector<IDevicePtr>();
	}

	IDevicePtr Manager::getMasterOutputDevice()
	{
		return IDevicePtr();
	}

	IDevicePtr Manager::getMasterInputDevice()
	{
		return IDevicePtr();
	}

	void Manager::setMasterOutputDevice(IDevicePtr device)
	{

	}

	void Manager::setMasterInputDevice(IDevicePtr device)
	{

	}
}