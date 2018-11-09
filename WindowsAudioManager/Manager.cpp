#include "Manager.hpp"
#include "Device.hpp"
#include "PolicyConfig.h"

#include <functiondiscoverykeys.h>

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

		m_isLoaded = true;

		try
		{
			updateDevices();
			getDefaultOutputDevice();
		}
		catch (...)
		{
			m_isLoaded = false;
		}
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
		if (!m_isLoaded)
			throw std::runtime_error("WindowsAudioManager is not loaded.");
		float volume;
		if (m_volume->GetMasterVolumeLevelScalar(&volume)!=0)
			throw std::runtime_error("Failed to get system volume.");
		return static_cast<int>(std::round(100 * volume));
	}

	void Manager::setVolume(int volume)
	{
		if (!m_isLoaded)
			throw std::runtime_error("WindowsAudioManager is not loaded.");
		float normalized = static_cast<float>(volume);
		normalized /= 1000.f;
		normalized *= 10;
		if (m_volume->SetMasterVolumeLevelScalar(normalized, NULL) != 0)
			throw std::runtime_error("Failed to set system volume.");
	}

	bool Manager::getMute()
	{
		if (!m_isLoaded)
			throw std::runtime_error("WindowsAudioManager is not loaded.");
		BOOL mute;
		if (m_volume->GetMute(&mute)!=0)
			throw std::runtime_error("Failed to get system mute.");
		return mute;
	}

	void Manager::setMute(bool mute)
	{
		if (!m_isLoaded)
			throw std::runtime_error("WindowsAudioManager is not loaded.");
		if (m_volume->SetMute(static_cast<BOOL>(mute), NULL)!=0)
			throw std::runtime_error("Failed to set system mute.");
	}

	std::vector<IAudioDevicePtr> Manager::getAllDevices()
	{
		if (!m_isLoaded)
			throw std::runtime_error("WindowsAudioManager is not loaded.");
		updateDevices();
		std::vector<IAudioDevicePtr> result;
		for (auto i : m_devices)
			result.push_back(i);
		return result;
	}

	IAudioDevicePtr Manager::getDefaultOutputDevice()
	{
		if (!m_isLoaded)
			throw std::runtime_error("WindowsAudioManager is not loaded.");
		IMMDevice* device;
		HRESULT result = m_enumerator->GetDefaultAudioEndpoint(eRender, eConsole, &device);
		if (result != 0)
			throw std::runtime_error("Failed to get default device.");
		LPWSTR id;
		result = device->GetId(&id);
		if (result != 0)
		{
			device->Release();
			throw std::runtime_error("Failed to get default device.");
		}

		if (m_volume != nullptr)
			m_volume->Release();
		result = device->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_ALL, NULL, (LPVOID*)&m_volume);
		device->Release();
		if (result != 0)
			throw std::runtime_error("Failed to get default device.");

		std::wstring ID(id);
		return findWindowsDeviceById(id);
	}

	IAudioDevicePtr Manager::getDefaultInputDevice()
	{
		if (!m_isLoaded)
			throw std::runtime_error("WindowsAudioManager is not loaded.");
		IMMDevice* device;
		HRESULT result = m_enumerator->GetDefaultAudioEndpoint(eCapture, eConsole, &device);
		if (result != 0)
			throw std::runtime_error("Failed to get default input device.");
		LPWSTR id;
		result = device->GetId(&id);
		device->Release();
		if (result != 0)
			throw std::runtime_error("Failed to get default input device.");

		std::wstring ID(id);
		return findWindowsDeviceById(id);
	}

	void Manager::updateDevices()
	{
		if (!m_isLoaded)
			throw std::runtime_error("WindowsAudioManager is not loaded.");
		int counter = 1;
		IMMDeviceCollection *render, *capture;
		HRESULT result = m_enumerator->EnumAudioEndpoints(eRender, DEVICE_STATEMASK_ALL, &render);
		if (result != 0)
			throw std::runtime_error("Failed to update devices.");
		result = m_enumerator->EnumAudioEndpoints(eCapture, DEVICE_STATEMASK_ALL, &capture);
		if (result != 0)
		{
			render->Release();
			throw std::runtime_error("Failed to update devices.");
		}
		m_devices.clear();
		try
		{
			auto renderers = getDevices(render, eRender);
			auto capturers = getDevices(capture, eCapture);
			m_devices.insert(m_devices.end(), renderers.begin(), renderers.end());
			m_devices.insert(m_devices.end(), capturers.begin(), capturers.end());
		}
		catch (...)
		{
			render->Release();
			capture->Release();
			throw;
		}
		render->Release();
		capture->Release();
	}

	IAudioDevicePtr Manager::findWindowsDeviceById(std::wstring id)
	{
		updateDevices();
		for (auto i : m_devices)
		{
			if (i->getSystemID() == id)
				return std::dynamic_pointer_cast<IAudioDevice>(i);
		}
		throw std::runtime_error("Audio device not found.");
	}

	std::vector<std::shared_ptr<Device>> Manager::getDevices(IMMDeviceCollection * devices, EDataFlow dataFlow)
	{
		std::vector<std::shared_ptr<Device>> devs;
		UINT count;
		HRESULT result = devices->GetCount(&count);
		if (result != 0)
			throw std::runtime_error("Failed to count devices.");
		for (unsigned int i = 0; i < count; i++)
		{
			IMMDevice* device;
			result = devices->Item(i, &device);
			if (result != 0)
				continue;
			LPWSTR id;
			result = device->GetId(&id);
			if (result != 0)
			{
				device->Release();
				continue;
			}

			Device::Status status;
			DWORD rawStatus;
			result = device->GetState(&rawStatus);
			if (result != 0)
			{
				device->Release();
				continue;
			}
			switch (rawStatus)
			{
			case DEVICE_STATE_ACTIVE: status = Device::Active; break;
			case DEVICE_STATE_DISABLED: status = Device::Disabled; break;
			case DEVICE_STATE_NOTPRESENT:
			case DEVICE_STATE_UNPLUGGED: status = Device::Unplugged; break;
			default: status = Device::Unknown; break;
			}

			IPropertyStore* properties;
			result = device->OpenPropertyStore(STGM_READ, &properties);
			if (result != 0)
			{
				device->Release();
				continue;
			}

			PROPVARIANT name;
			PropVariantInit(&name);
			result = properties->GetValue(PKEY_Device_FriendlyName, &name);
			if (result != 0)
			{
				device->Release();
				properties->Release();
				continue;
			}
			device->Release();
			properties->Release();
			devs.push_back(std::shared_ptr<Device>(new Device(std::wstring(name.pwszVal), std::wstring(id), status, dataFlow == eRender ? Device::Output : Device::Input)));
		}
		return devs;
	}

	void Manager::setDefaultOutputDevice(IAudioDevicePtr device)
	{
		if (!m_isLoaded)
			throw std::runtime_error("WindowsAudioManager is not loaded.");
		Device* windowsDevice = std::static_pointer_cast<Device>(device).get();
		if (windowsDevice==nullptr)
			throw std::runtime_error("Invalid device.");
		IPolicyConfigVista* policyConfig;
		ERole reserved = eConsole;
		HRESULT result = CoCreateInstance(__uuidof(CPolicyConfigVistaClient), NULL, CLSCTX_ALL, __uuidof(IPolicyConfigVista), (LPVOID*)&policyConfig);
		if (result != 0)
			throw std::runtime_error("Failed to set default device.");
		result = policyConfig->SetDefaultEndpoint(windowsDevice->getSystemID().c_str(), reserved);
		policyConfig->Release();
	}

	void Manager::setDefaultInputDevice(IAudioDevicePtr device)
	{
		setDefaultOutputDevice(device);
	}
}