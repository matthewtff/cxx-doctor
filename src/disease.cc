#include "disease.hh"

using namespace koohar;
using namespace oodb;
using namespace std;

namespace doctor {

const string Disease::m_prefix = "mkb_disease";

Disease::Disease (Request& Req, Response& Res, Db& db) : m_req(Req),
	m_res(Res), m_db(db)
{
	load();
}

// private

void Disease::load ()
{
	if (m_req.contains("search"))
		search();
	else if (m_req.contains("get"))
		get();
	else {
		m_res.writeHead(200);
		m_res.end();
	}
}

void Disease::search ()
{
	stringstream send_data;
	send_data << "{\"diseases\":[";

	string search_string = m_req.body("search_string");

	unsigned int found = 0;
	Set& all = m_db.getSet(m_prefix);
	for (auto it = all.begin(); it != all.end() && found < SearchMax; ++it) {
		if (checkSimilar(*it, search_string, send_data)) {
			++found;
		}
	}

	send_data << "]}";

	m_res.writeHead(200);
	m_res.header("Content-Type", "application/json");
	m_res.end(send_data.str());
}

bool Disease::checkSimilar (const string& key, const string& search_string,
	stringstream& stream)
{
	if (!m_db.checkSet(m_prefix, key))
		return false;

	string real_value = m_db.getString(m_prefix + ":" + key);

	if (real_value.length() < search_string.length())
		return false;
	for (unsigned int count = 0; count < search_string.length(); ++count) {
		if (real_value[count] != search_string[count])
			return false;
	}

	append(stream, key, real_value);

	return true;

}

void Disease::get () {
	string real_value = m_db.getString(m_prefix + ":" + m_req.body("key"));
	stringstream send_data;
	send_data << "{\"diseases\":[{\"key\":\"" << m_req.body("key")
		<< "\",\"value\":\"" << real_value << "\"}]}";

	m_res.writeHead(200);
	m_res.header("Content-Type", "application/json");
	m_res.end(send_data.str());
}

void Disease::append (stringstream& stream, const string& key,
	const string& string)
{
	bool first = stream.str().length() < 15; // approx length of '{"diseases":['
	if (!first)
		stream << ",";
	stream << "{\"key\":\"" << key << "\",\"value\":\"" << string << "\"}";
}


} // namespace doctor
