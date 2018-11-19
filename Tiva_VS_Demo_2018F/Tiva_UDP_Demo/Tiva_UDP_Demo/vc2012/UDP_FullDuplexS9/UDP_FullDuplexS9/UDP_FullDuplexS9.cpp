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
	float flt3;
	float flt4;
	float flt5;
	float flt6;
};


struct PACKOUT
{
	float flt1;
	float flt2;
	float flt3;
	float flt4;
	float flt5;
	float flt6;
};

#pragma pack(pop) // Fall back to previous setting

int _tmain(int argc, TCHAR* argv[])
{
	int nRetCode = 0;
	int wait = 0;

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
			printf("X: %.2f,%.2f, Steps: %.2f\r\n", pkin.flt1, pkin.flt2, pkin.flt3);
			printf("Y: %.2f %.2f Steps: %.2f \r\n", pkin.flt3, pkin.flt4, pkin.flt6);
			
			// repack the data

			/* X-DIRECTION */
			printf("Enter X-Direction (0-Left, 1-Right, 2-Stop): ");
			scanf("%f", &pkout.flt1);
			if (pkout.flt1 == 1)
			{
				pkout.flt2 = 0;
			}
			else if (pkout.flt1 == 0)
			{
				pkout.flt2 = 1;
			}
			else
			{
				pkout.flt2 = pkout.flt1;
			}
			printf("Enter number of steps for X: ");
			scanf("%f", &pkout.flt3);
			
			/* Y-DIRECTION */
			printf("Enter Y-Direction (0-Forward, 1-Backward, 2-Stop): ");
			scanf("%f", &pkout.flt4);
			if (pkout.flt4 == 1)
			{
				pkout.flt5 = 0;
			}
			else if (pkout.flt4 == 0)
			{
				pkout.flt5 = 1;
			}
			else
			{
				pkout.flt5 = pkout.flt4;
			}
			printf("Enter number of steps for Y: ");
			scanf("%f", &pkout.flt6);

			// send the repacked data through sender
			sender.SendData(&pkout);

			if (pkout.flt3 > pkout.flt6)
			{
				wait = 25 * (pkout.flt3);
			}
			else
			{
				wait = 25 * (pkout.flt6);
			}
			/*
			Sleep(wait);

			pkout.flt1 = 2;
			pkout.flt2 = 2;
			pkout.flt3 = 0; // steps
			pkout.flt4 = 2;
			pkout.flt5 = 2;
			pkout.flt6 = 0; // steps
			sender.SendData(&pkout);*/

		}		
	}


	return nRetCode;
}
