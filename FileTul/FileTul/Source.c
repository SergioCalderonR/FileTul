/*
UserTul will create a sample file in different Windows directories.
Use it to test Controlled Folder Access features for Windows Defender in
Windows 10 Fall Creators Update
*/
#include <Windows.h>
#include <tchar.h>
#include <ShlObj.h>
#include <PathCch.h>
#include <string.h>

#pragma comment(lib, "Pathcch.lib")

VOID ShowHelp()
{
	//Printing help
	wprintf(L"\nFileTul 1.0 - Write and set attributes to sample files in different Windows locations\n" 
			L"Copyrigth (C) 2017 Sergio Calderon\n"
			L"Checho's Blog - http://geeks.ms/blogs/checho \n");

	wprintf(L"\nUsage: \n\n"
		L"--To create a sample file: FileTul.exe [Option]\n\n"
		L"[Options]: \n\n"
		L"-Documents\n\n"
		L"-Pictures\n\n"
		L"-Music\n\n"
		L"-Desktop\n\n"
		L"Example: FileTu.exe -Documents\n\n");

	wprintf(
		L"--To encrypt a file using EFS: FileTul.exe -ef [PathToFile]\n\n"
		L"Example: FileTul.exe -EF C:\\Users\\Andy\\Documents\\newfile.txt\n");



}

//Show error message using Windows error codes
VOID ShowError(DWORD errId)
{
	DWORD formatOptions = FORMAT_MESSAGE_ALLOCATE_BUFFER
						| FORMAT_MESSAGE_FROM_SYSTEM
						| FORMAT_MESSAGE_IGNORE_INSERTS;
	DWORD langId=LANG_SYSTEM_DEFAULT;
	LPWSTR errMsg;

	if (!FormatMessageW(formatOptions, NULL, errId, langId, (LPWSTR)&errMsg, 0, NULL))
		wprintf(L"Could not get the error message. Code: %lu\n", GetLastError());

	wprintf(L"\n%s\n", errMsg);

}

VOID FileCreate(PWSTR path)
{

	//CreateFileW
	LPCWSTR fileName = NULL;
	DWORD desiredAccess = GENERIC_WRITE;
	DWORD sharedMode = FILE_SHARE_WRITE;
	DWORD creationDisposition = CREATE_ALWAYS;
	DWORD flagsAndAttributes = FILE_ATTRIBUTE_NORMAL;

	//PathCchCombine
	WCHAR pathCombined[MAX_PATH];
	SIZE_T sizeOfPath = MAX_PATH;

	HANDLE newFile;

	if (PathCchCombine(pathCombined, sizeOfPath, path, L"TestFile.txt") != S_OK)
		ShowError(GetLastError());
	else
	{		

		newFile = CreateFileW(pathCombined, desiredAccess, sharedMode, NULL,
			creationDisposition, flagsAndAttributes, NULL);

		if (newFile != INVALID_HANDLE_VALUE)
		{
			ShowError(GetLastError());
			CloseHandle(newFile);
		}
		else
		{
			wprintf(L"\nFile could not be created. Error code: ");
			ShowError(GetLastError());

		}
	}


	

}

int wmain(int argc, WCHAR *argv[])
{
	//SHGetKnownFolderPath
	REFKNOWNFOLDERID folderId = &FOLDERID_Documents;
	DWORD flags = KF_FLAG_DEFAULT;
	PWSTR path=NULL;
	
	//Results
	HRESULT hResult;	

	if (argc == 1)
	{
		ShowHelp();
		exit(1);

	}

	switch (argc)
	{
	case 2:
		if (_wcsicmp(argv[1], L"-Documents") == 0)
		{
			//Getting the current directory to Documents folder
			
			hResult = SHGetKnownFolderPath(&FOLDERID_Documents, flags, NULL, &path);

			if (hResult != S_OK) //If fails
			{
				wprintf(L"Error getting Documents folder path. Code: ");
				ShowError(GetLastError());
			}
			else //Got the Documents path
			{
				wprintf(L"\nDocuments path: %s\n", path);

				FileCreate(path);
				CoTaskMemFree(path);
				
			}

		}
		else if (_wcsicmp(argv[1], L"-Pictures") == 0)
		{
			//Getting the current directory to Pictures folder

			hResult = SHGetKnownFolderPath(&FOLDERID_Pictures, flags, NULL, &path);

			if (hResult != S_OK) //If fails
			{
				wprintf(L"Error getting Pictures folder path. Code: ");
				ShowError(GetLastError());
			}
			else //Got the Documents path
			{
				wprintf(L"\nPictures path: %s\n", path);

				FileCreate(path);
				CoTaskMemFree(path);
				

			}

			
		}
		else if (_wcsicmp(argv[1], L"-Desktop") == 0)
		{
			//Getting the current directory to Desktop folder

			hResult = SHGetKnownFolderPath(&FOLDERID_Desktop, flags, NULL, &path);
			

			if (hResult != S_OK) //If fails
			{
				wprintf(L"Error getting Desktop folder path. Code: ");
				ShowError(GetLastError());
			}
			else //Got the Desktop path
			{
				wprintf(L"\nDesktop path: %s\n", path);

				FileCreate(path);
				CoTaskMemFree(path);


			}
		}
		else if (_wcsicmp(argv[1], L"-Music") == 0)
		{
			//Getting the current directory to Music folder

			hResult = SHGetKnownFolderPath(&FOLDERID_Music, flags, NULL, &path);


			if (hResult != S_OK) //If fails
			{
				wprintf(L"Error getting Music folder path. Code: ");
				ShowError(GetLastError());
			}
			else //Got the Music path
			{
				wprintf(L"\nMusic path: %s\n", path);

				FileCreate(path);
				CoTaskMemFree(path);


			}
		}
		else if (_wcsicmp(argv[1], L"-AppData") == 0)
		{
			//Getting the current directory to Local AppData folder

			hResult = SHGetKnownFolderPath(&FOLDERID_LocalAppData, flags, NULL, &path);


			if (hResult != S_OK) //If fails
			{
				wprintf(L"Error getting AppData folder path. Code: ");
				ShowError(GetLastError());
			}
			else //Got the AppData path
			{
				wprintf(L"\nLocal AppData path: %s\n", path);

				FileCreate(path);
				CoTaskMemFree(path);


			}

		}
		else if (_wcsicmp(argv[1], L"-WinDir") == 0)
		{
			//Getting the current directory to Windows directory folder

			hResult = SHGetKnownFolderPath(&FOLDERID_Windows, flags, NULL, &path);


			if (hResult != S_OK) //If fails
			{
				wprintf(L"Error getting WinDir folder path. Code: ");
				ShowError(GetLastError());
			}
			else //Got the WinDir path
			{
				wprintf(L"\nWindows directory path: %s\n", path);

				FileCreate(path);
				CoTaskMemFree(path);


			}

		}
		else
		{
			ShowHelp();
		}
			

		break;

		case 3:
			if (_wcsicmp(argv[1], L"-EF") == 0)
			{


				if (EncryptFileW(argv[2]))
				{
					wprintf(L"\nFile encyrpted.\n");
					ShowError(GetLastError());
				}
				else
					ShowError(GetLastError());

			}
			else
				ShowHelp();

			break;

	default:
		ShowHelp();
		break;
	}

	return 0;
}