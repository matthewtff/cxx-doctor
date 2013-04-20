#ifndef doctor_disease_hh
#define doctor_disease_hh

#include <koohar.hh>
#include <oodb.hh>

#include <sstream>
#include <string>
#include <map>

#include "ipage.hh"

namespace doctor {

class Disease : public IPage {
public:
	static const unsigned short SearchMax = 5;

public:
	Disease () {}

	virtual void process (koohar::Request& Req, koohar::Response& Res,
		oodb::Db& db);

	virtual void clear () {}

public:
	static const std::string m_prefix;

private:

	typedef void (Disease::*Callback) ();

	typedef std::map<std::string, Callback> CallbackMap;

private:

	static CallbackMap initCallbacks ();

	void load ();
	void search ();
	void get ();
	void badRequest ();

	bool checkSimilar (const std::string& key,
		const std::string& search_string, koohar::JSON::Object& stream);

private:
	koohar::Request* m_req;
	koohar::Response* m_res;
	oodb::Db* m_db;

	static CallbackMap m_callbacks;

	static const std::string m_commands[];

}; // class Disease

} // namespace doctor

#endif // doctor_disease_hh
