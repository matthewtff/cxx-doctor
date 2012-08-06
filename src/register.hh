#ifndef doctor_register_hh
#define doctor_register_hh

#include <koohar/request.hh>
#include <koohar/response.hh>

#include <oodb/oodb.hh>

#include <string>

namespace doctor {

class Register {
public:
	Register (koohar::Request& Req, koohar::Response& Res, oodb::Db& db);

private:
	void load ();

private:
	oodb::Db& m_db;
	koohar::Request& m_req;
	koohar::Response& m_res;
}; // class Register

} // namespace doctor

#endif // doctor_register_hh
