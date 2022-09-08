#pragma once

#include <string>

namespace LaniaZeroLaunchcPlus::SetupWizard
{
	/// <summary>
	/// Interaction logic for Intro.xaml
	/// </summary>
	class Intro : public UserControl
	{
	public:
		Intro();

		std::wstring nextControl = L"step1";
	};
}
