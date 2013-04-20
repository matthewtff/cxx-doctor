#include "insurance.hh"

using namespace koohar;
using namespace oodb;
using namespace std;

namespace doctor {

const std::string Insurance::m_prefix = "insurance";

Insurance::CallbackMap Insurance::initCallbacks ()
{
	CallbackMap callbacks;
	callbacks["new"] = &Insurance::saveNew;
	callbacks["all"] = &Insurance::sendAll;
	return callbacks;
}

const std::string Insurance::m_commands[] = {
	"new",
	"all"
};

Insurance::CallbackMap Insurance::m_callbacks = Insurance::initCallbacks();

void Insurance:: process (Request& Req, Response& Res, Db& db)
{
	m_req = &Req;
	m_res = &Res;
	m_db = &db;
	load ();
}

// private

void Insurance::load ()
{
	for (size_t counter = 0; counter < m_callbacks.size(); ++counter)
		if (m_req->contains(m_commands[counter]))
			return (this->*m_callbacks[m_commands[counter]]) ();
	m_res->badRequest();
}

void Insurance::saveNew ()
{
	std::string msg;
	const std::string& name = m_req->body("name");
	if (name.empty())
		msg = "Wrong data.";
	else {
		if (m_db->checkSet(m_prefix, name))
			msg = "Insurance already exists.";
		else {
			m_db->addSet(m_prefix, name);
			msg = "success";
		}
	}

	m_res->writeHead(200);
	m_res->header("Content-Type", "text/plain");
	m_res->end(msg);
}

void Insurance::sendAll ()
{
	JSON::Object send_data;

	Set& all = m_db->getSet(m_prefix);
	for (auto it = all.begin(); it != all.end(); ++it)
		send_data["insurances"].addToArray(JSON::Object(*it));
	
	m_res->sendJSON(send_data);
}

} // namespace doctor
