#ifndef doctor_user_hh
#define doctor_user_hh

#include <string>

#include <oodb/oodb.hh>

namespace doctor {

class Medic {
public:
	Medic (oodb::Db& db);
	bool logIn (const std::string& login, const std::string& password);
	bool reg (const std::string& login, const std::string& password,
		const std::string& password_confirm, const std::string& name,
		const std::string& sur_name, const std::string& second_name,
		const std::string& category);
	std::string error () const { return m_error; }
	bool load (const std::string& login, const std::string& password);

	std::string login () const { return m_login; }
	std::string name () const { return m_name; }
	std::string surname () const { return m_surname; }
	std::string second_name () const { return m_second_name; }
	std::string category () const { return m_category; }

	static std::string generateKey (const std::string& login,
		const std::string& password);

public:
	static const std::string m_prefix;

private:
	/** Security checks for name && password.
	  * \return true if OK.
	  */
	bool checkLogin (const std::string& login);
	bool checkPassword (const std::string& password);

private:
	oodb::Db& m_db;
	std::string m_error;

	std::string m_login;
	std::string m_name;
	std::string m_surname;
	std::string m_second_name;
	std::string m_category;
}; // class Medic

} // namespace doctor

#endif // doctor_user_hh
