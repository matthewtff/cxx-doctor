#include "doctor.hh"

#include <koohar.hh>
#include <oodb.hh>

#include <algorithm>
#include <string>
#include <list>
#include <map>

#include "user.hh"
#include "visit.hh"
#include "inmate.hh"
#include "insurance.hh"
#include "machine.hh"
#include "settings.hh"
#include "disease.hh"

#include "ipage.hh"

namespace doctor {

const std::string Doctor::m_views_dir = "./views/";

Doctor::Doctor (oodb::Db& database) : m_db(database)
{
	m_handlers["/user"].reset(new User);
	m_handlers["/visit"].reset(new Visit);
	m_handlers["/inmate"].reset(new Inmate);
	m_handlers["/insurance"].reset(new Insurance);
	m_handlers["/machine"].reset(new Machine);
	m_handlers["/settings"].reset(new Settings);
	m_handlers["/disease"].reset(new Disease);
}

void Doctor::processRequest(koohar::Request& Req, koohar::Response &Res)
{
	if (Req.contains("/exit")) { // exiting application
		m_db.save();
		exit(0);
	} else if (Req.contains("/save")) { // save changes
		m_db.save();
		Res.writeHead(200);
		Res.end(std::string("success"));
	} else
		findRoute (Req, Res);
}

void Doctor::findRoute (koohar::Request& Req, koohar::Response& Res)
{
	typedef Handlers::value_type HandlerInfo;
	bool no_match = true;
	std::for_each(m_handlers.begin(), m_handlers.end(),
		[&](const HandlerInfo& handler_info) {
			if (no_match && Req.contains(handler_info.first)) {
				handler_info.second->process(Req, Res, m_db);
				handler_info.second->clear();
				no_match = false;
			}
		}
	);
	if (no_match) {
		Res.redirect("/html/index.html");
		Res.end();
	}
}

} // namespace doctor

