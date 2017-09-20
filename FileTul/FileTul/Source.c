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

VOID ShowError(DWORD errId)
{


}

int wmain(int argc, WCHAR *argv[])
{
	//SHGetKnownFolderPath
	REFKNOWNFOLDERID folderId = &FOLDERID_Documents;
	DWORD flags = KF_FLAG_DEFAULT;
	PWSTR path=NULL;

	//CreateFileW
	LPCWSTR fileName = L"TestFile.txt";
	DWORD desiredAccess = GENERIC_READ | GENERIC_WRITE;
	DWORD sharedMode = FILE_SHARE_WRITE;
	DWORD creationDisposition = CREATE_NEW;
	DWORD flagsAndAttributes = FILE_ATTRIBUTE_NORMAL;

	//Results
	HANDLE newFile;
	HRESULT hResult = SHGetKnownFolderPath(folderId, flags, NULL,&path);

	//PathCchCombine
	WCHAR pathCombined[MAX_PATH];
	SIZE_T sizeOfPath = MAX_PATH;

	if (hResult != S_OK)
		wprintf(L"Error code: %lu\n", GetLastError());
	else
	{
		wprintf(L"Documents path: %s\n", path);
		wprintf(L"%s\n", fileName);

		HRESULT fullPath = PathCchCombine(pathCombined, sizeOfPath, path, fileName);

		if (fullPath != S_OK)
			wprintf(L"Error combining full path. Code: %lu\n", GetLastError());
		else
			wprintf(L"Full path: %s\n", pathCombined);

		CoTaskMemFree(path);
	}

	

	getchar();

	return 0;
}