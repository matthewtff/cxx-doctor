#include "inmate.hh"

#include <sstream>

using namespace koohar;
using namespace oodb;
using namespace std;

#include <iostream>

namespace doctor {

Inmate::Inmate (Request& Req, Response& Res, Db& db) : m_req(Req), m_res(Res),
	m_db(db)
{
	load();
}

// private

void Inmate::load ()
{
	if (m_req.contains("new"))
		add();
	else if (m_req.contains("edit"))
		edit();
	else if (m_req.contains("search"))
		search();
	else if (m_req.contains("all"))
		all();
	else if (m_req.contains("get"))
		get();
	else if (m_req.contains("del"))
		del();
	else {
		m_res.writeHead(200);
		m_res.end();
	}
}

void Inmate::add ()
{
	Patient patient(m_db);
	bool succ = patient.add(
		m_req.body("name"),
		m_req.body("surname"),
		m_req.body("second_name"),
		m_req.body("date"),
		m_req.body("sex"),
		m_req.body("address"),
		m_req.body("insurance"),
		m_req.body("insurance_number"),
		m_req.body("card")
	);

	stringstream send_data;
	send_data << "{\"answer\":\"" << (succ ? "success" : patient.error())
		<< "\", \"id\":\"" << patient.key() << "\"}";

	m_res.writeHead(200);
	m_res.header("Content-Type", "application/json");
	m_res.end(send_data.str());
}

void Inmate::edit ()
{
	Patient patient(m_db);
	m_res.writeHead(200);
	m_res.header("Content-Type", "application/json");
	if (!patient.load(m_req.body("id"))) {
		m_res.end("Bad id.");
		return;
	}
	patient.name(m_req.body("name"));
	patient.surname(m_req.body("surname"));
	patient.secondName(m_req.body("second_name"));
	patient.date(m_req.body("date"));
	patient.sex(m_req.body("sex"));
	patient.address(m_req.body("address"));
	patient.insurance(m_req.body("insurance"));
	patient.insuranceNumber(m_req.body("insurance_number"));
	patient.card(m_req.body("card"));
	std::string answer = "{\"answer\":\"";
	answer.append(patient.save() ? "success\"}" : "Error\"}");
	m_res.end(answer);
}

void Inmate::search ()
{
	PatientList patients;
	Patient::search(m_db, m_req.body("search_string"), patients);

	sendPatients(patients);
}

void Inmate::all ()
{
	PatientList patients;
	Patient::all(m_db, patients);

	sendPatients(patients);
}

void Inmate::get ()
{
	PatientList patients;
	Patient::get(m_db, m_req.body("id"), patients);

	sendPatients(patients);
}

void Inmate::del ()
{
	bool succ = Patient::del(m_db, m_req.body("id"));
	m_res.writeHead(200);
	m_res.header("Content-Type", "plain/text");
	m_res.end(succ ? "success" : "Error: patient not found");
}

void Inmate::sendPatients (PatientList& patients)
{
	stringstream send_data;
	send_data << "{\"inmates\":[";

	for (auto it = patients.begin(); it != patients.end(); ++it) {
		if (it != patients.begin())
			send_data << ",";

		send_data << "{\"name\":\"" << it->name() << "\",";
		send_data << "\"surname\":\"" << it->surname() << "\",";
		send_data << "\"second_name\":\"" << it->secondName() << "\",";
		send_data << "\"date\":\"" << it->date() << "\",";
		send_data << "\"sex\":\"" << it->sex() << "\",";
		send_data << "\"address\":\"" << it->address() << "\",";
		send_data << "\"insurance\":\"" << it->insurance() << "\",";
		send_data << "\"insurance_number\":\"" << it->insurance_number() << "\",";
		send_data << "\"card\":\"" << it->card() << "\",";
		send_data << "\"id\":\"" << it->key() << "\"}";
	}
	send_data << "]}";

	m_res.writeHead(200);
	m_res.header("Content-Type", "application/json");
	m_res.end(send_data.str());
}

} // namespace doctor
