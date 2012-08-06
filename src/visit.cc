#include "visit.hh"

#include <sstream>

#include "servey.hh"

using namespace koohar;
using namespace oodb;
using namespace std;

namespace doctor {

Visit::Visit (Request& Req, Response& Res, Db& db) : m_req(Req), m_res(Res),
	m_db(db)
{
	load();
}

// private

void Visit::load ()
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

void Visit::saveNew ()
{
	Servey servey(m_db);
	bool succ = servey.add(
		m_req.body("type"),
		m_req.body("date"),
		m_req.body("sender"),
		m_req.body("dynamic"),
		m_req.body("login"),
		m_req.body("patient"),
		m_req.body("machine"),
		m_req.body("detectors"),
		m_req.body("diagnosis"),
		m_req.body("data")
	);
	
	m_res.writeHead(200);
	m_res.header("Content-Type", "text/plain");
	m_res.end(succ ? "success" : servey.error());
}

void Visit::sendAll ()
{
	ServeyList serveys;
	Servey::all(m_db, serveys);
	stringstream send_data;
	send_data << "{\"visits\":[";
	for (auto it = serveys.begin(); it != serveys.end(); ++it) {
		if (it != serveys.begin())
			send_data << ",";
		send_data << "{\"type\":\"" << it->type() << "\",";
		send_data << "\"date\":\"" << it->date() << "\",";
		send_data << "\"dynamic\":\"" << it->dynamic() << "\",";
		send_data << "\"patient\":\"" << it->patient() << "\",";
		send_data << "\"diagnosis\":\"" << it->diagnosis() << "\",";
		send_data << "\"data\":\"" << it->data() << "\",";
		send_data << "\"key\":\"" << it->key() << "\"}";
	}
	send_data << "]}";
	
	m_res.writeHead(200);
	m_res.header("Content-Type", "application/json");
	m_res.end(send_data.str());
}

} // namespace doctor
