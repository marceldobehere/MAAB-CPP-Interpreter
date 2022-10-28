#include "maabTask.h"
//#include "../../kernelStuff/other_IO/pit/pit.h"
#include "heap.h"
//#include "../../interrupts/interrupts.h"
#include "cstrTools.h"
//#include "../../OSDATA/MStack/MStackM.h"
#include "terminalInstance.h"
#include "cstr.h"

TaskMAAB::TaskMAAB(uint32_t codeLen, uint8_t* code, Window* window, TerminalInstance* term)
{
	this->window = window;
	dTerm = term;
	newTerm = (NewTerminalInstance*)(term->newTermInstance);


	this->code = (uint8_t*)malloc(codeLen);
	for (int i = 0; i < codeLen; i++)
		this->code[i] = code[i];
	this->codeLen = codeLen;


	memLen = 2000000;
	this->mem = (uint8_t*)malloc(memLen);
	for (int i = 0; i < memLen; i++)
		mem[i] = 0;



	newTerm->Println("Data:");
	for (int i = 0; i < this->codeLen; i++)
	{
		mem[i] = this->code[i];
		newTerm->Print("{} ", to_string(mem[i]), defCol);
	}
	newTerm->Println();

	waitInput = false;
	done = false;
	type = TaskType::BF;


	instrPointer = 0;
	errMsg = "<NO ERRORS>";
	errCode = 0;


	((TerminalInstance*)window->instance)->userlen = 0;
	((TerminalInstance*)window->instance)->takeInput = false;
	waitInput = false;
	newTerm->Println("<TASK STARTED!>");
	defCol = Colors.white;
}

void TaskMAAB::Do()
{
	if (waitInput)
		return;

	if (instrPointer >= memLen)
	{
		done = true;
		errCode = 1;
		errMsg = "INSTRUCTION POINTER OUT OF BOUNDS!";
	}

	for (int sI = 0; sI < cyclesPerCall; sI++)
	{
		if (waitInput)
			return;


		uint8_t instr = mem[instrPointer];

		if (instr == 0) //nop
		{
			instrPointer++;
		}
		else if (instr == 1) //exit
		{
			done = true;
			errCode = 0;
			return;
		}
		else if (instr == 2) //set fix mem to fix val
		{
			if (instrPointer + 9 >= memLen)
			{
				done = true;
				errCode = 1;
				errMsg = "INSTRUCTION OUT OF BOUNDS!";
				return;
			}
			uint8_t copySize = mem[instrPointer + 1];
			uint64_t copyAddr = (uint64_t)((void*)mem[instrPointer + 2]);

			if (instrPointer + 10 + copySize >= memLen)
			{
				done = true;
				errCode = 1;
				errMsg = "INSTRUCTION OUT OF BOUNDS!";
				return;
			}
			if (copyAddr + copySize >= memLen)
			{
				done = true;
				errCode = 1;
				errMsg = "ADDR OUT OF BOUNDS!";
				return;
			}

			//newTerm->Print("<COPY {} BYTES TO ADDR ", to_string(copySize), defCol);
			//newTerm->Println("{}>", to_string(copyAddr), defCol);


			for (int i = 0; i < copySize; i++)
			{
				//newTerm->Println("<COPY {}>", to_string(mem[instrPointer + 10 + i]), defCol);
				mem[copyAddr + i] = mem[instrPointer + 10 + i];
			}



			instrPointer += 10 + copySize;
		}
		else if (instr == 20) //jump
		{
			if (instrPointer + 8 >= memLen)
			{
				done = true;
				errCode = 1;
				errMsg = "INSTRUCTION OUT OF BOUNDS!";
				return;
			}
			uint64_t jumpAddr = (uint64_t)((void*)mem[instrPointer + 1]);

			instrPointer = jumpAddr;
		}









		else if (instr == 50) //syscall
		{
			if (instrPointer + 2 >= memLen)
			{
				done = true;
				errCode = 1;
				errMsg = "INSTRUCTION OUT OF BOUNDS!";
				return;
			}
			uint8_t syscall1 = (uint64_t)((void*)mem[instrPointer + 1]);
			uint8_t syscall2 = (uint64_t)((void*)mem[instrPointer + 2]);

			if (syscall1 == 1)
			{
				if (syscall2 == 1)
				{
					uint8_t byteToPrint = (uint64_t)((void*)mem[instrPointer + 3]);
					newTerm->Print((char)byteToPrint);
					instrPointer += 4;
				}
				/*else if (syscall2 == 2)
				{

				}*/
				else if (syscall2 == 3)
				{
					uint64_t printAddr = (uint64_t)((void*)mem[instrPointer + 3]);
					//newTerm->Println("<PRINTING STR AT {}>", to_string(printAddr), defCol);
					for (int i = 0; printAddr + i < memLen && mem[printAddr + i] != 0; i++)
					{
						newTerm->Print((char)mem[printAddr + i]);
					}
					instrPointer += 11;
				}

				else
				{
					done = true;
					errCode = 1;
					errMsg = "CONSOLE SYSCALL IS NOT SUPPORTED";
					return;
				}
			}

			else
			{
				done = true;
				errCode = 1;
				errMsg = "SYSCALL IS NOT SUPPORTED";
				return;
			}

			//uint64_t jumpAddr = (uint64_t)((void*)mem[instrPointer + 1]);

			//instrPointer = jumpAddr;
		}



		else
		{
			newTerm->Println("<INVALID OPCODE: {}!>\n", to_string(instr), defCol);
			instrPointer++;
		}

	}



}




void TaskMAAB::Free()
{
	free((void*)code);
	free((void*)mem);
}