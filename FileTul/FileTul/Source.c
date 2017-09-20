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
	DWORD desiredAccess = GENERIC_READ | GENERIC_WRITE;
	DWORD sharedMode = FILE_SHARE_WRITE;
	DWORD creationDisposition = CREATE_NEW;
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
		else
			wprintf(L"Miss typing.\n");

		break;

	default:
		break;
	}

	return 0;
}