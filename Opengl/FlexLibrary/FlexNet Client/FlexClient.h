#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define  WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <iphlpapi.h>

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Mswsock.lib")
#pragma comment(lib, "AdvApi32.lib")

#include <iostream>
#include <queue>
#include <string>
#include <thread>

#include "ErrorHandler.h"

struct MessageBuffer
{
	char Data[512];
};

template <typename T>
MessageBuffer convert_ToMessageData(const T* dataToConvert, const std::string& dataInfo)
{
	MessageBuffer tempMessageData;

	std::memcpy(&tempMessageData.Data, dataInfo.c_str(), 12);
	//int index = strlen(dataInfo.c_str());
	//while (index < 12)
	//{
	//	tempMessageData.DataInfo[index] = ' ';
	//	index++;
	//}
	std::memcpy(&tempMessageData.Data[12], dataToConvert, 500);

	return tempMessageData;
}

template <typename T>
T convert_FromMessageData(const MessageBuffer* messageDataToConvert)
{
	T convertedData;
	std::memcpy(&convertedData, &messageDataToConvert->Data[12], sizeof(T));

	return convertedData;
}

class FlexClient
{
public:
	FlexClient() = default;

	std::string UserName = "Guest";

	ErrMess init_Client();
	void close_Client();
	ErrMess Connect_ToServer(std::string IPAddress = "localhost");
	ErrMess send_MessageData(MessageBuffer* messageData);
	SOCKET ServerSocket = INVALID_SOCKET;
	std::string Message_Type();
	MessageBuffer receive_Message();
	bool data_HasArrived();

	static void receive_MessageFromServer(FlexClient* client);
private:
	WSADATA WinsockData;
	std::string ServerAddress;
	std::thread threadObj;
	std::queue<MessageBuffer> MessageDataQueue;
	bool ClientRunning = false;
	bool ConnectedToServer = false;
	bool DataReadyToRetrieve = false;

	ErrMess init_WinSock();
	ErrMess connect_ToServerSocket(addrinfo* serverAdrInfo);
	ErrMess get_ServerAddressInfo(const addrinfo* adrInfoHints, addrinfo** serverAdrInfo);
	void choose_UserName();
	void choose_ServerIpAddress();
};

