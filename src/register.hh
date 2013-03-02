#ifndef doctor_register_hh
#define doctor_register_hh

#include <koohar.hh>
#include <oodb.hh>

#include <string>

#include "ipage.hh"

namespace doctor {

class Register : public IPage {
public:
	Register () {}

	virtual void process (koohar::Request& Req, koohar::Response& Res,
		oodb::Db& db);

	virtual void clear () {}

private:
	void load ();

private:
	oodb::Db* m_db;
	koohar::Request* m_req;
	koohar::Response* m_res;
}; // class Register

} // namespace doctor

#endif // doctor_register_hh
