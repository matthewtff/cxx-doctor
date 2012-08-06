#ifndef doctor_machine_hh
#define doctor_machine_hh

#include <koohar/request.hh>
#include <koohar/response.hh>

#include <oodb/oodb.hh>

namespace doctor {

class Machine {
public:
	Machine (koohar::Request& Req, koohar::Response& Res, oodb::Db& db);

private:
	void load ();
	void saveNew ();
	void sendAll ();

private:
	koohar::Request& m_req;
	koohar::Response& m_res;
	oodb::Db& m_db;
}; // class Machine

} // namespace doctor

#endif // doctor_machine_hh
