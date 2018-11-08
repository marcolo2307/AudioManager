#ifndef AUDIO_MANAGER_HPP
#define AUDIO_MANAGER_HPP

#include <string>
#include <vector>

class IDevice
{
public:
	enum Status
	{
		Unknown,
		Active,
		Disabled,
		Unplugged
	};

	enum Type
	{
		Output,
		Input
	};

	virtual ~IDevice() {}

	virtual int getID() const = 0;
	virtual std::wstring getName() const = 0;

	virtual Status getStatus() const = 0;
	virtual Type getType() const = 0;
};

typedef std::weak_ptr<IDevice> IDevicePtr;

class IAudioManager
{
public:
	virtual ~IAudioManager() {}
	virtual bool isLoaded() = 0;

	virtual int getVolume() = 0;
	virtual void setVolume(int volume) = 0;

	virtual bool getMute() = 0;
	virtual void setMute(bool mute) = 0;

	virtual std::vector<IDevicePtr> getAllDevices() = 0;

	virtual IDevicePtr getMasterOutputDevice() = 0;
	virtual IDevicePtr getMasterInputDevice() = 0;

	virtual void setMasterOutputDevice(IDevicePtr device) = 0;
	virtual void setMasterInputDevice(IDevicePtr device) = 0;
};

typedef IAudioManager*(*AudioManagerLoader)();

#endif // AUDIO_MANAGER_HPP