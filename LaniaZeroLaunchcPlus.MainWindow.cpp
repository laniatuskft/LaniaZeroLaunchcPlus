#include "LaniaZeroLaunchcPlus.MainWindow.h"
#include "LaniaZeroLaunchcPlus.MainWindow_new.h"
#include "LaniaZeroLaunchcPlus.ControllerSettings.h"

using namespace Microsoft::Win32;
using namespace WPFFolderBrowser;
using namespace AutoUpdaterDotNET;

namespace LaniaZeroLaunchcPlus
{

bool MainWindow::Terminate = false;
bool MainWindow::consoleEnabled = false;
IDZConfig *MainWindow::gameConfig = new IDZConfig();

	MainWindow::MainWindow()
	{
	#if defined(DEBUG)
		if (!FileSystem::fileExists(L"idzconfig.bin"))
		{
			MainWindow_new *mwNew = new MainWindow_new();
			mwNew->ShowDialog();
			gameConfig = mwNew->newConfig;
			if (!gameConfig->getXOrDInput())
			{
				ControllerSettings *cs = new ControllerSettings(gameConfig, gameConfig->getXOrDInput());
				cs->ShowDialog();

				delete cs;
			}

//# Laniatus Games Studio Inc. | TODO TASK: A 'delete mwNew' statement was not added since mwNew was assigned to a field. Handle memory management manually.
		}
	#endif
		AutoUpdater::Start(L"https://raw.githubusercontent.com/nzgamer41/LaniaZeroLaunchcPlus/master/Autoupdate.xml");
		try
		{
			InitializeComponent();
			for (auto nic : NetworkInterface::GetAllNetworkInterfaces())
			{
				if (nic->Supports(NetworkInterfaceComponent::IPv4) == false)
				{
					continue;
				}
				for (auto ip : *nic->GetIPProperties()->UnicastAddresses)
				{
					if (ip->Address->AddressFamily == System::Net::Sockets::AddressFamily::InterNetwork)
					{
						networkAdapters.push_back(nic);
//# Laniatus Games Studio Inc. | TODO TASK: There is no C++ equivalent to 'ToString':
						comboBoxNetAdapter::Items->Add(nic->Name + L" " + ip->Address->ToString());
					}
				}
			}

			if (FileSystem::fileExists(L"idzconfig.bin"))
			{
				gameConfig = ReadFromBinaryFile<IDZConfig*>(L"idzconfig.bin");
				updateUI();
			}
			else
			{
				comboBoxNetAdapter->SelectedIndex = 0;
				updateUI();
			}
		}
		catch (const std::runtime_error &ex)
		{
			Debug::WriteLine(ex.what());
		}
	}

	void MainWindow::updateUI()
	{
		int selAdapter = networkAdapters.FindIndex([&] (std::any x)
		{
			return x->Name == gameConfig->getSelectedNic();
		});
		if (selAdapter != -1)
		{
			comboBoxNetAdapter->SelectedIndex = selAdapter;
		}

		if (gameConfig->getJapOrExp())
		{
			buttonJap->IsChecked = false;
			buttonExp->IsChecked = true;
		}
		else if (gameConfig->getJapOrExp() == false)
		{
			buttonExp->IsChecked = false;
			buttonJap->IsChecked = true;
		}

		textBoxGameAMFS->Text = gameConfig->getAMFSDir();

		checkBoxIdeal->IsChecked = gameConfig->getIdealLan();
		checkBoxDistServ->IsChecked = gameConfig->getDistServer();
		if (gameConfig->getRestriction() != 0)
		{
			restrictUpDown->Value = gameConfig->getRestriction();
		}
		else
		{
			restrictUpDown->Value = 97;
		}
		// When I implement a online AIME server this will be togglable
		//checkBoxAime.IsChecked = gameConfig.ImitateMe;
		std::wstring reg = L"Japan";
		if (gameConfig->getJapOrExp())
		{
			reg = L"Export";
		}
		std::wstring reg2 = L"DInput";
		if (gameConfig->getXOrDInput())
		{
			reg2 = L"XInput";
		}
	}

	void MainWindow::RadioButton_Checked(std::any sender, RoutedEventArgs *e)
	{

	}

	void MainWindow::ComboBoxNetAdapter_SelectionChanged(std::any sender, SelectionChangedEventArgs *e)
	{
		gameConfig->setSelectedNic(networkAdapters[comboBoxNetAdapter::SelectedIndex]->Name);
		for (auto ip : networkAdapters[comboBoxNetAdapter::SelectedIndex]->GetIPProperties()->UnicastAddresses)
		{
			if (ip->Address->AddressFamily == System::Net::Sockets::AddressFamily::InterNetwork)
			{
//# Laniatus Games Studio Inc. | TODO TASK: There is no C++ equivalent to 'ToString':
				gameConfig->setSelectedIP(ip->Address->ToString());
			}
		}
	}

	void MainWindow::configUpdate()
	{
		gameConfig->setSelectedNic(networkAdapters[comboBoxNetAdapter::SelectedIndex]->Name);
		for (auto ip : networkAdapters[comboBoxNetAdapter::SelectedIndex]->GetIPProperties()->UnicastAddresses)
		{
			if (ip->Address->AddressFamily == System::Net::Sockets::AddressFamily::InterNetwork)
			{
//# Laniatus Games Studio Inc. | TODO TASK: There is no C++ equivalent to 'ToString':
				gameConfig->setSelectedIP(ip->Address->ToString());
			}
		}
		if (static_cast<bool>(buttonExp::IsChecked))
		{
			gameConfig->setJapOrExp(true);
		}
		else if (static_cast<bool>(buttonJap::IsChecked))
		{
			gameConfig->setJapOrExp(false);
		}

		gameConfig->setAMFSDir(textBoxGameAMFS->Text);
		if (static_cast<bool>(buttonXinput::IsChecked))
		{
			gameConfig->setXOrDInput(true);
		}
		else if (static_cast<bool>(buttonDinput::IsChecked))
		{
			gameConfig->setXOrDInput(false);
		}

		gameConfig->setTwinStick(static_cast<bool>(checkBoxTwinStick::IsChecked));
		gameConfig->setIdealLan(static_cast<bool>(checkBoxIdeal::IsChecked));
		gameConfig->setDistServer(static_cast<bool>(checkBoxDistServ::IsChecked));
		// When I implement a online AIME server this will be togglable
		//checkBoxAime.IsChecked = gameConfig.ImitateMe;
		gameConfig->setRestriction(static_cast<int>(restrictUpDown->Value));
		WriteToBinaryFile(L"idzconfig.bin", gameConfig, false);
	}

	void MainWindow::Window_Closing(std::any sender, System::ComponentModel::CancelEventArgs *e)
	{
		configUpdate();
	}

	void MainWindow::TextBoxGameAMFS_MouseDown(std::any sender, MouseButtonEventArgs *e)
	{
	}

	void MainWindow::TextBoxGameAMFS_PreviewMouseDown(std::any sender, MouseButtonEventArgs *e)
	{
		WPFFolderBrowserDialog *folderBrowser = new WPFFolderBrowserDialog();
		if (folderBrowser->ShowDialog() == true)
		{
			textBoxGameAMFS->Text = folderBrowser->FileName;
		}

		delete folderBrowser;
	}

	void MainWindow::Button_Click(std::any sender, RoutedEventArgs *e)
	{
		if (textBoxGameAMFS->Text != L"")
		{
			configUpdate();
			gameConfig->ExportConfig();
			//Double checking the folder is actually selected
			gameBoot();
		}
		else
		{
			MessageBox::Show(L"You should probably select the AMFS folder first....\n\nDon't know how you expect to run the game without it?");
		}
	}

	void MainWindow::bootAime()
	{
		auto psiNpmRunDist = new ProcessStartInfo();
		psiNpmRunDist->FileName = L"cmd";
		psiNpmRunDist->RedirectStandardInput = true;
		psiNpmRunDist->WorkingDirectory = L".\\deps\\minime";
		//psiNpmRunDist.CreateNoWindow = true;
		psiNpmRunDist->UseShellExecute = false;
		auto pNpmRunDist = Process::Start(psiNpmRunDist);
		pNpmRunDist->StandardInput->WriteLine(L"start.bat");
		pNpmRunDist->WaitForExit();

//# Laniatus Games Studio Inc. | TODO TASK: A 'delete psiNpmRunDist' statement was not added since psiNpmRunDist was passed to a method or constructor. Handle memory management manually.
	}

	void MainWindow::bootAmdaemon()
	{
		auto psiNpmRunDist = new ProcessStartInfo();
		psiNpmRunDist->FileName = gameConfig->getAMFSDir() + L"\\..\\app\\package\\inject.exe";
		psiNpmRunDist->WorkingDirectory = gameConfig->getAMFSDir() + L"\\..\\app\\package\\";
		psiNpmRunDist->Arguments = L"-d -k .\\idzhook.dll .\\amdaemon.exe -c configDHCP_Final_Common.json configDHCP_Final_JP.json configDHCP_Final_JP_ST1.json configDHCP_Final_JP_ST2.json configDHCP_Final_EX.json configDHCP_Final_EX_ST1.json configDHCP_Final_EX_ST2.json";
		psiNpmRunDist->UseShellExecute = false;
		auto pNpmRunDist = Process::Start(psiNpmRunDist);
		pNpmRunDist->WaitForExit();

//# Laniatus Games Studio Inc. | TODO TASK: A 'delete psiNpmRunDist' statement was not added since psiNpmRunDist was passed to a method or constructor. Handle memory management manually.
	}

	void MainWindow::bootIDZ()
	{
		auto psiNpmRunDist = new ProcessStartInfo();
		psiNpmRunDist->FileName = gameConfig->getAMFSDir() + L"\\..\\app\\package\\inject.exe";
		psiNpmRunDist->WorkingDirectory = gameConfig->getAMFSDir() + L"\\..\\app\\package\\";
		psiNpmRunDist->Arguments = L"-k .\\idzhook.dll .\\InitialD0_DX11_Nu.exe";
		psiNpmRunDist->UseShellExecute = false;
		auto pNpmRunDist = Process::Start(psiNpmRunDist);
		pNpmRunDist->WaitForExit();

//# Laniatus Games Studio Inc. | TODO TASK: A 'delete psiNpmRunDist' statement was not added since psiNpmRunDist was passed to a method or constructor. Handle memory management manually.
	}

	void MainWindow::gameBoot()
	{

		/*
		 *  IDZ needs a very specific chain of things booted because SEGA
		 *  Step 1: MiniMe
		 *  Step 2: Locale Emu
		 *  Step 3: Amdaemon
		 *  Step 4: Game
		 *  this gon' be a bitch
		 */

		//  Step 0: Checking for Segatools
		//put code here dumbass
		if (!FileSystem::fileExists(gameConfig->getAMFSDir() + L"\\..\\app\\package\\inject.exe"))
		{
			Debug::WriteLine(L"missing segatools!");
			MessageBox::Show(L"You appear to be missing Segatools!\n\nCopy this from the 'deps\\segatools' folder into your 'package' folder where the main game files are.\n\nAlso make sure that you've left the amfs folder into the normal spot (so the same folder as app and pack.", L"Missing segatools", MessageBoxButton::OK, MessageBoxImage::Error);
			return;
		}
		AllocConsole();
		SetConsoleTitle(L"LaniaZeroLaunchcPlus Console Output (contains MiniMe and Amdaemon in one window)");
		//  Step 1: MiniMe.
		//checking for NodeJS
		ThreadStart ths = nullptr;
		Thread *th = nullptr;
		if (isNodeInstalled())
		{
			//passed node check, now to install dependencies
			if (FileSystem::fileExists(L"deps\\minime\\start.bat"))
			{
				ths = new ThreadStart([&] ()
				{
					bootAime();
				});
				th = new Thread(ths);
				th->Start();
			}
		}
		else
		{
			MessageBox::Show(L"It appears you don't have NodeJS installed! We could not find it in your PATH environment variable, if for some reason you have it installed in a folder that doesn't contain the word 'node', this will get confusing.\n\nThe default is: C:\\Program Files\\nodejs.\n\nMiniMe requires node! Quitting game.", L"Missing dependency", MessageBoxButton::OK, MessageBoxImage::Exclamation);

			delete th;
			return;
		}
		//locale emu stuff can go here once i figure out how tf to get it to work
		//  Step 3: Amdaemon
		ThreadStart ths2 = new ThreadStart([&] ()
		{
			bootAmdaemon();
		});
		Thread *th2 = new Thread(ths2);
		th2->Start();

		//  Step 4: IDZ
		ThreadStart ths3 = new ThreadStart([&] ()
		{
			bootIDZ();
		});
		Thread *th3 = new Thread(ths3);
		th3->Start();

		ThreadStart ths4 = new ThreadStart([&] ()
		{
			monitorGame(th,th2,th3);
		});
		Thread *th4 = new Thread(ths4);
		th4->Start();

		buttonLaunch->Visibility = Visibility::Hidden;
		buttonLaunch->IsEnabled = false;
		buttonClose->Visibility = Visibility::Visible;
		buttonClose->IsEnabled = true;

		delete th4;
//# Laniatus Games Studio Inc. | TODO TASK: A 'delete th3' statement was not added since th3 was passed to a method or constructor. Handle memory management manually.
//# Laniatus Games Studio Inc. | TODO TASK: A 'delete th2' statement was not added since th2 was passed to a method or constructor. Handle memory management manually.
//# Laniatus Games Studio Inc. | TODO TASK: A 'delete th' statement was not added since th was passed to a method or constructor. Handle memory management manually.
	}

	void MainWindow::flipTerm()
	{
		Terminate = !Terminate;
		buttonLaunch->Visibility = Visibility::Visible;
		buttonLaunch->IsEnabled = true;
		buttonClose->Visibility = Visibility::Hidden;
		buttonClose->IsEnabled = false;
	}

	void MainWindow::monitorGame(Thread *th, Thread *th2, Thread *th3)
	{
		while (th2->IsAlive || th3->IsAlive)
		{
			if (Terminate)
			{
				auto currentId = Process::GetCurrentProcess()->Id;
				Regex *regex = new Regex(LR"(amdaemon.*)");
				for (auto p : Process::GetProcesses(L"."))
				{
					if (regex->Match(p->ProcessName)->Success)
					{
						p->Kill();
						std::wcout << L"killed amdaemon!" << std::endl;
					}
				}
				regex = new Regex(LR"(InitialD0.*)");
				for (auto p : Process::GetProcesses(L"."))
				{
					if (regex->Match(p->ProcessName)->Success)
					{
						p->Kill();
						std::wcout << L"killed game process!" << std::endl;
					}
				}
				regex = new Regex(LR"(ServerBoxD8.*)");
				for (auto p : Process::GetProcesses(L"."))
				{
					if (regex->Match(p->ProcessName)->Success)
					{
						p->Kill();
						std::wcout << L"killed serverbox!" << std::endl;
					}
				}
				regex = new Regex(LR"(inject.*)");
				for (auto p : Process::GetProcesses(L"."))
				{
					if (regex->Match(p->ProcessName)->Success)
					{
						p->Kill();
						std::wcout << L"killed inject.exe!" << std::endl;
					}
				}
				regex = new Regex(LR"(node.*)");
				for (auto p : Process::GetProcesses(L"."))
				{
					if (regex->Match(p->ProcessName)->Success)
					{
						p->Kill();
						std::wcout << L"killed nodeJS! (if you were running node, you may want to restart it)" << std::endl;
					}
				}

				delete regex;
			}
		}
		//time to kill node
		Terminate = !Terminate;
		FreeConsole();
		return;
	}

	bool MainWindow::isNodeInstalled()
	{
		// FUCK NODE 2 ELECTRIC BOOGALOO
		std::wstring envVars = Environment::GetEnvironmentVariable(L"PATH");
		Debug::WriteLine(envVars);
		if (envVars.find(L"node") != std::wstring::npos)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void MainWindow::ButtonControls_Click(std::any sender, RoutedEventArgs *e)
	{
		ControllerSettings *cs = new ControllerSettings(gameConfig, gameConfig->getXOrDInput());
		cs->ShowDialog();

		delete cs;
	}

	void MainWindow::Window_PreviewKeyDown(std::any sender, KeyEventArgs *e)
	{
		if (e->Key == Key::Escape)
		{
			Terminate = true;
		}
	}

	void MainWindow::buttonClose_Click(std::any sender, RoutedEventArgs *e)
	{
		flipTerm();
	}

	void MainWindow::buttonDinput_Checked(std::any sender, RoutedEventArgs *e)
	{
		buttonControls->IsEnabled = true;
	}

	void MainWindow::buttonXinput_Checked(std::any sender, RoutedEventArgs *e)
	{
		buttonControls->IsEnabled = false;
	}

	void MainWindow::Window_ContentRendered(std::any sender, EventArgs *e)
	{
		if (gameConfig->getXOrDInput())
		{
			buttonDinput->IsChecked = false;
			buttonXinput->IsChecked = true;
		}
		else if (gameConfig->getXOrDInput() == false)
		{
			buttonDinput->IsChecked = true;
			buttonXinput->IsChecked = false;
		}

	}

	void MainWindow::Button_Click_1(std::any sender, RoutedEventArgs *e)
	{
		Process::Start(L"https://discord.link/LaniaZeroLaunchcPlus");
	}
}
