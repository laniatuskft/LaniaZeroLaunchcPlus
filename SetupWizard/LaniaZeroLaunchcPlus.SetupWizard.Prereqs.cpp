#include "LaniaZeroLaunchcPlus.SetupWizard.Prereqs.h"

namespace LaniaZeroLaunchcPlus::SetupWizard
{

	Prereqs::Prereqs()
	{
		InitializeComponent();

	}

	void Prereqs::UserControl_Loaded(std::any sender, RoutedEventArgs *e)
	{
		mainWindow = dynamic_cast<MainWindow_new*>(Window::GetWindow(this));
		mainWindow->buttonPrev->IsEnabled = false;
		mainWindow->buttonNext->IsEnabled = false;
		beginCheck();
	}

//# Laniatus Games Studio Inc. | TODO TASK: There is no equivalent in C++ to the 'async' keyword:
//ORIGINAL LINE: private async void beginCheck()
	void Prereqs::beginCheck()
	{
	#if defined(DEBUG)
		//saves having to install them every time
		//mainWindow.redistsComplete = true;
	#endif
		if (mainWindow->redistsComplete)
		{
			textBlockStatus->Text = L"Prerequisites have already been installed.";
			mainWindow->buttonPrev->IsEnabled = true;
			mainWindow->buttonNext->IsEnabled = true;
			return;
		}
		/* FUCK MICROSOFT
		 * Why the fuck is there no easy way to check for the DirectX Redistributables
		 * 
		 * ok real shit
		 * step 1: "check" for directx
		 * step 2: check for node (gonna use clever shit)
		 * step 3: check for VC2012
		 * step 4: install missing redists
		 * 
		 */
		//BEGIN DX
		textBlockStatus->Text = L"Installing DirectX Redistributibles...";
		//await Task.Run(() => downloadFile("https://download.microsoft.com/download/1/7/1/1718CCC4-6315-4D8E-9543-8E28A4E18C4C/dxwebsetup.exe"));
		//FUCK MICROSOFT AGAIN HOLY SHIT WHY'D THEY REMOVE THE DIRECTX DOWNLOADS
		if (FileSystem::fileExists(L"DirectX.zip"))
		{
			try
			{
				File::Delete(L"DirectX.zip");
				Directory::Delete(L".\\DirectX", true);
			}
			catch (...)
			{

			}
		}
//# Laniatus Games Studio Inc. | TODO TASK: There is no equivalent to 'await' in C++:
		await Task::Run([&] ()
		{
			downloadFile(L"https://nzgamer41.win/TeknoParrot/TPRedists/DirectX.zip");
		});
		ZipFile::ExtractToDirectory(L".\\DirectX.zip", L".\\DirectX");
		pbDl->IsIndeterminate = true;
		Process *p = new Process();
		ProcessStartInfo *si = new ProcessStartInfo();
//# Laniatus Games Studio Inc. | TODO TASK: There is no equivalent to 'await' in C++:
		await runProcess(L".\\DirectX\\dxsetup.exe", p, si);
		/*si.FileName = "dxwebsetup.exe";
		si.Arguments = "/Q";
		p.StartInfo = si;
		p.Start();
		await Task.Run(() => p.WaitForExit());*/


		textBlockStatus->Text += L"COMPLETE\n";
		//File.Delete("dxwebsetup.exe");

		File::Delete(L"DirectX.zip");
		Directory::Delete(L".\\DirectX", true);


		//END DX

		//BEGIN NODE
		//fuck im a genius
		std::wstring testjs = L"console.log(\"test\");";
		File::WriteAllText(L"test.js", testjs);

		auto enviromentPath = System::Environment::GetEnvironmentVariable(L"PATH");

		std::wcout << enviromentPath << std::endl;
		auto paths = StringHelper::split(enviromentPath, L';');
		auto exePath = paths.Select([&] (std::any x)
		{
			return FileSystem::combine(x, L"node.exe");
		})->Where([&] (std::any x)
		{
			return FileSystem::fileExists(x);
		})->FirstOrDefault();
		textBlockStatus->Text += L"Checking for Node.js...";
		p = new Process();
		si = new ProcessStartInfo();
		si->FileName = exePath;
		si->Arguments = L"test.js";
		si->RedirectStandardOutput = true;
		si->UseShellExecute = false;
		p->StartInfo = si;
		p->Start();
		std::wstring output = p->StandardOutput->ReadToEnd();
		p->WaitForExit();
		File::Delete(L"test.js");
		if (output == L"test\n")
		{
			textBlockStatus->Text += L"FOUND";
		}
		else
		{
			textBlockStatus->Text += L"NOT FOUND, DOWNLOADING...";
			pbDl->IsIndeterminate = false;
//# Laniatus Games Studio Inc. | TODO TASK: There is no equivalent to 'await' in C++:
			await Task::Run([&] ()
			{
				downloadFile(L"https://nodejs.org/dist/v12.18.3/node-v12.18.3-x64.msi");
			});
			Process *process = new Process();
			process->StartInfo->FileName = L"msiexec";
			process->StartInfo->WorkingDirectory = LR"(C:\temp\)";
			process->StartInfo->Arguments = L"/quiet /i " + FileSystem::getCurrentDirectory() + L"\\node-v12.18.3-x64.msi";
			process->StartInfo->Verb = L"runas";
			process->Start();
//# Laniatus Games Studio Inc. | TODO TASK: There is no equivalent to 'await' in C++:
			await Task::Run([&] ()
			{
				process->WaitForExit();
			});
			textBlockStatus->Text += L"COMPLETE\n";
			File::Delete(L"node-v12.18.3-x64.msi");

			delete process;
		}
		// END NODE

		//VS redists
		textBlockStatus->Text += L"\nInstalling Visual Studio Redistributibles...";
//# Laniatus Games Studio Inc. | TODO TASK: There is no equivalent to 'await' in C++:
		await Task::Run([&] ()
		{
			downloadFile(L"http://nzgamer41.win/TeknoParrot/TPRedists/vcr.zip");
		});
		//now the cooked shit begins
		ZipFile::ExtractToDirectory(L".\\vcr.zip", L".\\vcr");
		pbDl->IsIndeterminate = true;
//# Laniatus Games Studio Inc. | TODO TASK: There is no equivalent to 'await' in C++:
		await runProcess(L".\\vcr\\vcredist2005_x86.exe", p, si);
//# Laniatus Games Studio Inc. | TODO TASK: There is no equivalent to 'await' in C++:
		await runProcess(L".\\vcr\\vcredist2005_x64.exe", p, si);
//# Laniatus Games Studio Inc. | TODO TASK: There is no equivalent to 'await' in C++:
		await runProcess(L".\\vcr\\vcredist2008_x86.exe", p, si);
//# Laniatus Games Studio Inc. | TODO TASK: There is no equivalent to 'await' in C++:
		await runProcess(L".\\vcr\\vcredist2008_x64.exe", p, si);
//# Laniatus Games Studio Inc. | TODO TASK: There is no equivalent to 'await' in C++:
		await runProcess(L".\\vcr\\vcredist2010_x86.exe", p, si);
//# Laniatus Games Studio Inc. | TODO TASK: There is no equivalent to 'await' in C++:
		await runProcess(L".\\vcr\\vcredist2010_x64.exe", p, si);
//# Laniatus Games Studio Inc. | TODO TASK: There is no equivalent to 'await' in C++:
		await runProcess(L".\\vcr\\vcredist2012_x86.exe", p, si);
//# Laniatus Games Studio Inc. | TODO TASK: There is no equivalent to 'await' in C++:
		await runProcess(L".\\vcr\\vcredist2012_x64.exe", p, si);
//# Laniatus Games Studio Inc. | TODO TASK: There is no equivalent to 'await' in C++:
		await runProcess(L".\\vcr\\vcredist2013_x86.exe", p, si);
//# Laniatus Games Studio Inc. | TODO TASK: There is no equivalent to 'await' in C++:
		await runProcess(L".\\vcr\\vcredist2013_x64.exe", p, si);
//# Laniatus Games Studio Inc. | TODO TASK: There is no equivalent to 'await' in C++:
		await runProcess(L".\\vcr\\vcredist2015_2017_2019_x86.exe", p, si);
//# Laniatus Games Studio Inc. | TODO TASK: There is no equivalent to 'await' in C++:
		await runProcess(L".\\vcr\\vcredist2015_2017_2019_x64.exe", p, si);
		textBlockStatus->Text += L"COMPLETE\n";
		File::Delete(L"vcr.zip");
		Directory::Delete(L".\\vcr", true);
		pbDl->IsIndeterminate = false;
		pbDl->Value = 100;
		mainWindow->buttonNext->IsEnabled = true;
		mainWindow->buttonPrev->IsEnabled = true;
		mainWindow->redistsComplete = true;

//# Laniatus Games Studio Inc. | TODO TASK: A 'delete si' statement was not added since si was passed to a method or constructor. Handle memory management manually.
//# Laniatus Games Studio Inc. | TODO TASK: A 'delete p' statement was not added since p was passed to a method or constructor. Handle memory management manually.
	}

//# Laniatus Games Studio Inc. | TODO TASK: There is no equivalent in C++ to the 'async' keyword:
//ORIGINAL LINE: async Task runProcess(string filename, Process p, ProcessStartInfo si)
	Task *Prereqs::runProcess(const std::wstring &filename, Process *p, ProcessStartInfo *si)
	{
		bool isDone = false;

		p = new Process();
		si = new ProcessStartInfo();
		si->FileName = filename;
		if (filename.find(L"2005") != std::wstring::npos)
		{
			si->Arguments = L"/q";
		}
		else if (filename.find(L"2008") != std::wstring::npos)
		{
			si->Arguments = L"/qb";
		}
		else if (filename.find(L"dxsetup") != std::wstring::npos)
		{
			si->Arguments = L"/silent";
		}
		else
		{
			si->Arguments = L"/passive /norestart";
		}

		p->StartInfo = si;
		p->Start();
		//await Task.Run(() => p.WaitForExit());
		while (!p->HasExited)
		{
//# Laniatus Games Studio Inc. | TODO TASK: There is no equivalent to 'await' in C++:
			await Task::Delay(100);
		}
	}

	void Prereqs::downloadFile(const std::wstring &fileToDownload)
	{
//# Laniatus Games Studio Inc. | NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (WebClient wc = new WebClient())
		{
			WebClient wc = WebClient();
			this->Dispatcher->Invoke([&] ()
			{
				pbDl->IsIndeterminate = false;
				pbDl->Value = 0;
			});
			downloadComplete = false;
//# Laniatus Games Studio Inc. | TODO TASK: We cannot do this event wiring in C++. A new wiring method is required.. -----Lania-Issue: 3917 #DASH:
			wc.DownloadProgressChanged += wc_DownloadProgressChanged;
//# Laniatus Games Studio Inc. | TODO TASK: We cannot do this event wiring in C++. A new wiring method is required.. -----Lania-Issue: 3922 #DASH:
			wc.DownloadFileCompleted += wc_DownloadFileCompleted;
			System::Uri tempVar(fileToDownload);
			wc.DownloadFileAsync(&tempVar, FileSystem::getFileName(fileToDownload));

			while (!downloadComplete)
			{
				//wait
			}
		}
	}

	void Prereqs::wc_DownloadFileCompleted(std::any sender, AsyncCompletedEventArgs *e)
	{
		this->Dispatcher->Invoke([&] ()
		{
			downloadComplete = true;
			pbDl->IsIndeterminate = true;
		});
	}

	void Prereqs::wc_DownloadProgressChanged(std::any sender, DownloadProgressChangedEventArgs *e)
	{
		this->Dispatcher->Invoke([&] ()
		{
			pbDl->Value = e->ProgressPercentage;
		});
	}
}
