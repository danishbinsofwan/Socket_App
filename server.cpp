
#pragma warning(disable:4496)
#include <WinSock2.h>
#include <Windows.h>
#include <stdio.h>
#include <iostream>
using namespace std;


#pragma comment(lib, "Ws2_32.lib")
#define Port 6000

SOCKET Socket, Sub;
WSADATA Winsock;
sockaddr_in Addr;
sockaddr_in IncomingAddress;
int AddressLen = sizeof(IncomingAddress);

int main()
{
	printf("Server Side Running on Port 6000\n");
	WSAStartup(MAKEWORD(2, 2), &Winsock);    // Start Winsock

	if (LOBYTE(Winsock.wVersion) != 2 || HIBYTE(Winsock.wVersion) != 2)    // Check version
	{
		WSACleanup();
		return 0;
	}

	Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	ZeroMemory(&Addr, sizeof(Addr));
	Addr.sin_family = AF_INET;
	Addr.sin_port = htons(Port);
	bind(Socket, (sockaddr*)&Addr, sizeof(Addr));

	if (listen(Socket, 1) == SOCKET_ERROR)
	{
		printf("listening error\n");
	}
	else
	{
		printf("Server Listening start your client\n");
	}

	if (Sub = accept(Socket, (sockaddr*)&IncomingAddress, &AddressLen))
	{
		char *ClientIP = inet_ntoa(IncomingAddress.sin_addr);
		int ClientPort = ntohs(IncomingAddress.sin_port);
		printf("Client conncted!\n");
		printf("IP: %s:%d\n", ClientIP, ClientPort);

		printf("Sending file .. \n");

		FILE *File, *fis;
		char *Buffer;
		long Size;

		fopen_s(&File, "D:\eminem.txt", "r");

		if (!File)
		{
			printf("Error while readaing the file\n");
			getchar();
			return 0;
		}

		fseek(File, 0, SEEK_END);
		Size = ftell(File);
		fseek(File, 0, SEEK_SET);

		Buffer = new char[Size];

		fread(Buffer, Size, 1, File);
		char cSize[MAX_PATH];
		sprintf_s(cSize, "%i", Size);

		fclose(File);
		send(Sub, cSize, MAX_PATH, 0); // File size

		//int len = Size;
		//char *data = Buffer;

		int Offset = 0;
		while (Size > Offset)
		{
			int Amount = send(Sub, Buffer + Offset, Size - Offset, 0);

			if (Amount <= 0)
			{
				cout << "Error: " << WSAGetLastError() << endl;
				break;
			}
			else
			{
				Offset += Amount;
				printf("Done\n");
			}
		}


		free(Buffer);
		closesocket(Sub);
		closesocket(Socket);
		WSACleanup();
	}

	getchar();
	return 0;
}
