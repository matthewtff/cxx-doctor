#include "machine.hh"

#include <koohar.hh>
#include <oodb.hh>

#include "device.hh"

using namespace koohar;
using namespace oodb;
using namespace std;

namespace doctor {

Machine::CallbackMap Machine::initCallbacks ()
{
	Machine::CallbackMap callbacks;
	callbacks["new"] = &Machine::saveNew;
	callbacks["all"] = &Machine::sendAll;
	callbacks["rem"] = &Machine::remove;
	callbacks["change"] = &Machine::change;
	return callbacks;
}

Machine::CallbackMap Machine::m_callbacks = Machine::initCallbacks();

const std::string Machine::m_commands[] = {
	"new",
	"all",
	"rem",
	"change"
};

void Machine::process (Request& Req, Response& Res, Db& db)
{
	m_req = &Req;
	m_res = &Res;
	m_db = &db;
	load();
}

//private

void Machine::load ()
{
	for (size_t counter = 0; counter < m_callbacks.size(); ++counter)
		if (m_req->contains(m_commands[counter]))
			return (this->*m_callbacks[m_commands[counter]]) ();
	m_res->badRequest();
}

void Machine::saveNew ()
{
	Device device(*m_db);
	bool succ = device.add(m_req->body("name"), m_req->body("info"));

	m_res->writeHead(200);
	m_res->header("Content-Type", "text/plain");
	m_res->end(succ ? "success" : device.error());
}

void Machine::sendAll ()
{
	JSON::Object send_data;

	DeviceList all;
	Device::all(*m_db, all);
	for (auto it = all.begin(); it != all.end(); ++it) {
		JSON::Object device;
		device["name"] = it->name();
		device["info"] = JSON::parse(it->info());
		send_data["machines"].addToArray(device);
	}
	m_res->sendJSON(send_data);
}

void Machine::remove ()
{
	Device device(*m_db);
	bool succ = device.remove(m_req->body("name"));

	m_res->writeHead(200);
	m_res->header("Content-Type", "text/plain");
	m_res->end(succ ? "success" : device.error());
}

void Machine::change ()
{
	Device device(*m_db);
	bool succ = device.change(m_req->body("prev_name"), m_req->body("name"),
		m_req->body("info"));
	
	m_res->writeHead(200);
	m_res->header("Content-Type", "text/plain");
	m_res->end(succ ? "success" : device.error());
}

} // namespace doctor
