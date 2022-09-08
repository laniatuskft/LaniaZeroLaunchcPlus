#include "LaniaZeroLaunchcPlus.Properties.Settings.h"

namespace LaniaZeroLaunchcPlus::Properties
{

Settings *Settings::defaultInstance = (static_cast<Settings*>(System::Configuration::ApplicationSettingsBase::Synchronized(new Settings())));

	Settings *Settings::getDefault()
	{
		return defaultInstance;
	}
}
