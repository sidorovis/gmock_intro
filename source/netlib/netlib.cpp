#include "netlib.h"

#include <string>

using namespace netlib;

char* network::create_packet(const size_t size) {
	return new char[size];
}

network::network() {
}

network::~network() {
}

net_protocol::net_protocol(network& n)
	: _n(n) {

}
void net_protocol::connect(const std::string& password) {
	if (!_n.send_packet(password.c_str(), password.size()))
		throw std::logic_error("connect: send packet failed");
	size_t s;
	const char* const answer = _n.get_packet(&s);
	if (std::string(answer, s) != "world") {
		throw std::logic_error("connect: bad answer");
	}
}
void net_protocol::heartbeat() {
	if (!_n.send_packet("heartbeat", 9)) {
		throw std::logic_error("heartbeat: send packet failed");
	}
}

void net_protocol::disconnect() {
	_n.send_packet("bye", 3);
	size_t s;
	const char* const answer = _n.get_packet(&s);
	if (std::string(answer, s) != "baby") {
		throw std::logic_error("disconnect: bad answer");
	}
}
