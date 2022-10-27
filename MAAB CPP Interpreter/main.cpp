#include <iostream>
#include <fstream>
//#include <filesystem>
using namespace std;

#include "maabTask.h"
#include "terminalInstance.h"
#include "newTerminalInstance.h"


int main(int argc, char* argv[]) 
{
	FILE* pFile;
	long lSize;
	char* buffer;
	size_t result;


	cout << "> Reading File...\n";
	#pragma warning(disable:4096)
	fopen_s(&pFile, "test.maab", "rb");
	if (pFile == NULL) { fputs("File error", stderr); exit(1); }

	// obtain file size:
	fseek(pFile, 0, SEEK_END);
	lSize = ftell(pFile);
	rewind(pFile);
	cout << "+ > Filesize: " << lSize << " bytes.\n";

	// allocate memory to contain the whole file:
	buffer = (char*)malloc(sizeof(char) * lSize + 1);
	buffer[lSize] = 0;
	if (buffer == NULL) { fputs("Memory error", stderr); exit(2); }

	// copy the file into the buffer:
	result = fread(buffer, 1, lSize, pFile);
	if (result != lSize) { fputs("Reading error", stderr); exit(3); }


	//cout << "Filedata: \"" << buffer << "\"\n";

	/* the whole file is now loaded in the memory buffer. */

	// terminate
	fclose(pFile);
	free(buffer);





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
	TaskMAAB* maabTask = new TaskMAAB(lSize + 1, (uint8_t*)buffer, testWindow);

	//((NewTerminalInstance*)term->newTermInstance)->Println("This is a test {}!", "LMAO", Colors.bred);

	cout << "\n\n> Running Stuff...\n";

	while (!maabTask->GetDone())
		maabTask->Do();




	cout << "\n\n\nEnd.";
}