#include "insurance.hh"

#include <sstream>

using namespace koohar;
using namespace oodb;
using namespace std;

namespace doctor {

const std::string Insurance::m_prefix = "insurance";

Insurance::Insurance (Request& Req, Response& Res, Db& db) :
	m_req(Req), m_res(Res), m_db(db)
{
	load ();
}

// private

void Insurance::load ()
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

void Insurance::saveNew ()
{
	std::string msg;
	const std::string& name = m_req.body("name");
	if (name.empty())
		msg = "Wrong data.";
	else {
		if (m_db.checkSet(m_prefix, name))
			msg = "Insurance already exists.";
		else {
			m_db.addSet(m_prefix, name);
			msg = "success";
		}
	}

	m_res.writeHead(200);
	m_res.header("Content-Type", "plain/text");
	m_res.end(msg);
}

void Insurance::sendAll ()
{
	stringstream send_data;
	send_data << "{\"insurances\":[";

	Set& all = m_db.getSet(m_prefix);
	for (auto it = all.begin(); it != all.end(); ++it) {
		if (it != all.begin())
			send_data << ",";
		send_data  << "\"" << *it << "\"";
	}
	send_data << "]}";
	
	m_res.writeHead(200);
	m_res.header("Content-Type", "application/json");
	m_res.end(send_data.str());
}

} // namespace doctor
