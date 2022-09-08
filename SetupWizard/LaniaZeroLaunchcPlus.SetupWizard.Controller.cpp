#include "LaniaZeroLaunchcPlus.SetupWizard.Controller.h"

namespace LaniaZeroLaunchcPlus::SetupWizard
{

	Controller::Controller()
	{
		InitializeComponent();

	}

	void Controller::Button_Click(std::any sender, RoutedEventArgs *e)
	{
		//Xinput
		mainWindow->newConfig->setXOrDInput(true);
		mainWindow->nextUC();
	}

	void Controller::UserControl_Loaded(std::any sender, RoutedEventArgs *e)
	{
		mainWindow = dynamic_cast<MainWindow_new*>(Window::GetWindow(this));
		mainWindow->buttonNext->IsEnabled = false;
	}

	void Controller::buttonDinput_Click(std::any sender, RoutedEventArgs *e)
	{
		//Dinput
		mainWindow->newConfig->setXOrDInput(false);
		mainWindow->nextUC();
	}
}
