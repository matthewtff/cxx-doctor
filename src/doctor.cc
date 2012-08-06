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

#include <cstdio>

using namespace doctor;

static std::string views_dir("views/");
static std::string db_name("doctordb.dat");
static oodb::Db db(db_name);

struct ServerObjects {
	ServerObjects (oodb::Db& db) : m_db(db) {}
	oodb::Db& m_db;
}; // struct ServerObjects

HandlerRet sigHandler (HandlerGet sig)
{
	if (sig == CTRL_C_EVENT) {
		std::cout << "\texiting...\n";
		exit(0);
	}
}

void AddMKBToDb(oodb::Db& db);

void ServerLogic(koohar::Request& Req, koohar::Response &Res, void* Struct)
{
	ServerObjects* objects = reinterpret_cast<ServerObjects*>(Struct);
	if (!objects) // some kind of error actually :(
		return;
	if (Req.contains("/reset-all")) { // flush data from db
		objects->m_db.flush();
		AddMKBToDb(objects->m_db);
		Res.writeHead(200);
		std::string msg = "success";
		Res.header("Content-Type", "text/plain");
		Res.end(msg);
	} else if (Req.contains("/register")) {
		Register(Req, Res, objects->m_db);
	} else if (Req.contains("/visit")) {
		Visit(Req, Res, objects->m_db);
	} else if (Req.contains("/inmate")) {
		Inmate(Req, Res, objects->m_db);
	} else if (Req.contains("/insurance")) {
		Insurance(Req, Res, objects->m_db);
	} else if (Req.contains("/machine")) {
		Machine(Req, Res, objects->m_db);
	} else if (Req.contains("/settings")) {
		Settings(Req, Res, objects->m_db);
	} else if (Req.contains("/disease")) {
		Disease(Req, Res, objects->m_db);
	} else {
		Res.redirect("/html/index.html");
		Res.end();
	}
}

int main (int argc, char* argv[])
{
	setHandler(CTRL_C_EVENT, sigHandler);
	std::string host = "localhost";
	unsigned short port = 7000;
	if (argc > 1)
		host.assign(argv[1]);
	if (argc > 2)
		port = static_cast<unsigned short>(atoi(argv[2]));
	koohar::App app(host, port, 2);
	app.config("static_dir", "public");
	app.config("static", "/html");
	app.config("static", "/music");
	app.config("static", "/images");
	app.config("static", "/js");
	app.config("static", "/css");
	app.config("static", "/tmpl");
	app.config("static", "/lang");
	ServerObjects objects(db);
	//AddMKBToDb(db);
	app.listen(ServerLogic, reinterpret_cast<void*>(&objects));
	return 0;
}

void delReturnes(std::string& str)
{

	while ((str[str.length() - 1] == '\n') || (str[str.length() - 1] == '\r'))
		str.erase(str.length() - 1, 1);
}

void AddMKBToDb(oodb::Db& db)
{
	char *key = NULL, *value = 0;
	size_t size_key = 0, size_value = 0;
	ssize_t readed_key = 0, readed_value = 0;

	FILE* mkb_file = fopen("./mkb", "r");
	if (!mkb_file)
		return;

	while ((readed_key = getline(&key, &size_key, mkb_file)) > 0) {
		readed_value = getline(&value, &size_value, mkb_file);
		if (readed_value < 1)
			break;

		std::string key_str(key);
		std::string value_str(value);

		delReturnes(key_str);
		delReturnes(value_str);

		db.addSet(Disease::m_prefix, key_str);
		db.setString(Disease::m_prefix + ":" + key_str, value_str);

		free(key); key = 0;
		free(value); value = 0;
	}

	fclose(mkb_file);
}
