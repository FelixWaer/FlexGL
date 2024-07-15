#include "FlexClient.h"

#define DEFAULT_PORT "27015"
#define DEFAULT_BUFLEN 512

ErrMess FlexClient::init_Client()
{
	if (init_WinSock() == FLX_Init_Winsock_Failed)
	{
		std::cout << "Failed initialize Winsock:" << std::endl;
		return FLX_Init_Winsock_Failed;
	}

	ClientRunning = true;
	//choose_UserName();

	return FLX_Init_Winsock_Succeeded;
}

void FlexClient::close_Client()
{
	ClientRunning = false;

	threadObj.join();
	closesocket(ServerSocket);
	WSACleanup();
}

ErrMess FlexClient::Connect_ToServer(std::string IPAddress)
{
	addrinfo* serverAddressInfo = nullptr;
	addrinfo hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	do
	{
		//choose_ServerIpAddress();
		ServerAddress = IPAddress;

		if (get_ServerAddressInfo(&hints, &serverAddressInfo) == FLX_Get_Srv_Adr_Failed)
		{
			serverAddressInfo = nullptr;
			continue;
		}

		if (connect_ToServerSocket(serverAddressInfo) == FLX_Connect_To_Srv_Succeeded)
		{
			break;
		}
		else
		{
			serverAddressInfo = nullptr;
		}
	}
	while (ClientRunning == true);

	int iResult = send(ServerSocket, UserName.c_str(), DEFAULT_BUFLEN, 0);
	if (iResult == SOCKET_ERROR)
	{
		std::cout << "Failed to send: " << WSAGetLastError() << std::endl;

		closesocket(ServerSocket);
		WSACleanup();

		return FLX_Send_Message_Failed;
	}

	ConnectedToServer = true;
	threadObj = std::thread(FlexClient::receive_MessageFromServer, this);

	return FLX_Connect_To_Srv_Succeeded;
}

ErrMess FlexClient::init_WinSock()
{
	int iResult = WSAStartup(MAKEWORD(2, 2), &WinsockData);

	if (iResult != 0)
	{
		std::cout << "WSAStartup failed: " << iResult << std::endl;
		return FLX_Init_Winsock_Failed;
	}
	else
	{
		return FLX_Init_Winsock_Succeeded;
	}
}

ErrMess FlexClient::connect_ToServerSocket(addrinfo* serverAdrInfo)
{
	addrinfo* adrInfoPtr = nullptr;
	if (serverAdrInfo == nullptr)
	{
		std::cout << "Hello world!" << std::endl;
	}

	for (adrInfoPtr = serverAdrInfo; adrInfoPtr != nullptr; adrInfoPtr = adrInfoPtr->ai_next)
	{
		std::cout << "no world!" << std::endl;
		ServerSocket = socket(adrInfoPtr->ai_family, adrInfoPtr->ai_socktype, adrInfoPtr->ai_protocol);
		if (ServerSocket == INVALID_SOCKET)
		{
			std::cout << "Error at connecting socket: " << WSAGetLastError << std::endl;

			freeaddrinfo(serverAdrInfo);
			serverAdrInfo = nullptr;
			return FLX_Connect_To_Srv_Failed;
		}
		
		int connectionResult = connect(ServerSocket, adrInfoPtr->ai_addr, static_cast<int>(adrInfoPtr->ai_addrlen));
		if (connectionResult == SOCKET_ERROR)
		{
			closesocket(ServerSocket);
			ServerSocket = INVALID_SOCKET;
		}
		else
		{
			break;
		}
	}

	freeaddrinfo(serverAdrInfo);
	serverAdrInfo = nullptr;

	if (ServerSocket == INVALID_SOCKET)
	{
		std::cout << "Unable to connect to server!" << std::endl;
		closesocket(ServerSocket);
		return FLX_Connect_To_Srv_Failed;
	}
	else
	{
		return FLX_Connect_To_Srv_Succeeded;
	}
}

ErrMess FlexClient::get_ServerAddressInfo(const addrinfo* adrInfoHints, addrinfo** serverAdrInfo)
{
	int iResult = getaddrinfo(ServerAddress.c_str(), DEFAULT_PORT, adrInfoHints, serverAdrInfo);
	if (iResult != 0)
	{
		std::cout << "Get address info failed: " << iResult << std::endl;
		return FLX_Get_Srv_Adr_Failed;
	}
	else
	{
		return FLX_Get_Srv_Adr_Succeeded;
	}
}

ErrMess FlexClient::send_MessageData(MessageBuffer* messageData)
{
	char dataToSend[512];

	std::memcpy(dataToSend, messageData->Data, sizeof(dataToSend));

	int sendMessageResult = send(ServerSocket, reinterpret_cast<char*>(messageData), DEFAULT_BUFLEN, 0);
	if (sendMessageResult == SOCKET_ERROR)
	{
		std::cout << "Failed to send Message" << std::endl;
		//closesocket(flexClient.ServerSocket);
		//WSACleanup();
		return FLX_Send_Message_Failed;
	}
	else
	{
		return FLX_Send_Message_Succeeded;
	}
}

std::string FlexClient::Message_Type()
{
	MessageBuffer messageBuffer = MessageDataQueue.front();
	//MessageDataQueue.pop();

	char messageTypeBuffer[12];
	std::memcpy(messageTypeBuffer, messageBuffer.Data, 12);
	std::string messageType = messageTypeBuffer;

	return messageType;
}

MessageBuffer FlexClient::receive_Message()
{
	MessageBuffer dataReceived = MessageDataQueue.front();
	MessageDataQueue.pop();
	DataReadyToRetrieve = false;

	return dataReceived;
}

bool FlexClient::data_HasArrived()
{
	if (MessageDataQueue.empty() == false)
	{
		return true;
	}
	else
	{
		return false;
	}
	//if (DataReadyToRetrieve == true)
	//{
	//	DataReadyToRetrieve = false;
	//	return true;
	//}
	//else
	//{
	//	return false;
	//}
}

void FlexClient::choose_UserName()
{
	do
	{
		std::cout << "Input username please" << std::endl;
		std::cin >> UserName;
		std::cout << "\x1B[2J\x1B[H";
	} while (UserName.size() > 10);

	UserName += ": ";
}

void FlexClient::choose_ServerIpAddress()
{
	std::cout << "Hello: " << UserName << std::endl;
	std::cout << "Please write address of the server you want to connect to" << std::endl;

	std::cin >> ServerAddress;
	
	std::cout << "\x1B[2J\x1B[H";
	std::cout << ServerAddress << std::endl;
}

struct Message
{
	char sentence[500];
};

void FlexClient::receive_MessageFromServer(FlexClient* client)
{
	int iResult;
	int receiveBuffLength = DEFAULT_BUFLEN;
	MessageBuffer messageBuffer;

	while (client->ConnectedToServer == true)
	{
		iResult = recv(client->ServerSocket, messageBuffer.Data, receiveBuffLength, 0);
		if (iResult > 0)
		{
			client->MessageDataQueue.emplace(messageBuffer);
			client->DataReadyToRetrieve = true;
		}
	}
}
