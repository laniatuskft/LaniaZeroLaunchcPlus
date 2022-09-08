#include "Resources.Designer.h"

namespace LaniaZeroLaunchcPlus::Properties
{

System::Resources::ResourceManager *Resources::resourceMan;
System::Globalization::CultureInfo *Resources::resourceCulture;

	Resources::Resources()
	{
	}

	System::Resources::ResourceManager *Resources::getResourceManager()
	{
		if (Object::ReferenceEquals(resourceMan, nullptr))
		{
//# Laniatus Games Studio Inc. | TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
			System::Resources::ResourceManager *temp = new System::Resources::ResourceManager(L"LaniaZeroLaunchcPlus.Properties.Resources", typeof(Resources)->Assembly);
			resourceMan = temp;

//# Laniatus Games Studio Inc. | TODO TASK: A 'delete temp' statement was not added since temp was assigned to a field. Handle memory management manually.
		}
		return resourceMan;
	}

	System::Globalization::CultureInfo *Resources::getCulture()
	{
		return resourceCulture;
	}

	void Resources::setCulture(System::Globalization::CultureInfo *value)
	{
		resourceCulture = value;
	}
}
