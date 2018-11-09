#ifndef AUDIO_MANAGER_HPP
#define AUDIO_MANAGER_HPP

#include <string>
#include <vector>

class IAudioDevice
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

	virtual ~IAudioDevice() {}

	virtual int getID() const = 0;
	virtual std::wstring getName() const = 0;

	virtual Status getStatus() const = 0;
	virtual Type getType() const = 0;
};

typedef std::shared_ptr<IAudioDevice> IAudioDevicePtr;

class IAudioManager
{
public:
	virtual ~IAudioManager() {}
	virtual bool isLoaded() = 0;

	virtual int getVolume() = 0;
	virtual void setVolume(int volume) = 0;

	virtual bool getMute() = 0;
	virtual void setMute(bool mute) = 0;

	virtual std::vector<IAudioDevicePtr> getAllDevices() = 0;

	virtual IAudioDevicePtr getDefaultOutputDevice() = 0;
	virtual IAudioDevicePtr getDefaultInputDevice() = 0;

	virtual void setDefaultOutputDevice(IAudioDevicePtr device) = 0;
	virtual void setDefaultInputDevice(IAudioDevicePtr device) = 0;
};

typedef IAudioManager*(*AudioManagerLoader)();

#endif // AUDIO_MANAGER_HPP