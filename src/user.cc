#include "user.hh"

#include <list>
#include <string>
#include <sstream>

#include "medic.hh"

using namespace koohar;
using namespace oodb;
using namespace std;

namespace doctor {

void User::process (Request& Req, Response& Res, Db& db)
{
	m_db = &db;
	m_req = &Req;
	m_res = &Res;
	load();
}

// private

void User::load ()
{
	if (m_req->contains("register"))
		reg();
	else if (m_req->contains("all"))
		list();
	else if (m_req->contains("remove"))
		remove();
	else {
		m_res->writeHead(400);
		m_res->end();
	}
}

void User::reg ()
{
	Medic medic(*m_db);
	const bool success = medic.reg(
		m_req->body("login"),
		m_req->body("password"),
		m_req->body("password_confirm"),
		m_req->body("name"),
		m_req->body("surname"),
		m_req->body("second_name"),
		m_req->body("category")
	);

	m_res->writeHead(200);
	m_res->header("Content-Type", "text/plain");
	m_res->end(success ? "success" : medic.error());
}

void User::list ()
{
	std::list<std::string> medics = Medic::list(*m_db);
	m_res->writeHead(200);
	m_res->header("Content-Type", "application/json");
	std::stringstream medics_json;
	medics_json << "{\"medics\":[";
	for (auto medic = medics.begin(); medic != medics.end(); ++medic) {
		if (medic != medics.begin())
			medics_json << ",";
		medics_json << "\"" << *medic << "\"";
	}
	medics_json << "]}";
	m_res->end(medics_json.str());
}

void User::remove ()
{
	const bool success = Medic::remove(*m_db, m_req->body("login"));
	m_res->writeHead(200);
	m_res->header("Content-Type", "text/plain");
	m_res->end(success ? "success" : "Medic not found");
}

} // namespace doctor
