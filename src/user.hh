#ifndef doctor_user_hh
#define doctor_user_hh

#include <koohar.hh>
#include <oodb.hh>

#include <string>

#include "ipage.hh"

namespace doctor {

class User : public IPage {
public:

	virtual void process (koohar::Request& Req, koohar::Response& Res,
		oodb::Db& db);

	virtual void clear () {}

private:
	void load ();
	void reg ();
	void list ();
	void remove ();

private:
	oodb::Db* m_db;
	koohar::Request* m_req;
	koohar::Response* m_res;
}; // class User

} // namespace doctor

#endif // doctor_user_hh
