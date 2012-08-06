#ifndef doctor_servey_hh
#define doctor_servey_hh

#include <string>
#include <list>

#include <oodb/oodb.hh>

namespace doctor {

class Servey;

typedef std::list<Servey> ServeyList;

class Servey {
public:

	enum { MaxSearch = 5 };

public:
	Servey (oodb::Db& db);
	std::string error () const { return m_error; }
	bool add (const std::string& type, const std::string& date,
		const std::string& sender, const std::string& dynamic,
		const std::string& medic, const std::string& patient,
		const std::string& machine, const std::string& detectors,
		const std::string& diagnosis, const std::string& data);
	bool load (const std::string& key);

	/**
	 * Searches serveys of patient by id.
	 *
	 * \return true if found.
	 */
	static bool search (oodb::Db& db, const std::string& patient,
		ServeyList& serveys);

	static void all (oodb::Db& db, ServeyList& serveys);

	std::string type () const { return m_type; }
	void type (const std::string& Type) { m_type = Type; }

	std::string date () const { return m_date; }
	void date (const std::string& Date) { m_date = Date; }

	std::string sender () const { return m_sender; }
	void sender (const std::string& Sender) { m_sender = Sender; }

	std::string dynamic () const { return m_dynamic; }
	void dynamic (const std::string& Dynamic) { m_dynamic = Dynamic; }

	std::string medic () const { return m_medic; }
	void medic (const std::string& Medic) { m_medic = Medic; }

	std::string patient () const { return m_patient; }
	void patient (const std::string& Patient) { m_patient = Patient; }

	std::string machine () const { return m_machine; }
	void machine (const std::string& Machine) { m_machine = Machine; }

	std::string detectors () const { return m_detectors; }
	void detectors (const std::string& Detectors) { m_detectors = Detectors; }

	std::string diagnosis () const { return m_diagnosis; }
	void diagnosis (const std::string& Diagnosis) {
		m_diagnosis = Diagnosis;
	}

	std::string data () const { return m_data; }
	void data (const std::string& Data) { m_data = Data; }

	std::string key () const { return m_key; }
	void key (const std::string& Key) { m_key = Key; }

	static std::string generateKey (const std::string& medic,
		const std::string& patient);

public:
	static const std::string m_prefix;

private:
	bool checkSecurity (const std::string& value);

private:
	oodb::Db& m_db;
	std::string m_error;

	std::string m_type;
	std::string m_date;
	std::string m_sender;
	std::string m_dynamic;
	std::string m_medic; // Medic key.
	std::string m_patient; // Patient key.
	std::string m_machine; // Machine key.
	std::string m_detectors; 
	std::string m_diagnosis;
	std::string m_data;
	std::string m_key;
}; // class Servey

} // namespace doctor

#endif // doctor_servey_hh
