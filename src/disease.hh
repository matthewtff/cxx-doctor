#ifndef doctor_disease_hh
#define doctor_disease_hh

#include <koohar/request.hh>
#include <koohar/response.hh>

#include <oodb/oodb.hh>

#include <string>
#include <sstream>

namespace doctor {

class Disease {
public:
	enum { SearchMax = 5 };

public:
	Disease (koohar::Request& Req, koohar::Response& Res, oodb::Db& db);

public:
	static const std::string m_prefix;

private:
	void load ();
	void search ();
	bool checkSimilar (const std::string& key, const std::string& search_string,
		std::stringstream& stream);
	void get ();
	void append (std::stringstream& stream, const std::string& key,
		const std::string& string);

private:
	koohar::Request& m_req;
	koohar::Response& m_res;
	oodb::Db& m_db;
}; // class Disease

} // namespace doctor

#endif // doctor_disease_hh
