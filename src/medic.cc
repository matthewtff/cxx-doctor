#include "medic.hh"

#include "crypting.hh"

using namespace oodb;
using namespace std;

namespace doctor {

const std::string Medic::m_prefix = "medic";

Medic::Medic (Db& db) : m_db(db)
{}

bool Medic::logIn (const string& login, const string& password)
{
	if (login.empty() || password.empty())
		return false;
	
	string key = generateKey(login, password);

	if (m_db.checkSet(m_prefix, login)) {
		if (m_db.getString(key + ":password") == hash(password))
			return true;
		else {
			m_error = "Login/password mismatch.";
			return false;
		}
	} else {
		m_error = "Medic does not exist.";
		return false;
	}
}

bool Medic::reg (const string& login, const string& password,
	const string& password_confirm, const string& name,
	const string& surname, const string& second_name,
	const string& category)
{
	if (login.empty() || password.empty() || name.empty()
		|| surname.empty())
	{
		m_error = "Empty field.";
		return false;
	}
	if (password != password_confirm) {
		m_error = "Password mismatch.";
		return false;
	}
	// Some security checks.
	if (!checkLogin(login) || !checkPassword(password))
		return false; // m_error is set by checking functions.

	if (m_db.checkSet(m_prefix, login)) {
		// Do not register new user, if login already used.
		m_error = "Medic exists.";
		return false;
	}
	m_db.addSet(m_prefix, login);

	string key = generateKey(login, password);
	m_db.setString(key + ":password", hash(password));
	m_db.setString(key + ":name", name);
	m_db.setString(key + ":surname", surname);
	m_db.setString(key + ":second_name", second_name);
	m_db.setString(key + ":category", category);
	return true;
}

bool Medic::load (const string& login, const string& password)
{
	if (!m_db.checkSet(m_prefix, login)) {
		m_error = "Medic does not exist.";
		return false;
	}
	m_login = login;

	string key = generateKey(login, password);
	m_name = m_db.getString(key + ":name");
	m_surname = m_db.getString(key + ":surname");
	m_second_name = m_db.getString(key + ":second_name");
	m_category = m_db.getString(key + ":category");
	return true;
}

string Medic::generateKey (const string& login, const string& password)
{
	return m_prefix + ":" + hash(login + password);
}

// private

bool Medic::checkLogin (const string& login)
{
	if (login.size() < 5) {
		m_error = "Login is too short.";
		return false;
	}
	// Check for ':' symbol in login. Actually this should not be so important,
	// but we want to be sure app is secure.
	if (login.find(":") != login.npos) {
		m_error = "Login must not contain ':' symbol.";
		return false;
	}
	return true;
}

bool Medic::checkPassword (const string& password)
{
	if (password.size() < 5) {
		m_error = "Password is too short.";
		return false;
	}
	// Same as login.
	if (password.find(":") != password.npos) {
		m_error = "Password must not contain ':' symbol.";
		return false;
	}
	return true;
}


} // namespace doctor
