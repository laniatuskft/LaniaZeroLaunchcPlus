#pragma once

#include "IDZConfig.h"
#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <any>
#include "laniatus_filesystem.h"

using namespace Microsoft::Win32;
using namespace WPFFolderBrowser;
using namespace AutoUpdaterDotNET;

namespace LaniaZeroLaunchcPlus
{
	/// <summary>
	/// Interaction logic for MainWindow.xaml
	/// </summary>
	class MainWindow : public Window
	{
	public:
		static bool Terminate;
		static bool consoleEnabled;
		static IDZConfig *gameConfig;
	private:
		std::vector<NetworkInterface*> networkAdapters = std::vector<NetworkInterface*>();
	public:
		MainWindow();

	private:
		void updateUI();

		/// <summary>
		/// Writes the given object instance to a binary file.
		/// <para>Object type (and all child types) must be decorated with the [Serializable] attribute.</para>
		/// <para>To prevent a variable from being serialized, decorate it with the [NonSerialized] attribute; cannot be applied to properties.</para>
		/// </summary>
		/// <typeparam name="T">The type of object being written to the binary file.</typeparam>
		/// <param name="filePath">The file path to write the object instance to.</param>
		/// <param name="objectToWrite">The object instance to write to the binary file.</param>
		/// <param name="append">If false the file will be overwritten if it already exists. If true the contents will be appended to the file.</param>
	public:
		template<typename T>
		static void WriteToBinaryFile(const std::wstring &filePath, T objectToWrite, bool append = false)
		{
//# Laniatus Games Studio Inc. | NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (Stream stream = File.Open(filePath, append ? FileMode.Append : FileMode.Create))
			{
				Stream stream = File::Open(filePath, append ? FileMode::Append : FileMode::Create);
				auto binaryFormatter = new System::Runtime::Serialization::Formatters::Binary::BinaryFormatter();
				binaryFormatter->Serialize(stream, objectToWrite);

				delete binaryFormatter;
			}
		}

		/// <summary>
		/// Reads an object instance from a binary file.
		/// </summary>
		/// <typeparam name="T">The type of object to read from the binary file.</typeparam>
		/// <param name="filePath">The file path to read the object instance from.</param>
		/// <returns>Returns a new instance of the object read from the binary file.</returns>
		template<typename T>
		static T ReadFromBinaryFile(const std::wstring &filePath)
		{
//# Laniatus Games Studio Inc. | NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (Stream stream = File.Open(filePath, FileMode.Open))
			{
				Stream stream = File::Open(filePath, FileMode::Open);
				auto binaryFormatter = new System::Runtime::Serialization::Formatters::Binary::BinaryFormatter();

				delete binaryFormatter;
				return std::any_cast<T>(binaryFormatter->Deserialize(stream));
			}
		}
	private:
		void RadioButton_Checked(std::any sender, RoutedEventArgs *e);

		void ComboBoxNetAdapter_SelectionChanged(std::any sender, SelectionChangedEventArgs *e);

		void configUpdate();
		void Window_Closing(std::any sender, System::ComponentModel::CancelEventArgs *e);

		void TextBoxGameAMFS_MouseDown(std::any sender, MouseButtonEventArgs *e);

		void TextBoxGameAMFS_PreviewMouseDown(std::any sender, MouseButtonEventArgs *e);

		void Button_Click(std::any sender, RoutedEventArgs *e);

//# Laniatus Games Studio Inc. | NOTE: The following .NET DllImport attribute was converted using the Microsoft-specific __declspec(dllimport):
//[DllImport("kernel32.dll", SetLastError = true)][return: MarshalAs(UnmanagedType::Bool)]
		__declspec(dllimport) static bool AllocConsole();
//# Laniatus Games Studio Inc. | NOTE: The following .NET DllImport attribute was converted using the Microsoft-specific __declspec(dllimport):
//[DllImport("kernel32.dll", SetLastError = true)][return: MarshalAs(UnmanagedType::Bool)]
		__declspec(dllimport) static bool FreeConsole();

		void bootAime();
		void bootAmdaemon();

		void bootIDZ();

//# Laniatus Games Studio Inc. | NOTE: The following .NET DllImport attribute was converted using the Microsoft-specific __declspec(dllimport):
//[DllImport("kernel32.dll")]
		__declspec(dllimport) static bool SetConsoleTitle(const std::wstring &lpConsoleTitle);

		void gameBoot();

		void flipTerm();
	public:
		void monitorGame(Thread *th, Thread *th2, Thread *th3);
		bool isNodeInstalled();

	private:
		void ButtonControls_Click(std::any sender, RoutedEventArgs *e);

		void Window_PreviewKeyDown(std::any sender, KeyEventArgs *e);

		void buttonClose_Click(std::any sender, RoutedEventArgs *e);

		void buttonDinput_Checked(std::any sender, RoutedEventArgs *e);

		void buttonXinput_Checked(std::any sender, RoutedEventArgs *e);

		void Window_ContentRendered(std::any sender, EventArgs *e);

		void Button_Click_1(std::any sender, RoutedEventArgs *e);

	};
}
