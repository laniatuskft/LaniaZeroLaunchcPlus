#include "LaniaZeroLaunchcPlus.SetupWizard.GameSetup.h"

using namespace Microsoft::Win32;

namespace LaniaZeroLaunchcPlus::SetupWizard
{

	GameSetup::GameSetup()
	{
		InitializeComponent();
	}

	void GameSetup::buttonBrowse_Click(std::any sender, RoutedEventArgs *e)
	{
		bool check = false;
		OpenFileDialog *openFileDialog = new OpenFileDialog();
		openFileDialog->Filter = L"InitialD0_DX11_Nu.exe|InitialD0_DX11_Nu.exe";
		if (openFileDialog->ShowDialog() == true)
		{
			textBoxLocation->Text = openFileDialog->FileName;
			check = checkGameFiles(openFileDialog->FileName);
		}
		if (check)
		{
			mainWindow->buttonNext->IsEnabled = true;
		}
		else
		{
			mainWindow->buttonNext->IsEnabled = false;
		}

		delete openFileDialog;
	}

	std::wstring GameSetup::calcMd5(const std::wstring &filename)
	{
//# Laniatus Games Studio Inc. | NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (var md5 = MD5.Create())
		{
			auto md5 = MD5::Create();
//# Laniatus Games Studio Inc. | NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (var stream = File.OpenRead(filename))
			{
				auto stream = File::OpenRead(filename);
				std::vector<unsigned char> bytearray = md5.ComputeHash(stream);
				// Convert the byte array to hexadecimal string
				StringBuilder *sb = new StringBuilder();
				for (int i = 0; i < bytearray.size(); i++)
				{
//# Laniatus Games Studio Inc. | TODO TASK: There is no C++ equivalent to 'ToString':
					sb->append(bytearray[i].ToString(L"X2"));
				}

				delete sb;
				return sb->toString();
			}
		}
	}

	bool GameSetup::checkGameFiles(const std::wstring &filename)
	{
		textBlockStatus->Text = L"";
		/* MD5 LIST
		 * SDDF v1.31 unhtp: 35c0777c23afd19cd41423e6adc92b00
		 * SDDF v1.31 enc: 	 ba70fe2917d81bce46fe3e2fe78967e8
		 * SDDF v2.01 unhtp: fd24303120aa5f44c52a074344fe1c3c
		 * SDDF v2.11 unhtp (from SOWS): 
		 * SDDF v2.12 enc (from SOWS): 6455f160b5e14ec9182afcc5b86a3ba1
		 * As more versions appear, I'll update this list. This doesnt indicate anything hidden or secret.
		 */
		bool answer;
		if (FileSystem::fileExists(filename))
		{
			std::wstring exeMd5 = calcMd5(filename);
			exeMd5 = StringHelper::toLower(exeMd5);

//# Laniatus Games Studio Inc. | NOTE: The following 'switch' operated on a string and was converted to C++ 'if-else' logic:
//			switch (exeMd5)
//ORIGINAL LINE: case "35c0777c23afd19cd41423e6adc92b00":
			if (exeMd5 == L"35c0777c23afd19cd41423e6adc92b00")
			{
					answer = true;
					std::wcout << L"Version of IDZ is v1.31, supported version!" << std::endl;
					textBlockStatus->Text = L"Initial D0 v1.31: UNENCRYPTED!\nYou are ready to go!";
			}
//ORIGINAL LINE: case "63b071c35242c035159de374e10caabe":
			else if (exeMd5 == L"63b071c35242c035159de374e10caabe")
			{
					answer = true;
					std::wcout << L"Version of IDZ is v2.11, supported version!" << std::endl;
					textBlockStatus->Text = L"Initial D0 v2.11: UNENCRYPTED!\nYou are ready to go!";
			}
//ORIGINAL LINE: case "ba70fe2917d81bce46fe3e2fe78967e8":
			else if (exeMd5 == L"ba70fe2917d81bce46fe3e2fe78967e8")
			{
					answer = false;
					std::wcout << L"EXE is encrypted!" << std::endl;
					textBlockStatus->Text = L"Initial D0 v1.31: ENCRYPTED!\nYou need to find a copy of the EXE with the encryption removed, This Program cannot help you with that.";
			}
//ORIGINAL LINE: case "fd24303120aa5f44c52a074344fe1c3c":
			else if (exeMd5 == L"fd24303120aa5f44c52a074344fe1c3c")
			{
					answer = false;
					std::wcout << L"Unsupported private version!" << std::endl;
					textBlockStatus->Text = L"I'm not sure how you got this EXE, but it's not supported. You should probably use a private fork of a loader.\nIf you received this in error, contact nzgamer41!";
			}
//ORIGINAL LINE: case "6455f160b5e14ec9182afcc5b86a3ba1":
			else if (exeMd5 == L"6455f160b5e14ec9182afcc5b86a3ba1")
			{
					answer = false;
					std::wcout << L"Unsupported public version!" << std::endl;
					std::wcout << L"EXE is encrypted!" << std::endl;
					textBlockStatus->Text = L"Initial D0 v2.12: ENCRYPTED!\nDo you have a spare sows invite? Just kidding, but this dump is useless at the moment. The EXE is encrypted.";
			}
			else
			{
					answer = false;
					std::wcout << L"MD5 is " << exeMd5 << L" and is not supported atm" << std::endl;
					textBlockStatus->Text = L"I don't think this is the right EXE. Check you've selected the right file.";
			}

			if (answer)
			{
				mainWindow->newConfig->setAMFSDir(FileSystem::getDirectoryName(filename)->Replace(L"package", L"amfs"));
			}
		}
		else
		{
			answer = false;
		}

		return answer;
	}

	void GameSetup::UserControl_Loaded(std::any sender, RoutedEventArgs *e)
	{
		mainWindow = dynamic_cast<MainWindow_new*>(Window::GetWindow(this));
		mainWindow->buttonNext->IsEnabled = false;
	}
}
