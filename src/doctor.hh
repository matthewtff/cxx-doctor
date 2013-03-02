#ifndef doctor_doctor_hh
#define doctor_doctor_hh

#include <koohar.hh>
#include <oodb.hh>

#include <memory>
#include <string>
#include <list>
#include <map>

namespace doctor {

class IPage;

class Doctor {
public:
	Doctor (oodb::Db& database);

	void processRequest (koohar::Request& Req, koohar::Response& Res);

private:

	typedef std::map<std::string, std::shared_ptr<IPage>> Handlers;
	typedef std::list<std::string> Routes;

private:

	void findRoute (koohar::Request& Req, koohar::Response& Res);

private:

	static const std::string m_views_dir;

private:
	oodb::Db& m_db;
	Handlers m_handlers;
	Routes m_routes;
}; // class Doctor

} // namespace doctor

#endif // doctor_doctor_hh
