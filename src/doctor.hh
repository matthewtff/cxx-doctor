#ifndef doctor_doctor_hh
#define doctor_doctor_hh

#include <memory>
#include <string>
#include <list>
#include <map>

namespace koohar {
	class Request;
	class Response;
}

namespace oodb {
	class Db;
}

namespace doctor {

class IPage;

class Doctor {
public:
	Doctor (oodb::Db& database);

	void processRequest (koohar::Request& Req, koohar::Response& Res);

private:

	typedef std::map<std::string, std::shared_ptr<IPage>> Handlers;

private:

	void findRoute (koohar::Request& Req, koohar::Response& Res);

private:

	static const std::string m_views_dir;

private:
	oodb::Db& m_db;
	Handlers m_handlers;
}; // class Doctor

} // namespace doctor

#endif // doctor_doctor_hh
