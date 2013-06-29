#include "visit.hh"

#include "servey.hh"

#include <koohar.hh>
#include <oodb.hh>

using namespace koohar;
using namespace oodb;
using namespace std;

namespace doctor {

void Visit::process (Request& Req, Response& Res, Db& db)
{
	m_req = &Req;
	m_res = &Res;
	m_db = &db;
	load();
}

// private

void Visit::load ()
{
	if (m_req->contains("new"))
		saveNew();
	else if (m_req->contains("all"))
		sendAll();
	else
		m_res->badRequest();
}

void Visit::saveNew ()
{
	Servey servey(*m_db);
	bool succ = servey.add(
		m_req->body("type"),
		m_req->body("date"),
		m_req->body("sender"),
		m_req->body("dynamic"),
		m_req->body("login"),
		m_req->body("patient"),
		m_req->body("machine"),
		m_req->body("detectors"),
		m_req->body("diagnosis"),
		m_req->body("data")
	);
	
	m_res->writeHead(200);
	m_res->header("Content-Type", "text/plain");
	m_res->end(succ ? "success" : servey.error());
}

void Visit::sendAll ()
{
	ServeyList serveys;
	Servey::all(*m_db, serveys);

	JSON::Object send_data;

	for (auto it = serveys.begin(); it != serveys.end(); ++it) {
		JSON::Object visit;
		visit["type"] = it->type();
		visit["date"] = it->date();
		visit["dynamic"] = it->dynamic();
		visit["patient"] = it->patient();
		visit["diagnosis"] = it->diagnosis();
		visit["data"] = it->data();
		visit["key"] = it->key();
		send_data["visits"].addToArray(visit);
	}
	m_res->sendJSON(send_data);
}

} // namespace doctor
