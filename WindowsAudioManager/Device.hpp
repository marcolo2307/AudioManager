#ifndef WINDOWS_AUDIO_MANAGER_DEVICE_HPP
#define WINDOWS_AUDIO_MANAGER_DEVICE_HPP

#include "Base.hpp"

namespace WindowsAudioManager
{
	class Device : public IAudioDevice
	{
	public:
		Device(int id, std::wstring name, std::wstring systemID);
		virtual ~Device();

		inline virtual int getID() const override { return m_ID; }
		inline virtual std::wstring getName() const override { return m_name; }
		inline virtual Status getStatus() const override { return m_status; }
		inline virtual Type getType() const override { return m_type; }

		inline std::wstring getSystemID() const { return m_systemID; }
	private:
		int m_ID;
		std::wstring m_name;
		std::wstring m_systemID;
		Status m_status;
		Type m_type;
	};
}

#endif // WINDOWS_AUDIO_MANAGER_DEVICE_HPP