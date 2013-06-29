#include "device.hh"

#include <oodb.hh>

using namespace oodb;
using namespace std;

namespace doctor {

const string Device::m_prefix = "device";

Device::Device (Db& db) : m_db(db)
{}

bool Device::add (const string& name, const string& info)
{
	if (!(checkSecurity(name) && checkSecurity(info))) {
		m_error = "Wrong data";
		return false;
	} else if (m_db.checkSet(m_prefix, name)) {
		m_error = "Device already exists";
		return false;
	}

	m_db.addSet(m_prefix, name);

	string key = generateKey(name);
	m_db.setString(key + ":info", info);

	return true;
}

bool Device::change (const std::string& previous_name, const std::string& name,
	const std::string& info)
{
	if (previous_name.empty() || name.empty() || info.empty()) {
		m_error = "Wrong data";
		return false;
	}
	return remove(previous_name) && add(name, info);
}


bool Device::remove (const std::string& name)
{
	if (!(checkSecurity(name))) {
		m_error = "Wrong data";
		return false;
	} else if (!m_db.checkSet(m_prefix, name)) {
		m_error = "Device does not exist";
		return false;
	}

	m_db.remSet(m_prefix, name);
	string key = generateKey(name);
	m_db.unsetString(key + ":info");

	return true;
}


bool Device::load (const string& name)
{
	if (!m_db.checkSet(m_prefix, name)) {
		m_error = "Device does not exist";
		return false;
	}
	m_name = name;

	string key = generateKey(name);
	m_info = m_db.getString(key + ":info");

	return true;
}

string Device::generateKey (const string& name)
{
	return m_prefix + ":" + name;
}

void Device::all (oodb::Db& db, DeviceList& devices)
{
	Set& all = db.getSet(m_prefix);
	for (auto it = all.begin(); it != all.end(); ++it) {
		Device device(db);
		if (device.load(*it)) {
			devices.push_back(device);
		}
	}
}

// private

bool Device::checkSecurity (const string& value)
{
	// JSON contains ':', so do not check it.
	return !value.empty();// && value.find(":") == value.npos;
}

} // namespace doctor
