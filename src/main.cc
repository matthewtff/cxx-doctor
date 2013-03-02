#include <functional>
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>

#include <koohar.hh>
#include <oodb.hh>

#include "handler.hh"

#include "doctor.hh"
#include "disease.hh"

using namespace doctor;

static std::string db_name("doctordb.dat");
static oodb::Db db = oodb::Db(db_name);

HandlerRet sigHandler (HandlerGet sig);

void AddMKBToDb(oodb::Db& db);

int main (int argc, char* argv[])
{
	unsigned short port = (argc > 1)
		? static_cast<unsigned short>(std::atoi(argv[1]))
		: 8000;

	setHandler(CTRL_C_EVENT, sigHandler);
	setHandler(QUIT_EVENT, sigHandler);
	setHandler(TERM_EVENT, sigHandler);

	Doctor doc(db);
	koohar::ServerAsio server(port);

	server.load("./config.xml");

	server.listen( std::bind(&Doctor::processRequest, doc,
		std::placeholders::_1, std::placeholders::_2) );

	return 0;
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
