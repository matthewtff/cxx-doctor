#ifndef doctor_settings_hh
#define doctor_settings_hh

#include <koohar/request.hh>
#include <koohar/response.hh>

#include <oodb/oodb.hh>

#include <string>

namespace doctor {

class Settings {
public:
	static const std::string m_prefix;

public:
	Settings (koohar::Request& Req, koohar::Response& Res, oodb::Db& db);

private:
	void load ();
	void set ();
	void get ();

private:
	koohar::Request& m_req;
	koohar::Response& m_res;
	oodb::Db& m_db;
}; // class Settings


} // namespace doctor

#endif // doctor_settings_hh
