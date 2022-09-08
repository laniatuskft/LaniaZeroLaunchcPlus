#include "LaniaZeroLaunchcPlus.ControllerSettings.h"
#include "LaniaZeroLaunchcPlus.MainWindow.h"

using namespace SharpDX::DirectInput;

namespace LaniaZeroLaunchcPlus
{

TextBox *ControllerSettings::selTextBox = new TextBox();

	ControllerSettings::ControllerSettings(IDZConfig *gameProfile, bool isXinput)
	{
		InitializeComponent();
		_gameProfile = gameProfile;
		_isXinput = isXinput;
		if (_isXinput)
		{
			MessageBox::Show(L"Whoops, somehow you've ended up here with XInput selected. Gonna close this now. XINPUT MAPPING COMING SOME TIME IN 2021!");
			this->Close();
		}

		if (_joystick != nullptr)
		{
			_joystick->Dispose();
		}
		dInput = new DirectInput();
		auto joystickGuid = Guid::Empty;
		for (auto device : *dInput->GetDevices(DeviceType::Joystick, DeviceEnumerationFlags::AttachedOnly))
		{
			joystickGuid = device->InstanceGuid;
			break;
		}
		for (auto device : *dInput->GetDevices(DeviceType::Driving, DeviceEnumerationFlags::AttachedOnly))
		{
			joystickGuid = device->InstanceGuid;
			break;
		}
		for (auto device : *dInput->GetDevices(DeviceType::Gamepad, DeviceEnumerationFlags::AttachedOnly))
		{
			joystickGuid = device->InstanceGuid;
			break;
		}
		for (auto device : *dInput->GetDevices(DeviceType::FirstPerson, DeviceEnumerationFlags::AttachedOnly))
		{
			joystickGuid = device->InstanceGuid;
			break;
		}
		if (joystickGuid == Guid::Empty)
		{
			MessageBox::Show(L"No DirectInput joystick connected");
			return;
		}

		_joystick = new Joystick(dInput, joystickGuid);
		_joystick->Properties->BufferSize = 512;
		_joystick->Acquire();
	}

	void ControllerSettings::PollPad()
	{
		while (!_listen)
		{
			_joystick->Poll();
			auto datas = _joystick->GetBufferedData();
			for (auto state : datas)
			{
				//better check for POV thing
//# Laniatus Games Studio Inc. | TODO TASK: There is no C++ equivalent to 'ToString':
				if (state->Offset.ToString().Contains(L"PointOfViewControllers"))
				{
//# Laniatus Games Studio Inc. | TODO TASK: There is no C++ equivalent to 'ToString':
					MessageBox::Show(L"Whoops, you've tried to map the D-Pad of your Wheel/Controller to a button.\n\nThis is mapped to the IDZ cabinet's arrow keys already.", state->Offset.ToString() + L" is not a valid input!");
				}
				else
				{
//# Laniatus Games Studio Inc. | TODO TASK: There is no C++ equivalent to 'ToString':
					if (state->Offset.ToString() == L"X" || state->Offset.ToString() == L"Y" || state->Offset.ToString() == L"Z")
					{
						this->Dispatcher->Invoke([&] ()
						{
							try
							{
								selTextBox->Text = state->Offset.ToString() + L" Axis";
							}
							catch (...)
							{
							}
						});
					}
					else
					{
//# Laniatus Games Studio Inc. | TODO TASK: There is no C++ equivalent to 'ToString':
						if (state->Offset.ToString().Contains(L"Buttons"))
						{
							/* FUCKING SHARPDX
							 * Lemme tell you why this is here.
							 * SharpDX for some fucking reason maps the buttons like "Button 1" on your DInput gamepad is called "Buttons0"
							 * segatools however uses the numbers that you see in controller settings, that start at 1.
							 * hence i need to increase the number.
							 */

//# Laniatus Games Studio Inc. | TODO TASK: There is no C++ equivalent to 'ToString':
							std::wstring lemmefix = state->Offset.ToString().Replace(L"Buttons", L"");
							int buttonNo = std::stoi(lemmefix);
							buttonNo++;
							lemmefix = L"Buttons" + std::to_wstring(buttonNo);
							this->Dispatcher->Invoke([&] ()
							{
								try
								{
									selTextBox->Text = lemmefix;
								}
								catch (...)
								{
								}
							});
						}
//# Laniatus Games Studio Inc. | TODO TASK: There is no C++ equivalent to 'ToString':
						else if (state->Offset.ToString().Contains(L"Sliders"))
						{
							/* FUCKING SHARPDX
							 * Lemme tell you why this is here.
							 * SharpDX for some fucking reason maps the buttons like "Button 1" on your DInput gamepad is called "Buttons0"
							 * segatools however uses the numbers that you see in controller settings, that start at 1.
							 * hence i need to increase the number.
							 */

//# Laniatus Games Studio Inc. | TODO TASK: There is no C++ equivalent to 'ToString':
							std::wstring lemmefix = state->Offset.ToString().Replace(L"Sliders", L"");
							int buttonNo = std::stoi(lemmefix);
							buttonNo++;
							lemmefix = L"Sliders" + std::to_wstring(buttonNo);
							this->Dispatcher->Invoke([&] ()
							{
								try
								{
									selTextBox->Text = lemmefix;
								}
								catch (...)
								{
								}
							});
						}
						else
						{
							this->Dispatcher->Invoke([&] ()
							{
								try
								{
									selTextBox->Text = state->Offset.ToString();
								}
								catch (...)
								{
								}
							});
						}
					}
				}
			}
		}
	}

	void ControllerSettings::Window_Loaded(std::any sender, RoutedEventArgs *e)
	{

	}

	void ControllerSettings::TextBox_PreviewMouseDown_1(std::any sender, MouseButtonEventArgs *e)
	{
		selTextBox = (dynamic_cast<TextBox*>(sender));
	}

	std::vector<TextBox*> ControllerSettings::GetAllTextBox()
	{
		std::vector<TextBox*> textBoxes;
		/// casting the content into panel
		Panel *mainContainer = std::any_cast<Panel*>(this->Content);

		/// GetAll UIElement
		UIElementCollection *element = mainContainer->Children;

		StackPanel *controls = static_cast<StackPanel*>(element[0]);

		UIElementCollection *element2 = controls->Children;

		/// casting the UIElementCollection into List
		std::vector<FrameworkElement*> lstElement = element2->Cast<FrameworkElement*>().ToList();

		/// Geting all Control from list
		auto lstControl = lstElement.OfType<Control*>();

		for (auto control : *lstControl)
		{
			if (dynamic_cast<TextBox*>(control) != nullptr)
			{
				textBoxes.push_back(static_cast<TextBox*>(control));
			}
		}
		return textBoxes;
	}

	void ControllerSettings::StackPanel_Unloaded(std::any sender, RoutedEventArgs *e)
	{

	}

	void ControllerSettings::updateTextBoxes()
	{
		std::vector<TextBox*> controls = GetAllTextBox();
		try
		{
			if (_gameProfile->getBrakeAxis() != L"")
			{
				//time to check if Rotation is used
				if (_gameProfile->getBrakeAxis().find(L"R") != std::wstring::npos)
				{
					controls[0]->Text = StringHelper::replace(_gameProfile->getBrakeAxis(), L"R", L"Rotation");
				}
				else if (_gameProfile->getBrakeAxis().find(L"U") != std::wstring::npos)
				{
					controls[0]->Text = StringHelper::replace(_gameProfile->getBrakeAxis(), L"U", L"Sliders1");
				}
				else if (_gameProfile->getBrakeAxis().find(L"V") != std::wstring::npos)
				{
					controls[0]->Text = StringHelper::replace(_gameProfile->getBrakeAxis(), L"V", L"Sliders2");
				}
				else
				{
					controls[0]->Text = _gameProfile->getBrakeAxis() + L" Axis";
				}
			}
			if (_gameProfile->getAccelAxis() != L"")
			{
				if (_gameProfile->getAccelAxis().find(L"R") != std::wstring::npos)
				{
					controls[1]->Text = StringHelper::replace(_gameProfile->getAccelAxis(), L"R", L"Rotation");
				}
				else if (_gameProfile->getAccelAxis().find(L"U") != std::wstring::npos)
				{
					controls[0]->Text = StringHelper::replace(_gameProfile->getAccelAxis(), L"U", L"Sliders1");
				}
				else if (_gameProfile->getAccelAxis().find(L"V") != std::wstring::npos)
				{
					controls[0]->Text = StringHelper::replace(_gameProfile->getAccelAxis(), L"V", L"Sliders2");
				}
				else
				{
					controls[1]->Text = _gameProfile->getAccelAxis() + L" Axis";
				}
			}

			controls[2]->Text = L"Buttons" + _gameProfile->getStartButton();
			controls[3]->Text = L"Buttons" + _gameProfile->getViewChg();
			controls[4]->Text = L"Buttons" + _gameProfile->getShiftDn();
			controls[5]->Text = L"Buttons" + _gameProfile->getShiftUp();
			controls[6]->Text = L"Buttons" + _gameProfile->getGear1();
			controls[7]->Text = L"Buttons" + _gameProfile->getGear2();
			controls[8]->Text = L"Buttons" + _gameProfile->getGear3();
			controls[9]->Text = L"Buttons" + _gameProfile->getGear4();
			controls[10]->Text = L"Buttons" + _gameProfile->getGear5();
			controls[11]->Text = L"Buttons" + _gameProfile->getGear6();
			reverseAccAxis->IsChecked = _gameProfile->getReverseAccelAxis();
			reverseBrakeAxis->IsChecked = _gameProfile->getReverseBrakeAxis();
			textBoxDevice->Text = _gameProfile->getDevName();
			textBoxShifter->Text = _gameProfile->getShifterName();
		}
		catch (...)
		{

		}
	}

	void ControllerSettings::Window_Closing(std::any sender, System::ComponentModel::CancelEventArgs *e)
	{
		std::vector<TextBox*> controls = GetAllTextBox();

		if (controls[0]->Text == L"Sliders1")
		{
			controls[0]->Text = StringHelper::replace(controls[0]->Text, L"Sliders1", L"U");
		}
		if (controls[1]->Text.find(L"Sliders1") != std::wstring::npos)
		{
			controls[1]->Text = StringHelper::replace(controls[1]->Text, L"Sliders1", L"U");
		}

		if (controls[0]->Text == L"Sliders2")
		{
			controls[0]->Text = StringHelper::replace(controls[0]->Text, L"Sliders2", L"V");
		}
		if (controls[1]->Text.find(L"Sliders2") != std::wstring::npos)
		{
			controls[1]->Text = StringHelper::replace(controls[1]->Text, L"Sliders2", L"V");
		}


		//time to check if Rotation is used
		if (controls[0]->Text.find(L"Rotation") != std::wstring::npos)
		{
			controls[0]->Text = StringHelper::replace(controls[0]->Text, L"Rotation", L"R");
		}
		if (controls[1]->Text.find(L"Rotation") != std::wstring::npos)
		{
			controls[1]->Text = StringHelper::replace(controls[1]->Text, L"Rotation", L"R");
		}

		if (controls[0]->Text.find(L" Axis") != std::wstring::npos)
		{
			controls[0]->Text = StringHelper::replace(controls[0]->Text, L" Axis", L"");
		}
		if (controls[1]->Text.find(L" Axis") != std::wstring::npos)
		{
			controls[1]->Text = StringHelper::replace(controls[1]->Text, L" Axis", L"");
		}

		//transfer settings to IDZConfig
		_gameProfile->setBrakeAxis(controls[0]->Text);
		_gameProfile->setAccelAxis(controls[1]->Text);
		_gameProfile->setStartButton(StringHelper::replace(controls[2]->Text, L"Buttons", L""));
		_gameProfile->setViewChg(StringHelper::replace(controls[3]->Text, L"Buttons", L""));
		_gameProfile->setShiftDn(StringHelper::replace(controls[4]->Text, L"Buttons", L""));
		_gameProfile->setShiftUp(StringHelper::replace(controls[5]->Text, L"Buttons", L""));
		_gameProfile->setGear1(StringHelper::replace(controls[6]->Text, L"Buttons", L""));
		_gameProfile->setGear2(StringHelper::replace(controls[7]->Text, L"Buttons", L""));
		_gameProfile->setGear3(StringHelper::replace(controls[8]->Text, L"Buttons", L""));
		_gameProfile->setGear4(StringHelper::replace(controls[9]->Text, L"Buttons", L""));
		_gameProfile->setGear5(StringHelper::replace(controls[10]->Text, L"Buttons", L""));
		_gameProfile->setGear6(StringHelper::replace(controls[11]->Text, L"Buttons", L""));
		_gameProfile->setReverseAccelAxis(static_cast<bool>(reverseAccAxis::IsChecked));
		_gameProfile->setReverseBrakeAxis(static_cast<bool>(reverseBrakeAxis::IsChecked));
		_gameProfile->setDevName(textBoxDevice->Text);
		_gameProfile->setShifterName(textBoxShifter->Text);

		MainWindow::gameConfig = _gameProfile;

		_listen = false;
		_joystick->Unacquire();
		thControl->Abort();
	}

	void ControllerSettings::Window_ContentRendered(std::any sender, EventArgs *e)
	{
		updateTextBoxes();
		ThreadStart thsControl = new ThreadStart([&] ()
		{
			PollPad();
		});
		thControl = new Thread(thsControl);
		thControl->Start();
	}
}
