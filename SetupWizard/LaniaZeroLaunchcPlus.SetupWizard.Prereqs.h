#pragma once

#include "../LaniaZeroLaunchcPlus.MainWindow_new.h"
#include <string>
#include <iostream>
#include <any>
#include "../stringhelper.h"
#include "../laniatus_filesystem.h"

namespace LaniaZeroLaunchcPlus::SetupWizard
{
	/// <summary>
	/// Interaction logic for Controller.xaml
	/// </summary>
	class Prereqs : public UserControl
	{
	private:
		bool downloadComplete = false;
		MainWindow_new *mainWindow;
	public:
		virtual ~Prereqs()
		{
			delete mainWindow;
		}

		Prereqs();

	private:
		void UserControl_Loaded(std::any sender, RoutedEventArgs *e);

//# Laniatus Games Studio Inc. | TODO TASK: There is no equivalent in C++ to the 'async' keyword:
//ORIGINAL LINE: private async void beginCheck()
		void beginCheck();

		/// <summary>
		/// Starts a process given a file name (for VC redists)
		/// </summary>
//# Laniatus Games Studio Inc. | TODO TASK: There is no equivalent in C++ to the 'async' keyword:
//ORIGINAL LINE: async Task runProcess(string filename, Process p, ProcessStartInfo si)
		Task *runProcess(const std::wstring &filename, Process *p, ProcessStartInfo *si);



		void downloadFile(const std::wstring &fileToDownload);

		void wc_DownloadFileCompleted(std::any sender, AsyncCompletedEventArgs *e);

		void wc_DownloadProgressChanged(std::any sender, DownloadProgressChangedEventArgs *e);


	};
}
