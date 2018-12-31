#pragma once

#include "DllMain.h"
#include "Types.h"
#include <msclr/lock.h>

using namespace System;

namespace SBAuroraReactive 
{
	public value struct EnumeratedDevice
	{
		u16 vid, pid;
		u16 ledInfoFlag, totalNumLeds;
		String^ serialNo;
		String^ deviceInstance;
		String^ friendlyName;
	};

	public ref class LEDManager
	{
	public:
		LEDManager();
		virtual ~LEDManager()
		{
			if (m_Instance != nullptr)
			{
				m_Instance->Release();
				m_Instance = nullptr;
			}
		}
		!LEDManager()
		{
			if (m_Instance != nullptr)
			{
				m_Instance->Release();
				m_Instance = nullptr;
			}
		}

		array<EnumeratedDevice>^ EnumConnectedDevices();

	private:
		ICTLEDMgr* m_Instance = nullptr;
		Object^ m_enumLock = gcnew Object();
	};
}
