#pragma once
#include <iostream>
#include <string>
#include <filesystem>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <inaddr.h>
#include <stdio.h>
#pragma comment(lib, "ws2_32.lib")

class Chat
{
public:
	
	Chat() = default;
	~Chat() = default;

	void start();
};
