#ifndef doctor_device_hh
#define doctor_device_hh

#include <string>
#include <list>

#include <oodb/oodb.hh>

namespace doctor {

class Device;

typedef std::list<Device> DeviceList;

class Device {
public:
	Device (oodb::Db& db);
	std::string error () const { return m_error; }

	bool add (const std::string& name, const std::string& info);

	bool change (const std::string& previous_name, const std::string& name,
		const std::string& info);

	bool remove (const std::string& name);

	bool load (const std::string& name);

	static void all (oodb::Db& db, DeviceList& devices);

	std::string name () const { return m_name; }
	void name (const std::string& Name) { m_name = Name; }

	std::string info () const { return m_info; }
	void info (const std::string& Info) { m_info = Info; }

	static std::string generateKey(const std::string& name);

public:
	static const std::string m_prefix;

private:
	bool checkSecurity(const std::string& value);

private:
	oodb::Db& m_db;
	std::string m_error;

	std::string m_name;
	std::string m_info; // JSONed, detectors also here ??

}; // class Device

} // namespace doctor

#endif // doctor_device_hh
