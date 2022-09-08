#include "LaniaZeroLaunchcPlus.MainWindow_new.h"
#include "SetupWizard/LaniaZeroLaunchcPlus.SetupWizard.Intro.h"
#include "SetupWizard/LaniaZeroLaunchcPlus.SetupWizard.Controller.h"
#include "SetupWizard/LaniaZeroLaunchcPlus.SetupWizard.ControllerMap.h"
#include "SetupWizard/LaniaZeroLaunchcPlus.SetupWizard.Prereqs.h"
#include "SetupWizard/LaniaZeroLaunchcPlus.SetupWizard.GameSetup.h"

using namespace LaniaZeroLaunchcPlus::SetupWizard;

namespace LaniaZeroLaunchcPlus
{

	MainWindow_new::MainWindow_new()
	{
		InitializeComponent();
		setupWizard->Content = new SetupWizard::Intro();
	}

	void MainWindow_new::buttonNext_Click(std::any sender, RoutedEventArgs *e)
	{
		if (newConfig->getXOrDInput() && curControl == 1)
		{
			//Skip Controller Selector
			curControl = 3;
		}
		else
		{
			curControl++;
		}
		changeControl();
	}

	void MainWindow_new::buttonPrev_Click(std::any sender, RoutedEventArgs *e)
	{
		if (newConfig->getXOrDInput() && curControl == 3)
		{
			//Skip Controller Selector
			curControl = 1;
		}
		else
		{
			curControl--;
		}
		changeControl();
	}

	void MainWindow_new::nextUC()
	{
		if (newConfig->getXOrDInput() && curControl == 1)
		{
			//Skip Controller Selector
			curControl = 3;
		}
		else
		{
			curControl++;
		}
		changeControl();
	}

	void MainWindow_new::changeControl()
	{
		switch (curControl)
		{
			case 0:
				setupWizard->Content = new SetupWizard::Intro();
				buttonPrev->IsEnabled = false;
				break;
			case 1:
				setupWizard->Content = new SetupWizard::Controller();
				buttonPrev->IsEnabled = true;
				break;
			case 2:
				setupWizard->Content = new SetupWizard::ControllerMap();
				break;
			case 3:
				setupWizard->Content = new SetupWizard::Prereqs();
				break;
			case 4:
				setupWizard->Content = new SetupWizard::GameSetup();
				break;
			default:
				this->Close();
				break;
		}
	}
}
