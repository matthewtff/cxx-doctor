#ifndef doctor_user_hh
#define doctor_user_hh

#include <koohar.hh>
#include <oodb.hh>

#include <string>
#include <map>

#include "ipage.hh"

namespace doctor {

class User : public IPage {
public:

	virtual void process (koohar::Request& Req, koohar::Response& Res,
		oodb::Db& db);

	virtual void clear () {}

private:

	typedef void (User::*Callback) ();

	typedef std::map<std::string, Callback> CallbackMap;

private:

	static CallbackMap initCallbacks ();

	void load ();
	void reg ();
	void list ();
	void remove ();
	void get ();

private:
	oodb::Db* m_db;
	koohar::Request* m_req;
	koohar::Response* m_res;

	static CallbackMap m_callbacks;
	static const std::string m_commands[];
}; // class User

} // namespace doctor

#endif // doctor_user_hh
