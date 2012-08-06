#include "device.hh"

using namespace oodb;
using namespace std;

namespace doctor {

const string Device::m_prefix = "device";

Device::Device (Db& db) : m_db(db)
{}

bool Device::add (const string& name, const string& info)
{
	if (!(checkSecurity(name) && checkSecurity(info))) {
		m_error = "Wrong data.";
		return false;
	}

	m_db.addSet(m_prefix, name);

	string key = generateKey(name);
	m_db.setString(key + ":info", info);

	return true;
}

bool Device::load (const string& name)
{
	if (!m_db.checkSet(m_prefix, name)) {
		m_error = "Device does not exist.";
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
	return !value.empty() && value.find(":") == value.npos;
}

} // namespace doctor
