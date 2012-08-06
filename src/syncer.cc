#include "syncer.hh"

#include <koohar/socket.hh>
#include <koohar/file.hh>

using namespace std;

namespace doctor {

void sendHeader (koohar::Socket::Handle sock, oodb::Db& db);

bool syncronizeDb (oodb::Db& db, const string& ip, const short port)
{
	koohar::Socket sock(false, true); // Syncronious, ipv4
	if (!sock.connect(ip, port))
		return false;
	
	sendHeader(sock.fd(), db);

	return true;
}

void sendHeader (koohar::Socket::Handle sock, oodb::Db& db)
{
}

} // namespace doctor
