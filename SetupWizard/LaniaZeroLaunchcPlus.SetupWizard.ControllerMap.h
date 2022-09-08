#pragma once

#include "../LaniaZeroLaunchcPlus.MainWindow_new.h"
#include <vector>
#include <any>

//# Laniatus Games Studio Inc. | NOTE: Forward class declarations:
namespace SharpDX::DirectInput { class DeviceInstance; }
namespace SharpDX::DirectInput { class DirectInput; }

using namespace SharpDX::DirectInput;

namespace LaniaZeroLaunchcPlus::SetupWizard
{
	/// <summary>
	/// Interaction logic for ControllerMap.xaml
	/// </summary>
	class ControllerMap : public UserControl
	{
	private:
		std::vector<DeviceInstance*> controllers = std::vector<DeviceInstance*>();
		DirectInput *dInput;
		MainWindow_new *mainWindow;
	public:
		virtual ~ControllerMap()
		{
			delete dInput;
			delete mainWindow;
		}

		ControllerMap();

	private:
		void UserControl_Loaded(std::any sender, RoutedEventArgs *e);

		void controllerList();

		void listBoxDevices_SelectionChanged(std::any sender, SelectionChangedEventArgs *e);
	};
}
