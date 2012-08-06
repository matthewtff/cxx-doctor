#ifndef doctor_visit_hh
#define doctor_visit_hh

#include <koohar/request.hh>
#include <koohar/response.hh>

#include <oodb/oodb.hh>

namespace doctor {

class Visit {
public:
	Visit (koohar::Request& Req, koohar::Response& Res, oodb::Db& db);

private:
	void load ();
	void saveNew ();
	void sendAll ();

private:
	koohar::Request& m_req;
	koohar::Response& m_res;
	oodb::Db& m_db;
}; // class Visit

} // namespace doctor

#endif // doctor_visit_hh
