#include "register.hh"

#include "medic.hh"

using namespace koohar;
using namespace oodb;
using namespace std;

namespace doctor {

Register::Register (Request& Req, Response& Res, Db& db) : m_db(db),
	m_req(Req), m_res(Res)
{
	load();
}

// private

void Register::load ()
{
	Medic medic(m_db);
	const string& login = m_req.body("login");
	const string& password = m_req.body("password");
	const bool succ = medic.reg(login, password,
		m_req.body("password_confirm"),
		m_req.body("name"),
		m_req.body("surname"),
		m_req.body("second_name"),
		m_req.body("category")
	);

	m_res.writeHead(200);
	m_res.end(succ ? "success" : medic.error());
}

} // namespace doctor
