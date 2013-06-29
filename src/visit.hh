#ifndef doctor_visit_hh
#define doctor_visit_hh

#include "ipage.hh"

namespace koohar {
	class Request;
	class Response;
}

namespace oodb {
	class Db;
}

namespace doctor {

class Visit : public IPage {
public:
	Visit () {}

	virtual void process (koohar::Request& Req, koohar::Response& Res,
		oodb::Db& db);

	virtual void clear () {}

private:
	void load ();
	void saveNew ();
	void sendAll ();

private:
	koohar::Request* m_req;
	koohar::Response* m_res;
	oodb::Db* m_db;
}; // class Visit

} // namespace doctor

#endif // doctor_visit_hh
