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

	wprintf(L"%s\n", errMsg);

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
			wprintf(L"\nFile was created on: %s\n", pathCombined);
			ShowError(GetLastError());
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
		wprintf(L"\nUsage: %s [FolderType]\n", argv[0]);
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
			FileCreate(argv[1]);
		}
			

		break;

	default:
		break;
	}

	return 0;
}