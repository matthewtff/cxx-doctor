#include "doctor.hh"

#include <koohar.hh>
#include <oodb.hh>

#include <algorithm>
#include <string>
#include <list>
#include <map>

#include "register.hh"
#include "visit.hh"
#include "inmate.hh"
#include "insurance.hh"
#include "machine.hh"
#include "settings.hh"
#include "disease.hh"

#include "ipage.hh"

#include "handler.hh"

namespace doctor {

const std::string Doctor::m_views_dir = "./views/";

Doctor::Doctor (oodb::Db& database) : m_db(database)
{
	m_handlers["/register"].reset(dynamic_cast<IPage*>(new Register));
	m_handlers["/visit"].reset(dynamic_cast<IPage*>(new Visit));
	m_handlers["/inmate"].reset(dynamic_cast<IPage*>(new Inmate));
	m_handlers["/insurance"].reset(dynamic_cast<IPage*>(new Insurance));
	m_handlers["/machine"].reset(dynamic_cast<IPage*>(new Machine));
	m_handlers["/settings"].reset(dynamic_cast<IPage*>(new Settings));
	m_handlers["/disease"].reset(dynamic_cast<IPage*>(new Disease));

	m_routes.push_back("/register");
	m_routes.push_back("/visit");
	m_routes.push_back("/inmate");
	m_routes.push_back("/insurance");
	m_routes.push_back("/machine");
	m_routes.push_back("/settings");
	m_routes.push_back("/disease");
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
	} else {
		findRoute (Req, Res);
	}
}

void Doctor::findRoute (koohar::Request& Req, koohar::Response& Res)
{
	bool no_match = true;
	std::for_each(m_routes.begin(), m_routes.end(),
		[&](const std::string& route) {
			if (no_match && Req.contains(route)) {
				auto page = m_handlers[route];
				page->process(Req, Res, m_db);
				page->clear();
				no_match = false;
			}
		}
	);
	if (no_match)
		koohar::WebPage(Req, Res, m_views_dir + "./index.html").render();
}

} // namespace doctor
