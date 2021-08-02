#pragma once
#include <iostream>
class Client
{
public:
	Client();
	~Client();
	std::string sendrecieve(const std::string& s);
	bool isSetup() {
		return setup;
	};
private:
	int m_sock = 0;
	bool reconnect();
	char* decyptBuffer(char* buffer, int length);
	bool setupEncryption();
	bool connected = false;
	bool setup = false;
};

extern std::unique_ptr<Client> m_Client;