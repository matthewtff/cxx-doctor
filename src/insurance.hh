#ifndef doctor_insurance_hh
#define doctor_insurance_hh

#include <koohar.hh>
#include <oodb.hh>

#include <string>
#include <map>

#include "ipage.hh"

namespace doctor {

class Insurance : public IPage {
public:
	static const std::string m_prefix;

public:
	Insurance () {}
	virtual void process (koohar::Request& Req, koohar::Response& Res,
		oodb::Db& db);

	virtual void clear () {}

private:

	typedef void (Insurance::*Callback) ();

	typedef std::map<std::string, Callback> CallbackMap;

private:

	static CallbackMap initCallbacks ();

	void load ();
	void saveNew ();
	void sendAll ();

private:
	koohar::Request* m_req;
	koohar::Response* m_res;
	oodb::Db* m_db;

	static CallbackMap m_callbacks;

	static const std::string m_commands[];

}; // class Insurance


} // namespace doctor

#endif // doctor_insurance_hh
