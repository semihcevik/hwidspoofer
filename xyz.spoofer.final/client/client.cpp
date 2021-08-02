#include "..\client\common.h"
#include "..\client\client.h"

#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib,"ws2_32.lib")

#include <sstream>

#include "..\hwid.h"

#define PORT 8001
#define SERVERIP _xor_("213.238.179.107")
std::string VERSION = _xor_("0.0.5");
std::string ENC_KEY = _xor_("bd1373c8647a990967e63515733f31b2");
std::string IV = _xor_("925a28e64f7c1216f6");
sockaddr_in serv_addr;

Client::Client() {
	WSADATA data; WORD ver = MAKEWORD(2, 2);
	INT WSResult = WSAStartup(ver, &data);

	if (WSResult != 0) {
		return;
	}

	m_sock = socket(AF_INET, SOCK_STREAM, 0);

	if (m_sock == INVALID_SOCKET) {
		WSACleanup();
		return;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	inet_pton(AF_INET, SERVERIP.c_str(), &serv_addr.sin_addr);
	connected = reconnect();

	if (connected) setup = setupEncryption();
}

Client::~Client() {
	if (m_sock != INVALID_SOCKET) {
		closesocket(m_sock);
		WSACleanup();
	}
}

bool Client::reconnect() {
	if (m_sock != INVALID_SOCKET) {
		int connResult = connect(m_sock, (sockaddr*)&serv_addr, sizeof(serv_addr));
		if (connResult == SOCKET_ERROR) {
			closesocket(m_sock);
			WSACleanup();
		}
		else {
			return true;
		}
	}
	return false;
}

std::string Client::sendrecieve(const std::string& text) {
	if (m_sock != INVALID_SOCKET && connected) {
		char buf[4024];
		int sendresult = send(m_sock, text.c_str(), text.size(), 0);
		if (sendresult != SOCKET_ERROR) {
			ZeroMemory(buf, 4024);
			int bytesRec = recv(m_sock, buf, 4024, 0);
			if (bytesRec > 0) {
				return std::string(buf, 0, bytesRec);
			}
		}
		else if (reconnect()) {
			return sendrecieve(text);
		}
	}
	return "";
}
int f = 0;

void ERRORLOG(std::string message) {
	std::cout << message << std::endl;
	system(_xor_("pause").c_str());
	exit(0);
}

template< typename ... Args >
std::string stringer(Args const& ... args)
{
	std::ostringstream stream;
	using List = int[];
	(void)List {
		0, ((void)(stream << args), 0) ...
	};
	return stream.str();
}

bool Client::setupEncryption() {
	std::string SetupKey = sendrecieve(ENC_KEY + _xor_(";") + IV);
	std::string serverCipher = SetupKey.substr(0, SetupKey.find(_xor_(";"))).data();
	std::string serverIv = SetupKey.substr(SetupKey.find(_xor_(";")) + 1).data();

	if (ENC_KEY == serverCipher) {
		if (IV == serverIv) {
			// Client-Server authentication success
			std::string ServerVersion = sendrecieve(VERSION);
			// Check version control:
			if (VERSION == ServerVersion) {
				std::string successGetUsername = _xor_("SUCCESS_GET_USERNAME");
				std::string getUsername = sendrecieve(stringer(_xor_("SPOOFER_GET_USERNAME;"), getHWinfo64()));
				if (getUsername.size() == successGetUsername.size()) return true;
				else ERRORLOG(_xor_("ERROR 3131"));
			}
			else ERRORLOG(_xor_("ERROR 103"));
		}
		else ERRORLOG(_xor_("ERROR 102"));
	}
	else ERRORLOG(_xor_("ERROR 101"));
}

char* Client::decyptBuffer(char* buffer, int length)
{
	std::string ss(buffer, length);
	std::string decryptedString;// = decrypt(ss);
	ss.clear();

	char* finalBuffer = new char[decryptedString.size()];

	std::copy(decryptedString.begin(), decryptedString.end(), finalBuffer);
	std::cout << finalBuffer;

	decryptedString.clear();
	delete[] buffer;
	return finalBuffer;
}

std::unique_ptr<Client> m_Client;