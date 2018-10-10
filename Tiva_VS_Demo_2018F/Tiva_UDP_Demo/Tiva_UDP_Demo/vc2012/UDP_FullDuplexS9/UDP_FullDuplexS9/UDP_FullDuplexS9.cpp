// UDP_FullDuplexS9.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

// Two neccessary header files you need to include.
// Place the include for winsock2.h at the beginning of your include statements to avoid a conflict with an older library
#include <winsock2.h>
#include "xPCUDPSock.h"

#pragma pack(push,1) // Important! Tell the compiler to pack things up tightly 

//buffer structure definition
struct PACKIN
{
	float flt1;
	float flt2;
};


struct PACKOUT
{
	float flt1;
	float flt2;
};

#pragma pack(pop) // Fall back to previous setting

int _tmain(int argc, TCHAR* argv[])
{
	int nRetCode = 0;

	// Initialize the UDP lib. If failed, quit running.
	if (!InitUDPLib())
	{
		nRetCode = 2;
	}else
	{
		// Create receiver, with packet size equal to that of PACKIN and port at 12403 or the output port for the Tiva in virtual port 3
		CUDPReceiver receiver(sizeof(PACKIN),12403);

		// Create sender, with packet size equal to that of PACKOUT and port at port is 12302 or input port for the Tiva in virtual port 2, 
		// and remote address 127.0.0.1(localhost)
		CUDPSender sender(sizeof(PACKOUT), 12302,"127.0.0.1");
		
		// Define buffers for input and output
		PACKIN pkin;
		PACKOUT pkout;
		// Routing data endlessly
		while(1)
		{
			// prevent from running to fast
			Sleep(1);
			// get latest data from receiver
			receiver.GetData(&pkin);
			
			// repack the data
			printf("Enter X-Direction (0-Left, 1-Right): ");
			scanf("%f", &pkout.flt1);
			printf("Enter number of steps: ");
			scanf("%f", &pkout.flt2);

			// send the repacked data through sender
			sender.SendData(&pkout);
		}		
	}


	return nRetCode;
}
