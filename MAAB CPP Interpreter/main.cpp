#include <iostream>
#include <fstream>
#include <string>
//#include <filesystem>
using namespace std;

#include "maabTask.h"
#include "terminalInstance.h"
#include "newTerminalInstance.h"

#include <conio.h>
#include <stdio.h>


int main(int argc, char* argv[]) 
{
	if (argc != 2)
	{
		cout << "Invalid Arguments!\n";
		string response;
		getline(cin, response);
		return -1;
	}
	const char* fName = argv[1];




	FILE* pFile;
	long lSize;
	char* buffer;
	size_t result;


	cout << "> Reading File \"" << fName << "\"...\n";
	#pragma warning(disable:4096)
	fopen_s(&pFile, fName, "rb");
	if (pFile == NULL) { fputs("File error", stderr); exit(1); }

	// obtain file size:
	fseek(pFile, 0, SEEK_END);
	lSize = ftell(pFile);
	rewind(pFile);
	cout << "+ > Filesize: " << lSize << " bytes.\n";

	// allocate memory to contain the whole file:
	buffer = (char*)malloc(sizeof(char) * lSize);
	if (buffer == NULL) { fputs("Memory error", stderr); exit(2); }

	// copy the file into the buffer:
	result = fread(buffer, 1, lSize, pFile);
	if (result != lSize) { fputs("Reading error", stderr); exit(3); }


	//cout << "Filedata: \"" << buffer << "\"\n";

	/* the whole file is now loaded in the memory buffer. */

	// terminate
	fclose(pFile);
	//free(buffer);





	cout << "> Initing Stuff...\n";

	cout << "+ > Initing User...\n";
	OSUser* user = new OSUser();
	user->colData.userColor = Colors.bgreen;
	user->colData.arrowColor = Colors.gray;
	user->colData.defaultTextColor = Colors.white;
	user->password = "12345";
	user->permLevel = 0;

	cout << "+ > Initing Terminal...\n";
	TerminalInstance* term = new TerminalInstance(user);

	cout << "+ > Initing Window...\n";
	Window* testWindow = new Window((DefaultInstance*)term, Size(10,10), Position(10,10), "Test Window", true, true, true);

	cout << "+ > Initing Terminal (2)...\n";
	term->SetWindow(testWindow);

	cout << "+ > Initing Task...\n";
	TaskMAAB* maabTask = new TaskMAAB(lSize, (uint8_t*)buffer, testWindow, term);

	//((NewTerminalInstance*)term->newTermInstance)->Println("This is a test {}!", "LMAO", Colors.bred);

	cout << "\n\n> Running Stuff...\n";

	while (!maabTask->GetDone())
	{
		maabTask->Do();
		if (maabTask->waitInput && !maabTask->gotInput)
		{
			int input = _kbhit();
			if (input == 0)
				continue;
			char chr = (char)_getch();
			//cout << "CHR: '" << chr << "'";
			if (chr == '\r' || maabTask->memUserInputLen >= 490)
			{
				maabTask->gotInput = true;
			}
			else if (chr == '\b')
			{
				if (maabTask->memUserInputLen > 0)
				{
					maabTask->memUserInput[--maabTask->memUserInputLen] = 0;
					cout << "\b \b";
				}
			}
			else
			{
				maabTask->memUserInput[maabTask->memUserInputLen++] = chr;
				cout << chr;
			}
		}
	}

	maabTask->Free();


	cout << "\n\n\nEnd.";
	{
		string response;
		getline(cin, response);
		return 0;
	}
}