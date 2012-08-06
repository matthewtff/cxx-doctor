#ifndef doctor_inmate_hh
#define doctor_inmate_hh

#include <koohar/request.hh>
#include <koohar/response.hh>

#include <oodb/oodb.hh>

#include <string>

#include "patient.hh"

namespace doctor {

class Inmate {
public:
	Inmate (koohar::Request& Req, koohar::Response& Res, oodb::Db& db);

private:
	void load ();
	void add ();
	void search ();
	void edit ();
	void all ();
	void get ();
	void del ();
	void sendPatients (PatientList& patients);

private:
	koohar::Request& m_req;
	koohar::Response& m_res;
	oodb::Db& m_db;
}; // class Inmate

} // namespace doctor

#endif // doctor_inmate_hh
