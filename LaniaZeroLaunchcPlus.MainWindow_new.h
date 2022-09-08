#pragma once

#include "IDZConfig.h"
#include <any>

using namespace LaniaZeroLaunchcPlus::SetupWizard;

namespace LaniaZeroLaunchcPlus
{
	/// <summary>
	/// Interaction logic for MainWindow_new.xaml
	/// </summary>
	class MainWindow_new : public Window
	{
	private:
		int curControl = 0;
	public:
		IDZConfig *newConfig = new IDZConfig();
		bool redistsComplete = false;
		virtual ~MainWindow_new()
		{
			delete newConfig;
		}

		MainWindow_new();

	private:
		void buttonNext_Click(std::any sender, RoutedEventArgs *e);

		void buttonPrev_Click(std::any sender, RoutedEventArgs *e);

	public:
		void nextUC();

	private:
		void changeControl();
	};
}
