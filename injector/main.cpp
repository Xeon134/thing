#include <iostream>
#include <Windows.h>
#include <filesystem>
#include <TlHelp32.h>

#include "injector.h"

using namespace std;

DWORD processId = NULL;

bool FindProcessId(string processName) {
	PROCESSENTRY32 processInfo;
	processInfo.dwSize = sizeof(processInfo);

	HANDLE processSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (processSnapshot == INVALID_HANDLE_VALUE)
		return FALSE;

	Process32First(processSnapshot, &processInfo);
	if (!processName.compare(processInfo.szExeFile)) {
		CloseHandle(processSnapshot);
		processId = processInfo.th32ProcessID;
		return TRUE;
	}

	while (Process32Next(processSnapshot, &processInfo)) {
		if (!processName.compare(processInfo.szExeFile)) {
			CloseHandle(processSnapshot);
			processId = processInfo.th32ProcessID;
			return TRUE;
		}
	}

	CloseHandle(processSnapshot);
	return FALSE;
}

int wmain(int argc, wchar_t* argv[]) {
	cout << "Waiting for Sea of Thieves to launch." << endl;

	do {
		Sleep(1000);
	} while (!FindProcessId("SoTGame.exe"));

	cout << "Found the Sea of Thieves process." << endl;

	auto filePath = filesystem::path(argv[0]).remove_filename().string() + string("sot-internal.dll");

	cout << "Injecting " << filePath << "..." << endl;

	HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
	if (ManualMap(process, filePath.c_str())) {
		CloseHandle(process);
		cout << "Done." << endl << endl;
	}

	cin.get();
	return EXIT_SUCCESS;
}