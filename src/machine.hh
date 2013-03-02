#ifndef doctor_machine_hh
#define doctor_machine_hh

#include <koohar.hh>
#include <oodb.hh>

#include <string>
#include <map>

#include "ipage.hh"

namespace doctor {

class Machine : public IPage {
public:
	Machine () {}

	virtual void process (koohar::Request& Req, koohar::Response& Res,
		oodb::Db& db);

	virtual void clear () {}

private:

	typedef void (Machine::*Callback) ();

	typedef std::map<std::string, Callback> CallbackMap;

private:

	static CallbackMap initCallbacks ();

	void load ();
	void saveNew ();
	void sendAll ();
	void remove ();
	void change ();
	void badRequest ();

private:
	koohar::Request* m_req;
	koohar::Response* m_res;
	oodb::Db* m_db;

	static CallbackMap m_callbacks;

	static const std::string m_commands[];

}; // class Machine

} // namespace doctor

#endif // doctor_machine_hh
