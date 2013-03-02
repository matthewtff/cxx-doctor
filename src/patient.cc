#include "patient.hh"

#include <koohar.hh>

#include "crypting.hh"

using namespace koohar;
using namespace oodb;
using namespace std;

namespace doctor {

const string Patient::m_prefix = "patient";

Patient::Patient (Db& db) : m_db(db)
{}

bool Patient::add (const string& name, const string& surname,
		const string& second_name, const string& date,
		const string& sex, const string& address,
		const string& insurance, const string& insurance_number,
		const string& card)
{
	if (!(checkSecurity(name) && checkSecurity(surname)
		&& checkSecurity(second_name) && checkSecurity(date)
		&& checkSecurity(sex) && checkSecurity(address)
		&& checkSecurity(insurance) && checkSecurity(insurance_number)
		&& checkSecurity(card) && !name.empty() && !surname.empty()
		&& !date.empty()))
	{
		m_error = "Wrong data.";
		return false;
	}

	m_key = generateKey(name, surname);
	m_db.addSet(m_prefix, m_key);
	m_db.setString(m_key + ":name", name);
	m_db.setString(m_key + ":surname", surname);
	m_db.setString(m_key + ":second_name", second_name);
	m_db.setString(m_key + ":date", date);
	m_db.setString(m_key + ":sex", sex);
	m_db.setString(m_key + ":address", address);
	m_db.setString(m_key + ":insurance", insurance);
	m_db.setString(m_key + ":insurance_number", insurance_number);
	m_db.setString(m_key + ":card", card);
	return true;
}

bool Patient::save ()
{
	m_db.setString(m_key + ":name", m_name);
	m_db.setString(m_key + ":surname", m_surname);
	m_db.setString(m_key + ":second_name", m_second_name);
	m_db.setString(m_key + ":date", m_date);
	m_db.setString(m_key + ":sex", m_sex);
	m_db.setString(m_key + ":address", m_address);
	m_db.setString(m_key + ":insurance", m_insurance);
	m_db.setString(m_key + ":insurance_number", m_insurance_number);
	m_db.setString(m_key + ":card", m_card);
	return true;
}

bool Patient::load (const string& key)
{
	if (!m_db.checkSet(m_prefix, key)) {
		m_error = "Patient does not exist.";
		return false;
	}
	m_key = key;
	m_name = m_db.getString(m_key + ":name");
	m_surname = m_db.getString(m_key + ":surname");
	m_second_name = m_db.getString(m_key + ":second_name");
	m_date = m_db.getString(m_key + ":date");
	m_sex = m_db.getString(m_key + ":sex");
	m_address = m_db.getString(m_key + ":address");
	m_insurance = m_db.getString(m_key + ":insurance");
	m_insurance_number = m_db.getString(m_key + ":insurance_number");
	m_card = m_db.getString(m_key + ":card");
	return true;
}

bool Patient::del (oodb::Db& db, const std::string& id)
{
	if (id.empty() || !db.checkSet(m_prefix, id))
		return false;

	db.remSet(m_prefix, id);
	db.unsetString(id + ":name");
	db.unsetString(id + ":surname");
	db.unsetString(id + ":second_name");
	db.unsetString(id + ":date");
	db.unsetString(id + ":sex");
	db.unsetString(id + ":address");
	db.unsetString(id + ":insurance");
	db.unsetString(id + ":insurance_number");
	db.unsetString(id + ":card");
	return true;
}

bool Patient::search (Db& db, const string& search_string,
	PatientList& patients)
{
	if (search_string.empty())
		return false;
	
	bool found = false;
	Set& all = db.getSet(m_prefix);
	for (auto it = all.begin(); it != all.end(); ++it) {
		if (checkSimilar(db, *it, search_string)) {
			Patient patie(db);
			if (!patie.load(*it))
				continue;
			patients.push_back(patie);
			found = true;
			if (patients.size() >= SearchMax) // We've got all we need.
				return found; // true
		}
	}
	return found;
}

bool Patient::checkSimilar (Db& db, const string& key,
	const string& search_string)
{
	if (!db.checkSet(m_prefix, key))
		return false;

	string real_surname = db.getString(key + ":surname");

	if (real_surname.length() < search_string.length())
		return false;
	for (unsigned int count = 0; count < search_string.length(); ++count) {
		if (real_surname[count] != search_string[count])
			return false;
	}
	return true;
}

void Patient::all (Db& db, PatientList& patients)
{
	Set& all = db.getSet(m_prefix);
	for (auto it = all.begin(); it != all.end(); ++it) {
		Patient patie(db);
		if (!patie.load(*it))
			continue;
		patients.push_back(patie);
	}
}

void Patient::get (Db& db, const string& id, PatientList& patients)
{
	Patient patie(db);
	if (patie.load(id))
		patients.push_back(patie);
}


string Patient::generateKey (const string& name, const string& surname)
{
	return hash(name + surname + Date().toString());
}

// private

bool Patient::checkSecurity (const string& value)
{
	return (value.length() < 2048) && (value.find(":") == value.npos);
}

} // namespace doctor
