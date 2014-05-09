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
	m_handlers["/register"].reset(new Register);
	m_handlers["/visit"].reset(new Visit);
	m_handlers["/inmate"].reset(new Inmate);
	m_handlers["/insurance"].reset(new Insurance);
	m_handlers["/machine"].reset(new Machine);
	m_handlers["/settings"].reset(new Settings);
	m_handlers["/disease"].reset(new Disease);

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
  for (const std::string& route : m_routes) {
    if (Req.contains(route)) {
      auto page = m_handlers[route];
      page->process(Req, Res, m_db);
      page->clear();
      return;
    }
  }
  Res.redirect("/html/index.html");
  Res.end();
}

} // namespace doctor
