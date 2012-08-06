#ifndef doctor_patient_hh
#define doctor_patient_hh

#include <string>
#include <list>

#include <oodb/oodb.hh>

namespace doctor {

class Patient;

typedef std::list<Patient> PatientList;

class Patient {
public:

	enum { SearchMax = 5 };

public:
	Patient (oodb::Db& db);
	std::string error () const { return m_error; }
	bool add (const std::string& name, const std::string& surname,
		const std::string& second_name, const std::string& date,
		const std::string& sex, const std::string& address,
		const std::string& insurance, const std::string& insurance_number,
		const std::string& card);
	
	bool save ();

	bool load (const std::string& key);

	static bool del (oodb::Db& db, const std::string& id);

	/**
	 * Searches patients by surname, and if found similar - puts to list.
	 *
	 * \return true if found one or more similar patients.
	 */
	static bool search (oodb::Db& db, const std::string& search_string,
		PatientList& patients);

	/**
	 * Check if patient on id is similar by surname.
	 */
	static bool checkSimilar (oodb::Db& db, const std::string& key,
		const std::string& search_string);
	
	static void all (oodb::Db& db, PatientList& patients);

	/**
	 * Get one by hash.
	 */
	static void get (oodb::Db& db, const std::string& id,
		PatientList& patients);

	std::string name () const { return m_name; }
	void name (const std::string Name) { m_name = Name; }

	std::string surname () const { return m_surname; }
	void surname (const std::string& SurName) { m_surname = SurName; }

	std::string secondName () const { return m_second_name; }
	void secondName (const std::string& SecondName) {
		m_second_name = SecondName;
	}

	std::string date () const { return m_date; }
	void date (const std::string& Date) { m_date = Date; }

	std::string sex () const { return m_sex; }
	void sex (const std::string& Sex) { m_sex = Sex; }

	std::string address () const { return m_address; }
	void address (const std::string& Address) { m_address = Address; }

	std::string insurance () const { return m_insurance; }
	void insurance (const std::string& Insurance) { m_insurance = Insurance; }

	std::string insurance_number () const { return m_insurance_number; }
	void insuranceNumber (const std::string& InsuranceNumber) {
		m_insurance_number = InsuranceNumber;
	}

	std::string card () const { return m_card; }
	void card (const std::string& Card) { m_card = Card; }

	std::string key () const { return m_key; }
	void key (const std::string& Key) { m_key = Key; }

	static std::string generateKey (const std::string& name,
		const std::string& surname);

public:
	static const std::string m_prefix;

private:

	bool checkSecurity (const std::string& value);

private:
	oodb::Db& m_db;
	std::string m_error;

	std::string m_name;
	std::string m_surname;
	std::string m_second_name;
	std::string m_date;
	std::string m_sex;
	std::string m_address;
	std::string m_insurance;
	std::string m_insurance_number;
	std::string m_card;
	std::string m_key;
}; // class Patient

} // namesapce doctor

#endif // doctor_patient_hh
