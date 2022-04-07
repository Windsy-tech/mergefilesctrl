// MergeFileConsole.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include "MergeFileConsole.h"
#include <windows.h> 
#include <stdio.h> 
#include <string>
#include <stdlib.h>
#include <cstdio>
#include <fstream>
#include <filesystem>
#include <Windows.h>

using namespace std;

int main()
{
	cout << "Hello World!\n";	
	std::wcout << ExePath() << "\n";
	MergeFiles();
	
}

std::wstring ExePath() {
	TCHAR buffer[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, buffer, MAX_PATH);
	std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
	return std::wstring(buffer).substr(0, pos);
}

// Temp workaround for customer
int MergeFiles() {

	fstream oldFile;
	fstream newFile;
	fstream wFile;

	oldFile.open("test1.din", ios::in);

	wFile.open("writtenfile.din", ios::out);

	//C:\\Users\\Mj\\S2\\mergefilesctrl\\


	int i = 0;
	if (oldFile.is_open()) {
		std::string line;
		std::string newLine;
		// Loop through the old file
		while (getline(oldFile, line)) {

			// ********** Turbine characteristics only ***********
			if ((i >= 26) && (i <= 38) || (i >= 58) && (i <= 76) || (i >= 79) && (i <= 86)) {
				std::string tempLine;
				tempLine = line.substr(0, line.find(" "));
				//cout << "TempLine: " << tempLine << endl;

				//cout << tempLine << endl;

				//RpmMinConverter     1020                  [rpm]   *read from Flex if not specified; minimal rpm of converter

				//*Turbine Type
				if (tempLine.at(0) != '*') {
					int j = 0;
					std::string tempString;

					newFile.open("test2.din", ios::in);

					while (getline(newFile, newLine)) {

						// RatedPower          2080[kW] * read from Flex if not specified; Rated Power
						// GearEfficiency      0.9740[-] * read from Flex if not specified; gear box efficiency
						std::string tempLine2;
						tempLine2 = newLine.substr(0, newLine.find(" "));

						//cout << "j val: " << j << endl;
						//cout << "TempLine2: " << tempLine2 << endl;

						if ((j >= 1 && j <=2) || (j >=5 && j <=15) || (j >= 18 && j <= 23)) {
							if (tempLine2.find(tempLine) != std::string::npos) {
								tempString = newLine;
								newLine.clear();
								newFile.close();
								break;
							}
						}
						j++;
					}
					if (tempString.empty()) {
						tempString = line;					
					}
					wFile << tempString << endl;
					newLine.clear();
					newFile.close();
				}
				else {
					wFile << line << endl;
				}
				//cout << line << endl;
			} 
			else {
				wFile << line << endl;
			}

			i++;
		}

		//Change Turbine Characteristics

		//for (int i = )
		cout << "Total lines in file: " << i << endl;
		oldFile.close();
		wFile.close();
	}
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
