#include "Chat.h"

using namespace std;
const char SERVER_IP[] = "10.211.55.3";					
const short SERVER_PORT_NUM = 4700;				
const short BUFF_SIZE = 1024;					
int erStat;

void Chat::start() {

	in_addr ip_to_num;
	inet_pton(AF_INET, SERVER_IP, &ip_to_num);

	// WinSock initialization
	WSADATA wsData;
	erStat = WSAStartup(MAKEWORD(2, 2), &wsData);

	if (erStat != 0) {
		std::cout << "Error WinSock version initializaion #";
		cout << WSAGetLastError();
	}
	else
		cout << "WinSock initialization is OK" << endl;

//инициализация сокета
	SOCKET ClientSock = socket(AF_INET, SOCK_STREAM, 0);

	if (ClientSock == INVALID_SOCKET) {
		cout << "Error initialization socket # " << WSAGetLastError() << endl;
		closesocket(ClientSock);
		WSACleanup();
	}
	else
		cout << "Client socket initialization is OK" << endl;
	sockaddr_in servInfo;

	ZeroMemory(&servInfo, sizeof(servInfo));

	servInfo.sin_family = AF_INET;
	servInfo.sin_addr = ip_to_num;
	servInfo.sin_port = htons(SERVER_PORT_NUM);

	erStat = connect(ClientSock, (sockaddr*)&servInfo, sizeof(servInfo));

	if (erStat != 0) {
		cout << "Connection to Server is FAILED. Error # " << WSAGetLastError() << endl;
		closesocket(ClientSock);
		WSACleanup();
	}
	else
		cout << "Connection established SUCCESSFULLY. Ready to send a message to Server" << endl;



	std::cout << "Welcome to Chat!" << std::endl;

	while (true)
	{
		vector <char> servBuff(BUFF_SIZE), clientBuff(BUFF_SIZE);							// Buffers for sending and receiving data
		short packet_size = 0;
		std::cout << std::endl;
		std::cout << "Select an Action: \n1 - Enter.\n2 - New User Registration \n0 - Exit" << std::endl;
		fgets(servBuff.data(), servBuff.size(), stdin);
		packet_size = send(ClientSock, servBuff.data(), servBuff.size(), 0);
		string f = servBuff.data();
		f.pop_back();
		if (f == "2"){
			cout << "REGISTRATION" << endl;
			cout << "NAME?" << endl;
			fgets(servBuff.data(), servBuff.size(), stdin);
			packet_size = send(ClientSock, servBuff.data(), servBuff.size(), 0);

			cout << "LOGIN?" << endl;
			fgets(servBuff.data(), servBuff.size(), stdin);
			packet_size = send(ClientSock, servBuff.data(), servBuff.size(), 0);
			cout << "PASS?" << endl;
			fgets(servBuff.data(), servBuff.size(), stdin);
			packet_size = send(ClientSock, servBuff.data(), servBuff.size(), 0);
			continue;
		}
		if (f == "1") {
			cout << "ENTER" << endl;
			cout << "LOGIN?" << endl;
			fgets(servBuff.data(), servBuff.size(), stdin);
			packet_size = send(ClientSock, servBuff.data(), servBuff.size(), 0);

			cout << "PASS?" << endl;
			fgets(servBuff.data(), servBuff.size(), stdin);
			packet_size = send(ClientSock, servBuff.data(), servBuff.size(), 0);

		}
		packet_size = recv(ClientSock, clientBuff.data(), clientBuff.size(), 0);
		string s;
		s = clientBuff[0];
		if (s == "0") { cout << "incorrect log or pass" << endl; }

		if (s == "1") { cout << "Welcome to chat" << endl; }
		{
			
				while (true)
				{
					std::cout << std::endl;
					//выбор пользователем желаемого действия
					std::cout << "Select an Action: " << std::endl;
					std::cout << "1 - Read Incoming Messages" << std::endl;
					std::cout << "2 - Write a message" << std::endl;
					std::cout << "0 - Exit" << std::endl;
					char c;
					fgets(servBuff.data(), servBuff.size(), stdin);
					packet_size = send(ClientSock, servBuff.data(), servBuff.size(), 0);
					c = servBuff[0];
					if (c == '0')
					{
						servBuff.clear();
						break;
					}

					if (c == '1') {
						cout << "Messages for you:" << endl;
						packet_size = recv(ClientSock, clientBuff.data(), clientBuff.size(), 0);
						cout << clientBuff.data();
						cout << endl;
						
						
					}

					if (c == '2') {
						cout << "Выберите кому отправить сообщение:" << endl;
						cout << "users in chat: " << endl;

						packet_size = recv(ClientSock, clientBuff.data(), clientBuff.size(), 0);
						cout << clientBuff.data();
						cout << endl;
						servBuff = {'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1' };

						cout << "Введите имя" << endl;

						cout << "ucer?" << endl;
						fgets(servBuff.data(), servBuff.size(), stdin);
						packet_size = send(ClientSock, servBuff.data(), servBuff.size(), 0);
						cout << servBuff.data() << endl;
						cout << "text?" << endl;
						//string h;
						//std::getline(std::cin, h, '\n');
						fgets(servBuff.data(), servBuff.size(), stdin);
						cout << servBuff.data() << endl;
						packet_size = send(ClientSock, servBuff.data(), servBuff.size(), 0);

						cout << "Meesage sended" << endl;

					}
				}
			}	
	}

	closesocket(ClientSock);
	WSACleanup();

	}
