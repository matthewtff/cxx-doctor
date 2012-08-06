#ifndef doctor_insurance_hh
#define doctor_insurance_hh

#include <koohar/request.hh>
#include <koohar/response.hh>

#include <oodb/oodb.hh>

#include <string>

namespace doctor {


class Insurance {
public:
	static const std::string m_prefix;

public:
	Insurance (koohar::Request& Req, koohar::Response& Res, oodb::Db& db);

private:
	void load ();
	void saveNew ();
	void sendAll ();

private:
	koohar::Request& m_req;
	koohar::Response& m_res;
	oodb::Db& m_db;
}; // class Insurance


} // namespace doctor

#endif // doctor_insurance_hh
