#include "machine.hh"

#include <sstream>

#include "device.hh"

using namespace koohar;
using namespace oodb;
using namespace std;

namespace doctor {

Machine::Machine (Request& Req, Response& Res, Db& db) : m_req(Req), m_res(Res),
	m_db(db)
{
	load();
}

//private

void Machine::load ()
{
	if (m_req.contains("new"))
		saveNew();
	else if (m_req.contains("all"))
		sendAll();
	else {
		m_res.writeHead(200);
		m_res.end();
	}
}

void Machine::saveNew ()
{
	Device device(m_db);
	bool succ = device.add(m_req.body("name"), m_req.body("info"));

	m_res.writeHead(200);
	m_res.header("Content-Type", "text/plain");
	m_res.end(succ ? "success" : device.error());
}

void Machine::sendAll ()
{
	stringstream send_data;
	send_data << "{\"machines\":[";

	DeviceList all;
	Device::all(m_db, all);
	for (auto it = all.begin(); it != all.end(); ++it) {
		if (it != all.begin())
			send_data << ",";
		send_data << "{\"name\":\"" << it->name() << "\",";
		send_data << "\"info\":\"" << it->info() << "\"}";
	}

	send_data << "]}";

	m_res.writeHead(200);
	m_res.header("Content-Type", "application/json");
	m_res.end(send_data.str());
}

} // namespace doctor
