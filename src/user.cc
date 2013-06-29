#include "user.hh"

#include <list>
#include <string>
#include <sstream>

#include "medic.hh"

using namespace koohar;
using namespace oodb;
using namespace std;

namespace doctor {

User::CallbackMap User::initCallbacks ()
{
	CallbackMap callbacks;
	callbacks["register"] = &User::reg;
	callbacks["all"] = &User::list;
	callbacks["remove"] = &User::remove;
	callbacks["get"] = &User::get;
	return callbacks;
}

User::CallbackMap User::m_callbacks = User::initCallbacks();

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
	for (CallbackMap::iterator callback = m_callbacks.begin();
		callback != m_callbacks.end(); ++callback)
	{
		if (m_req->contains(callback->first))
			return (this->*(callback->second))();
	}
	m_res->badRequest();
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

void User::get ()
{
	Medic medic(*m_db);
	const bool success = medic.load(m_req->body("login"),
		m_req->body("password"));
	if (!success)
		m_res->badRequest();

	JSON::Object user_json;
	user_json["login"] = medic.login();
	user_json["name"] = medic.name();
	user_json["surname"] = medic.surname();
	user_json["second_name"] = medic.second_name();
	user_json["category"] = medic.category();
	m_res->writeHead(200);
	m_res->end(user_json.toString());
}

} // namespace doctor
