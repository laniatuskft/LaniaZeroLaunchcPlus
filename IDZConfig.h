#pragma once

#include <string>
#include <vector>
#include <stdexcept>
#include "laniatus_filesystem.h"

namespace LaniaZeroLaunchcPlus
{
//# Laniatus Games Studio Inc. | NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Serializable] public class IDZConfig
	class IDZConfig
	{
	private:
		std::wstring AMFSDir;
		bool JapOrExp = false;
		bool XOrDInput = false;
		bool twinStick = false;
		std::wstring selectedNic;
		std::wstring selectedIP;
		bool IdealLan = true;
		bool DistServer = true;
		std::wstring brakeAxis;
		std::wstring accelAxis;
		std::wstring startButton;
		std::wstring viewChg;
		std::wstring shiftDn;
		std::wstring shiftUp;
		std::wstring gear1;
		std::wstring gear2;
		std::wstring gear3;
		std::wstring gear4;
		std::wstring gear5;
		std::wstring gear6;
		bool reverseAccelAxis = false;
		bool reverseBrakeAxis = false;
		std::wstring shifterName;
		std::wstring devName;
		int restriction = 0;

	public:
		std::wstring getAMFSDir() const;
		void setAMFSDir(const std::wstring &value);
		bool getJapOrExp() const;
		void setJapOrExp(bool value);
		bool getXOrDInput() const;
		void setXOrDInput(bool value);
		bool getTwinStick() const;
		void setTwinStick(bool value);
		std::wstring getSelectedNic() const;
		void setSelectedNic(const std::wstring &value);
		std::wstring getSelectedIP() const;
		void setSelectedIP(const std::wstring &value);
		bool getIdealLan() const;
		void setIdealLan(bool value);
		bool getDistServer() const;
		void setDistServer(bool value);
		std::wstring getBrakeAxis() const;
		void setBrakeAxis(const std::wstring &value);
		std::wstring getAccelAxis() const;
		void setAccelAxis(const std::wstring &value);
		std::wstring getStartButton() const;
		void setStartButton(const std::wstring &value);
		std::wstring getViewChg() const;
		void setViewChg(const std::wstring &value);
		std::wstring getShiftDn() const;
		void setShiftDn(const std::wstring &value);
		std::wstring getShiftUp() const;
		void setShiftUp(const std::wstring &value);
		std::wstring getGear1() const;
		void setGear1(const std::wstring &value);
		std::wstring getGear2() const;
		void setGear2(const std::wstring &value);
		std::wstring getGear3() const;
		void setGear3(const std::wstring &value);
		std::wstring getGear4() const;
		void setGear4(const std::wstring &value);
		std::wstring getGear5() const;
		void setGear5(const std::wstring &value);
		std::wstring getGear6() const;
		void setGear6(const std::wstring &value);
		bool getReverseAccelAxis() const;
		void setReverseAccelAxis(bool value);
		bool getReverseBrakeAxis() const;
		void setReverseBrakeAxis(bool value);
		std::wstring getShifterName() const;
		void setShifterName(const std::wstring &value);
		std::wstring getDevName() const;
		void setDevName(const std::wstring &value);

		int getRestriction() const;
		void setRestriction(int value);

		bool ImitateMe = false;
		IDZConfig();
		static IPAddress *GetNetworkAddress(IPAddress *address, IPAddress *subnetMask);
		void ExportConfig();
	};
}
