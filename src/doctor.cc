#include <functional>
#include <iostream>
#include <cstdlib>
#include <string>

#include <koohar/app.hh>
#include <koohar/webpage.hh>

#include <oodb/oodb.hh>

#include "win.hh"
#include "register.hh"
#include "visit.hh"
#include "inmate.hh"
#include "insurance.hh"
#include "machine.hh"
#include "settings.hh"
#include "disease.hh"

#include <fstream>

using namespace doctor;

static std::string views_dir("./views/");
static std::string db_name("doctordb.dat");
static oodb::Db db = oodb::Db(db_name);

void AddMKBToDb(oodb::Db& db);

class Doctor {
public:
	Doctor (oodb::Db& database) : m_db(database) {}

	void processRequest (koohar::Request& Req, koohar::Response& Res);

private:
	oodb::Db& m_db;
}; // class Doctor;

void Doctor::processRequest(koohar::Request& Req, koohar::Response &Res)
{
	if (Req.contains("/reset-all")) { // flush data from db
		m_db.flush();
		AddMKBToDb(m_db);
		Res.writeHead(200);
		std::string msg = "success";
		Res.header("Content-Type", "text/plain");
		Res.end(msg);
	} else if (Req.contains("/save")) { // save changes
		std::cout << "\tSaving data..." << std::endl;
		m_db.save();
		std::cout << "\tData successfully saved!" << std::endl;
	} else if (Req.contains("/register")) {
		Register(Req, Res, m_db);
	} else if (Req.contains("/visit")) {
		Visit(Req, Res, m_db);
	} else if (Req.contains("/inmate")) {
		Inmate(Req, Res, m_db);
	} else if (Req.contains("/insurance")) {
		Insurance(Req, Res, m_db);
	} else if (Req.contains("/machine")) {
		Machine(Req, Res, m_db);
	} else if (Req.contains("/settings")) {
		Settings(Req, Res, m_db);
	} else if (Req.contains("/disease")) {
		Disease(Req, Res, m_db);
	} else {
		koohar::WebPage(Req, Res, views_dir + "./index.html").render();
	}
}

HandlerRet sigHandler (HandlerGet sig)
{
	if (sig == CTRL_C_EVENT || sig == QUIT_EVENT || sig == TERM_EVENT) {
		db.save();
		exit(0);
	}
#ifdef _WIN32
	else return 0;
#endif /* _WIN32 */
}

int main (int argc, char* argv[])
{
	setHandler(CTRL_C_EVENT, sigHandler);
	setHandler(QUIT_EVENT, sigHandler);
	setHandler(TERM_EVENT, sigHandler);

	std::string host = "localhost";
	unsigned short port = 7000;
	if (argc > 1)
		host.assign(argv[1]);
	if (argc > 2)
		port = static_cast<unsigned short>(atoi(argv[2]));

	Doctor doc(db);
	auto callback = std::bind(&Doctor::processRequest, doc,
		std::placeholders::_1, std::placeholders::_2);
	koohar::App<decltype(callback)> app(host, port, 2);
	app.config("static_dir", "public");
	app.config("static", "/html");
	app.config("static", "/music");
	app.config("static", "/images");
	app.config("static", "/js");
	app.config("static", "/css");
	app.config("static", "/tmpl");
	app.config("static", "/lang");

	app.listen(callback);
	return 0;
}

void delReturnes(std::string& str)
{
	while ((str[str.length() - 1] == '\n') || (str[str.length() - 1] == '\r'))
		str.erase(str.length() - 1, 1);
}

void AddMKBToDb(oodb::Db& db)
{
	std::string key, value;

	std::ifstream mkb_file("./mkb");
	if (!mkb_file.is_open())
		return;

	std::getline(mkb_file, key);
	std::getline(mkb_file, value);

	while (!key.empty() && !value.empty()) {

		delReturnes(key);
		delReturnes(value);

		db.addSet(Disease::m_prefix, key);
		db.setString(Disease::m_prefix + ":" + key, value);

		std::getline(mkb_file, key);
		std::getline(mkb_file, value);
	}
}
