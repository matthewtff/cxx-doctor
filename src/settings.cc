#include "settings.hh"

#include <sstream>

#include <iostream>

using namespace koohar;
using namespace oodb;
using namespace std;

namespace doctor {

const string Settings::m_prefix = "settings";

void Settings::process (Request& Req, Response& Res, Db& db)
{
	m_req = &Req;
	m_res = &Res;
	m_db = &db;
	load ();
}

// private

void Settings::load ()
{
	if (m_req->contains("get"))
		get();
	else if (m_req->contains("set"))
		set();
	else {
		m_res->writeHead(400);
		m_res->end();
	}
}

void Settings::set ()
{
	std::string msg = "success";
	const std::string& settings = m_req->body("settings");
	if (settings.empty())
		msg = "Wrong data.";
	else
		m_db->setString(m_prefix, settings);

	m_res->writeHead(200);
	m_res->header("Content-Type", "plain/text");
	m_res->end(msg);
}

void Settings::get ()
{
	stringstream send_data;
	string settings = m_db->getString(m_prefix);
	send_data << (settings.empty() ? "{\"empty\":\"true\"}" : settings);

	m_res->writeHead(200);
	m_res->header("Content-Type", "application/json");
	m_res->end(send_data.str());
}

} // namespace doctor
