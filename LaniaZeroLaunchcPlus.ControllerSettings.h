#pragma once

#include "IDZConfig.h"
#include <string>
#include <vector>
#include <any>
#include "stringhelper.h"

//# Laniatus Games Studio Inc. | NOTE: Forward class declarations:
namespace SharpDX::DirectInput { class DirectInput; }
namespace SharpDX::DirectInput { class Joystick; }

using namespace SharpDX::DirectInput;

namespace LaniaZeroLaunchcPlus
{
	/// <summary>
	/// Interaction logic for ControllerSettings.xaml
	/// </summary>
	class ControllerSettings : public Window
	{
	private:
		bool _isXinput = false;
		IDZConfig *_gameProfile;
		DirectInput *dInput;
		static TextBox *selTextBox;
		Joystick *_joystick;
		bool _listen = false;
		Thread *thControl;
		//private static Thread _inputListener;
	public:
		virtual ~ControllerSettings()
		{
			delete _gameProfile;
			delete dInput;
			delete _joystick;
			delete thControl;
		}

		ControllerSettings(IDZConfig *gameProfile, bool isXinput);

	private:
		void PollPad();

		void Window_Loaded(std::any sender, RoutedEventArgs *e);

		void TextBox_PreviewMouseDown_1(std::any sender, MouseButtonEventArgs *e);
		std::vector<TextBox*> GetAllTextBox();
		void StackPanel_Unloaded(std::any sender, RoutedEventArgs *e);
		void updateTextBoxes();
		void Window_Closing(std::any sender, System::ComponentModel::CancelEventArgs *e);

		void Window_ContentRendered(std::any sender, EventArgs *e);
	};
}
