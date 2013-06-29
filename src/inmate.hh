#ifndef doctor_inmate_hh
#define doctor_inmate_hh

#include <string>
#include <map>

#include "patient.hh"

#include "ipage.hh"

namespace koohar {
	class Request;
	class Response;
}

namespace oodb {
	class Db;
}

namespace doctor {

class Inmate : public IPage {
public:

	virtual void process (koohar::Request& Req, koohar::Response& Res,
		oodb::Db& db);

	virtual void clear () {}

private:

	typedef void (Inmate::*Callback) ();

	typedef std::map<std::string, Callback> CallbackMap;

private:

	static CallbackMap initCallbacks ();

	void load ();
	void add ();
	void search ();
	void edit ();
	void all ();
	void get ();
	void del ();
	void sendPatients (PatientList& patients);

private:
	koohar::Request* m_req;
	koohar::Response* m_res;
	oodb::Db* m_db;

	static CallbackMap m_callbacks;
	static const std::string m_commands[];

}; // class Inmate

} // namespace doctor

#endif // doctor_inmate_hh
