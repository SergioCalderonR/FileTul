/*
UserTul will create a sample file in different Windows directories.
Use it to test Controlled Folder Access features for Windows Defender in
Windows 10 Fall Creators Update
*/
#include <Windows.h>
#include <tchar.h>
#include <ShlObj.h>
#include <PathCch.h>

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

int wmain(int argc, WCHAR *argv[])
{
	//SHGetKnownFolderPath
	REFKNOWNFOLDERID folderId = &FOLDERID_Documents;
	DWORD flags = KF_FLAG_DEFAULT;
	PWSTR path=NULL;

	//CreateFileW
	LPCWSTR fileName=NULL;
	DWORD desiredAccess = GENERIC_READ | GENERIC_WRITE;
	DWORD sharedMode = FILE_SHARE_WRITE;
	DWORD creationDisposition = CREATE_NEW;
	DWORD flagsAndAttributes = FILE_ATTRIBUTE_NORMAL;

	//Results
	HANDLE newFile;
	HRESULT hResult;

	//PathCchCombine
	WCHAR pathCombined[MAX_PATH];
	SIZE_T sizeOfPath = MAX_PATH;

	if (argc == 1)
	{
		wprintf(L"\nUsage: FileTul [FolderType]");
		exit(1);

	}
		

	//Getting the current directory to Documents folder
	hResult = SHGetKnownFolderPath(folderId, flags, NULL, &path);

	if (hResult != S_OK)
		wprintf(L"Error code: %lu\n", GetLastError());
	else //Got the Documents path
	{
		wprintf(L"Documents path: %s\n", path);		
		

		if (PathCchCombine(pathCombined, sizeOfPath, path, L"TestFile.txt") != S_OK)
			ShowError(GetLastError());
		else
		{
			
			fileName = pathCombined;
			/*wprintf(L"Full path: %s\n", fileName);*/

			newFile = CreateFileW(fileName, desiredAccess, sharedMode, NULL,
								creationDisposition, flagsAndAttributes, NULL);

			if (newFile != INVALID_HANDLE_VALUE)
			{
				wprintf(L"File was created on: %s\n", fileName);
			}
			else
			{
				wprintf(L"File could not be created. Error code: ");
				ShowError(GetLastError());
			}

			

		}
			

		CoTaskMemFree(path);
	}



	return 0;
}