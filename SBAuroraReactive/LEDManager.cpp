#include "LEDManager.h"

SBAuroraReactive::LEDManager::LEDManager()
{
	ICTLEDMgr* outMgr = nullptr;
	const auto creationResult = CreateLEDManager(&outMgr);
	if (creationResult == CTINTRFCRESULT_Success)
		m_Instance = outMgr;
	else
		throw gcnew System::Exception("Error creating ICTLEDMgr");
}

array<SBAuroraReactive::EnumeratedDevice>^ SBAuroraReactive::LEDManager::EnumConnectedDevices()
{
	auto tempList = gcnew System::Collections::Generic::List<EnumeratedDevice>();

	msclr::lock l(m_enumLock);
	DWORD currIdx = 0;
	for (;;)
	{
		USHORT usVendorID = 0;
		USHORT usProductID = 0;
		wchar_t serialNoBuf[256] ={ 0 };
		wchar_t deviceInstanceBuf[256] ={ 0 };
		DWORD sizeOfSerialNoBuf = (DWORD)array_countof(serialNoBuf)-1;
		DWORD sizeOfDeviceInstanceBuf = (DWORD)array_countof(deviceInstanceBuf)-1;
		USHORT usLedInfoFlag = 0;
		USHORT usTotalNumLeds = 0;
		wchar_t deviceFriendlyNameBuf[256] ={ 0 };
		DWORD sizeOfDeviceFriendlyNameBuf = (DWORD)array_countof(deviceFriendlyNameBuf)-1;
		DWORD dwFlag = 0;
		HRESULT hr = m_Instance->EnumConnectedDevices(
			currIdx, &usVendorID, &usProductID,
			serialNoBuf, &sizeOfSerialNoBuf,
			deviceInstanceBuf, &sizeOfDeviceInstanceBuf,
			&usLedInfoFlag, &usTotalNumLeds,
			deviceFriendlyNameBuf, &sizeOfDeviceFriendlyNameBuf, dwFlag);

		if (currIdx == 0xFFFFFFFF)
			break;

		if (!SUCCEEDED(hr))
		{
			currIdx = 0xFFFFFFFF;
			continue;
		}
		else
		{
			EnumeratedDevice dev;
			dev.vid = usVendorID;
			dev.pid = usProductID;
			dev.ledInfoFlag = usLedInfoFlag;
			dev.totalNumLeds = usTotalNumLeds;
			dev.serialNo = gcnew String(serialNoBuf);
			dev.deviceInstance = gcnew String(deviceInstanceBuf);
			dev.friendlyName = gcnew String(deviceFriendlyNameBuf);
			tempList->Add(dev);
			currIdx++;
		}
	}

	return tempList->ToArray();
}
