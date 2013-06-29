#ifndef doctor_settings_hh
#define doctor_settings_hh

#include <string>

#include "ipage.hh"

namespace koohar {
	class Request;
	class Response;
}

namespace oodb {
	class Db;
}

namespace doctor {

class Settings : public IPage {
public:
	static const std::string m_prefix;

public:
	Settings () {}

	virtual void process (koohar::Request& Req, koohar::Response& Res,
		oodb::Db& db);

	virtual void clear () {}

private:
	void load ();
	void set ();
	void get ();

private:
	koohar::Request* m_req;
	koohar::Response* m_res;
	oodb::Db* m_db;
}; // class Settings


} // namespace doctor

#endif // doctor_settings_hh
