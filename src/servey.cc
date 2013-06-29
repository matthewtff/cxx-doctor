#include "servey.hh"

#include <koohar.hh>
#include <oodb.hh>

#include "crypting.hh"

using namespace koohar;
using namespace oodb;
using namespace std;

namespace doctor {

const std::string Servey::m_prefix = "servey";

Servey::Servey (Db& db) : m_db(db)
{}

bool Servey::add (const string& type, const string& date,
	const std::string& sender, const string& dynamic,
	const string& medic, const string& patient,
	const string& machine, const string& detectors,
	const string& diagnosis, const string& data)
{
	if (!(checkSecurity(type) && checkSecurity(date) && checkSecurity(dynamic)
		&& checkSecurity(patient) && checkSecurity(diagnosis)
		&& checkSecurity(data)))
	{
		m_error = "Wrong data.";
		return false;
	}

	m_key = generateKey(medic, patient);
	m_db.addSet(m_prefix, m_key);
	m_db.setString(m_key + ":type", type);
	m_db.setString(m_key + ":date", date);
	m_db.setString(m_key + ":sender", sender);
	m_db.setString(m_key + ":dynamic", dynamic);
	m_db.setString(m_key + ":medic", medic);
	m_db.setString(m_key + ":patient", patient);
	m_db.setString(m_key + ":machine", machine);
	m_db.setString(m_key + ":detectors", detectors);
	m_db.setString(m_key + ":diagnosis", diagnosis);
	m_db.setString(m_key + ":data", data);
	return true;
}


bool Servey::load (const string& key)
{
	if (!m_db.checkSet(m_prefix, key)) {
		m_error = "Servey does not exist.";
		return false;
	}

	m_key = key;
	m_type = m_db.getString(m_key + ":type");
	m_date = m_db.getString(m_key + ":date");
	m_sender = m_db.getString(m_key + ":sender");
	m_dynamic = m_db.getString(m_key + ":dynamic");
	m_medic = m_db.getString(m_key + ":medic");
	m_patient = m_db.getString(m_key + ":patient");
	m_machine = m_db.getString(m_key + ":machine");
	m_detectors = m_db.getString(m_key + ":detectors");
	m_diagnosis = m_db.getString(m_key + ":diagnosis");
	m_data = m_db.getString(m_key + ":data");

	return true;
}

bool Servey::search (oodb::Db& db, const string& search_string,
	ServeyList& serveys)
{
	if (search_string.empty())
		return false;

	bool found = false;
	Set& all = db.getSet(m_prefix);
	for (auto it = all.begin(); it != all.end(); ++it) {
		if (search_string == db.getString(*it + ":patient"))
		{
			Servey servey(db);
			if (!servey.load(*it))
				continue;
			serveys.push_back(servey);
			found = true;
			if (serveys.size() > MaxSearch) // Theese are enough.
				return found;
		}
	}
	return true;
}

void Servey::all (Db& db, ServeyList& serveys)
{
	Set& all = db.getSet(m_prefix);
	for (auto it = all.begin(); it != all.end(); ++it) {
		Servey servey(db);
		if (servey.load(*it)) {
			serveys.push_back(servey);
		}
	}
}

string Servey::generateKey (const string& medic, const string& patient)
{
	return hash(medic + patient + Date().toString());
}

// private

/**
 * In this object should be no empty fields.
 */
bool Servey::checkSecurity (const std::string& value)
{
	return !value.empty() && value.find(":") == value.npos;
}

} // namespace doctor
