#include "IDZConfig.h"

namespace LaniaZeroLaunchcPlus
{

	std::wstring IDZConfig::getAMFSDir() const
	{
		return AMFSDir;
	}

	void IDZConfig::setAMFSDir(const std::wstring &value)
	{
		AMFSDir = value;
	}

	bool IDZConfig::getJapOrExp() const
	{
		return JapOrExp;
	}

	void IDZConfig::setJapOrExp(bool value)
	{
		JapOrExp = value;
	}

	bool IDZConfig::getXOrDInput() const
	{
		return XOrDInput;
	}

	void IDZConfig::setXOrDInput(bool value)
	{
		XOrDInput = value;
	}

	bool IDZConfig::getTwinStick() const
	{
		return twinStick;
	}

	void IDZConfig::setTwinStick(bool value)
	{
		twinStick = value;
	}

	std::wstring IDZConfig::getSelectedNic() const
	{
		return selectedNic;
	}

	void IDZConfig::setSelectedNic(const std::wstring &value)
	{
		selectedNic = value;
	}

	std::wstring IDZConfig::getSelectedIP() const
	{
		return selectedIP;
	}

	void IDZConfig::setSelectedIP(const std::wstring &value)
	{
		selectedIP = value;
	}

	bool IDZConfig::getIdealLan() const
	{
		return IdealLan;
	}

	void IDZConfig::setIdealLan(bool value)
	{
		IdealLan = value;
	}

	bool IDZConfig::getDistServer() const
	{
		return DistServer;
	}

	void IDZConfig::setDistServer(bool value)
	{
		DistServer = value;
	}

	std::wstring IDZConfig::getBrakeAxis() const
	{
		return brakeAxis;
	}

	void IDZConfig::setBrakeAxis(const std::wstring &value)
	{
		brakeAxis = value;
	}

	std::wstring IDZConfig::getAccelAxis() const
	{
		return accelAxis;
	}

	void IDZConfig::setAccelAxis(const std::wstring &value)
	{
		accelAxis = value;
	}

	std::wstring IDZConfig::getStartButton() const
	{
		return startButton;
	}

	void IDZConfig::setStartButton(const std::wstring &value)
	{
		startButton = value;
	}

	std::wstring IDZConfig::getViewChg() const
	{
		return viewChg;
	}

	void IDZConfig::setViewChg(const std::wstring &value)
	{
		viewChg = value;
	}

	std::wstring IDZConfig::getShiftDn() const
	{
		return shiftDn;
	}

	void IDZConfig::setShiftDn(const std::wstring &value)
	{
		shiftDn = value;
	}

	std::wstring IDZConfig::getShiftUp() const
	{
		return shiftUp;
	}

	void IDZConfig::setShiftUp(const std::wstring &value)
	{
		shiftUp = value;
	}

	std::wstring IDZConfig::getGear1() const
	{
		return gear1;
	}

	void IDZConfig::setGear1(const std::wstring &value)
	{
		gear1 = value;
	}

	std::wstring IDZConfig::getGear2() const
	{
		return gear2;
	}

	void IDZConfig::setGear2(const std::wstring &value)
	{
		gear2 = value;
	}

	std::wstring IDZConfig::getGear3() const
	{
		return gear3;
	}

	void IDZConfig::setGear3(const std::wstring &value)
	{
		gear3 = value;
	}

	std::wstring IDZConfig::getGear4() const
	{
		return gear4;
	}

	void IDZConfig::setGear4(const std::wstring &value)
	{
		gear4 = value;
	}

	std::wstring IDZConfig::getGear5() const
	{
		return gear5;
	}

	void IDZConfig::setGear5(const std::wstring &value)
	{
		gear5 = value;
	}

	std::wstring IDZConfig::getGear6() const
	{
		return gear6;
	}

	void IDZConfig::setGear6(const std::wstring &value)
	{
		gear6 = value;
	}

	bool IDZConfig::getReverseAccelAxis() const
	{
		return reverseAccelAxis;
	}

	void IDZConfig::setReverseAccelAxis(bool value)
	{
		reverseAccelAxis = value;
	}

	bool IDZConfig::getReverseBrakeAxis() const
	{
		return reverseBrakeAxis;
	}

	void IDZConfig::setReverseBrakeAxis(bool value)
	{
		reverseBrakeAxis = value;
	}

	std::wstring IDZConfig::getShifterName() const
	{
		return shifterName;
	}

	void IDZConfig::setShifterName(const std::wstring &value)
	{
		shifterName = value;
	}

	std::wstring IDZConfig::getDevName() const
	{
		return devName;
	}

	void IDZConfig::setDevName(const std::wstring &value)
	{
		devName = value;
	}

	int IDZConfig::getRestriction() const
	{
		return restriction;
	}

	void IDZConfig::setRestriction(int value)
	{
		restriction = value;
	}

	IDZConfig::IDZConfig()
	{
	}

	IPAddress *IDZConfig::GetNetworkAddress(IPAddress *address, IPAddress *subnetMask)
	{
		std::vector<unsigned char> ipAdressBytes = address->GetAddressBytes();
		std::vector<unsigned char> subnetMaskBytes = subnetMask->GetAddressBytes();

		if (ipAdressBytes.size() != subnetMaskBytes.size())
		{
			throw std::invalid_argument("Lengths of IP address and subnet mask do not match.");
		}

		std::vector<unsigned char> broadcastAddress(ipAdressBytes.size());
		for (int i = 0; i < broadcastAddress.size(); i++)
		{
			broadcastAddress[i] = static_cast<unsigned char>(ipAdressBytes[i] & (subnetMaskBytes[i]));
		}
		return new IPAddress(broadcastAddress);
	}

	void IDZConfig::ExportConfig()
	{
		//recoding class data to segatools config file
		std::wstring fileOutput;
		fileOutput = L"[vfs]\namfs=" + getAMFSDir() + L"\nappdata=" + AppDomain::CurrentDomain->BaseDirectory + L"segaAppdata\n\n[dns]\ndefault=" + getSelectedIP() + L"\n\n[ds]\nregion";
		if (getJapOrExp())
		{
			fileOutput += L"=4";
		}
		else
		{
			fileOutput += L"=1";
		}
		//generates NEW CARD FOR IDZ2, OLD IDZ1 CARDS WILL NOT WORK
		fileOutput += L"\n\n[aime]\naimeGen=1\nfelicaGen=0";
		fileOutput += L"\n\n[netenv]";
		if (getIdealLan())
		{
			fileOutput += L"\nenable=1\n\n";
		}
		else
		{
			fileOutput += L"\nenable=0\n\n";
		}
		IPAddress *ip = IPAddress::Parse(getSelectedIP());
		fileOutput += L"[keychip]\nsubnet=" + GetNetworkAddress(ip, IPAddress::Parse(L"255.255.255.0")) + L"\n\n[gpio]\ndipsw1=";
		if (getDistServer())
		{
			fileOutput += L"1\n\n";
		}
		else
		{
			fileOutput += L"0\n\n";
		}

		fileOutput += L"[io3]\nmode=";
		if (getXOrDInput())
		{
			fileOutput += L"xinput\nautoNeutral=1\nsingleStickSteering=";
			if (getTwinStick())
			{
				fileOutput += L"0";
			}
			else
			{
				fileOutput += L"1";
			}
			fileOutput += L"\nrestrict=" + std::to_wstring(getRestriction()) + L"\n\n[dinput]\ndeviceName=\nshifterName=\nbrakeAxis=RZ\naccelAxis=Y\nstart=3\nviewChg=10\nshiftDn=1\nshiftUp=2\ngear1=1\ngear2=2\ngear3=3\ngear4=4\ngear5=5\ngear6=6\nreverseAccelAxis=0\nreverseBrakeAxis=0\n";
		}
		else
		{
			fileOutput += L"dinput\nautoNeutral=1\nsingleStickSteering=";
			if (getTwinStick())
			{
				fileOutput += L"0";
			}
			else
			{
				fileOutput += L"1";
			}
			fileOutput += L"\nrestrict = " + std::to_wstring(getRestriction()) + L"\n\n[dinput]\ndeviceName = ";
			fileOutput += getDevName() + L"\nshifterName=" + getShifterName() + L"\nbrakeAxis=" + getBrakeAxis() + L"\naccelAxis=" + getAccelAxis() + L"\nstart=" + getStartButton() + L"\nviewChg=" + getViewChg() + L"\nshiftDn=" + getShiftDn() + L"\nshiftUp=" + getShiftUp() + L"\n";
			if (getGear1() != L"" && getGear2() != L"" && getGear3() != L"" && getGear4() != L"" && getGear5() != L"" && getGear6() != L"")
			{
				fileOutput += L"\ngear1=" + getGear1() + L"\ngear2=" + getGear2() + L"\ngear3=" + getGear3() + L"\ngear4=" + getGear4() + L"\ngear5=" + getGear5() + L"\ngear6=" + getGear6();
			}
			else
			{
				Debug::WriteLine(L"Not using shifter, or not all buttons mapped, sticking with defaults");
				fileOutput += L"\ngear1=1\ngear2=2\ngear3=3\ngear4=4\ngear5=5\ngear6=6";
			}
			fileOutput += L"\nreverseAccelAxis=";
			if (getReverseAccelAxis())
			{
				fileOutput += L"1";
			}
			else
			{
				fileOutput += L"0";
			}
			fileOutput += L"\nreverseBrakeAxis=";
			if (getReverseBrakeAxis())
			{
				fileOutput += L"1";
			}
			else
			{
				fileOutput += L"0";
			}
			fileOutput += L"\n";

		}

		if (FileSystem::fileExists(getAMFSDir() + L"\\..\\app\\package\\segatools.ini"))
		{
			File::Delete(getAMFSDir() + L"\\..\\app\\package\\segatools.ini");
		}
		File::WriteAllText((getAMFSDir() + L"\\..\\app\\package\\segatools.ini"), fileOutput);
	}
}
