#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <iostream>

using namespace std;

const int PORT_NO = 1397;

bool connect() {
	int s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == -1)
		return false;
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(PORT_NO);
	if (bind(s, (sockaddr*)&addr, sizeof(addr)) == -1)
		return false;
	listen(s, 10);

	return true;
}

int main() {
	if (!connect()) {
		cout << "Failed to connect" << endl;
	}
	return 0;
}
