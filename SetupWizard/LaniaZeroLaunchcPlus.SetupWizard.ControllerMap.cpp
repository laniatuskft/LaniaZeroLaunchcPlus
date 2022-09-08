#include "LaniaZeroLaunchcPlus.SetupWizard.ControllerMap.h"

using namespace SharpDX::DirectInput;

namespace LaniaZeroLaunchcPlus::SetupWizard
{

	ControllerMap::ControllerMap()
	{
		InitializeComponent();
		dInput = new DirectInput();
	}

	void ControllerMap::UserControl_Loaded(std::any sender, RoutedEventArgs *e)
	{
		mainWindow = dynamic_cast<MainWindow_new*>(Window::GetWindow(this));
		mainWindow->buttonNext->IsEnabled = true;
		controllerList();
	}

	void ControllerMap::controllerList()
	{
		for (auto device : *dInput->GetDevices(DeviceType::Gamepad, DeviceEnumerationFlags::AttachedOnly))
		{
			controllers.push_back(device);
			listBoxDevices::Items->Add(device->ProductName);
		}
		for (auto device : *dInput->GetDevices(DeviceType::Joystick, DeviceEnumerationFlags::AttachedOnly))
		{
			controllers.push_back(device);
			listBoxDevices::Items->Add(device->ProductName);
		}
		for (auto device : *dInput->GetDevices(DeviceType::Driving, DeviceEnumerationFlags::AttachedOnly))
		{
			controllers.push_back(device);
			listBoxDevices::Items->Add(device->ProductName);
		}
		for (auto device : *dInput->GetDevices(DeviceType::Flight, DeviceEnumerationFlags::AttachedOnly))
		{
			controllers.push_back(device);
			listBoxDevices::Items->Add(device->ProductName);
		}
		for (auto device : *dInput->GetDevices(DeviceType::FirstPerson, DeviceEnumerationFlags::AttachedOnly))
		{
			controllers.push_back(device);
			listBoxDevices::Items->Add(device->ProductName);
		}
	}

	void ControllerMap::listBoxDevices_SelectionChanged(std::any sender, SelectionChangedEventArgs *e)
	{
		mainWindow->newConfig->setDevName(controllers[listBoxDevices::SelectedIndex]->ProductName);
	}
}
