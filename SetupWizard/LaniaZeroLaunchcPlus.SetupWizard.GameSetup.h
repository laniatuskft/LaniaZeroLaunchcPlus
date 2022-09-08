#pragma once

#include "../LaniaZeroLaunchcPlus.MainWindow_new.h"
#include <string>
#include <vector>
#include <iostream>
#include <any>
#include "../stringhelper.h"
#include "../stringbuilder.h"
#include "../laniatus_filesystem.h"

using namespace Microsoft::Win32;

namespace LaniaZeroLaunchcPlus::SetupWizard
{
	/// <summary>
	/// Interaction logic for Intro.xaml
	/// </summary>
	class GameSetup : public UserControl
	{
	private:
		MainWindow_new *mainWindow;
	public:
		virtual ~GameSetup()
		{
			delete mainWindow;
		}

		GameSetup();

	private:
		void buttonBrowse_Click(std::any sender, RoutedEventArgs *e);

		std::wstring calcMd5(const std::wstring &filename);

		bool checkGameFiles(const std::wstring &filename);

		void UserControl_Loaded(std::any sender, RoutedEventArgs *e);
	};
}
