#pragma once

#include "../LaniaZeroLaunchcPlus.MainWindow_new.h"
#include <any>

namespace LaniaZeroLaunchcPlus::SetupWizard
{
	/// <summary>
	/// Interaction logic for Controller.xaml
	/// </summary>
	class Controller : public UserControl
	{
	private:
		MainWindow_new *mainWindow;
	public:
		virtual ~Controller()
		{
			delete mainWindow;
		}

		Controller();

	private:
		void Button_Click(std::any sender, RoutedEventArgs *e);

		void UserControl_Loaded(std::any sender, RoutedEventArgs *e);

		void buttonDinput_Click(std::any sender, RoutedEventArgs *e);
	};
}
