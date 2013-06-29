#include "inmate.hh"

using namespace koohar;
using namespace oodb;
using namespace std;

namespace doctor {

Inmate::CallbackMap Inmate::initCallbacks ()
{
	CallbackMap callbacks;
	callbacks["new"] = &Inmate::add;
	callbacks["edit"] = &Inmate::edit;
	callbacks["search"] = &Inmate::search;
	callbacks["all"] = &Inmate::all;
	callbacks["get"] = &Inmate::get;
	callbacks["del"] = &Inmate::del;
	return callbacks;
}

Inmate::CallbackMap Inmate::m_callbacks = Inmate::initCallbacks();

const std::string Inmate::m_commands[] = {
	"new",
	"edit",
	"search",
	"all",
	"get",
	"del"
};

void Inmate::process (Request& Req, Response& Res, Db& db)
{
	m_req = &Req;
	m_res = &Res;
	m_db = &db;
	load();
}

// private

void Inmate::load ()
{
	for (size_t counter = 0; counter < m_callbacks.size(); ++counter)
		if (m_req->contains(m_commands[counter]))
			return (this->*m_callbacks[m_commands[counter]]) ();
	m_res->badRequest();
}

void Inmate::add ()
{
	Patient patient(*m_db);
	bool succ = patient.add(
		m_req->body("name"),
		m_req->body("surname"),
		m_req->body("second_name"),
		m_req->body("date"),
		m_req->body("sex"),
		m_req->body("address"),
		m_req->body("insurance"),
		m_req->body("insurance_number"),
		m_req->body("card")
	);

	if (!succ) {
		m_res->badRequest();
		return;
	}
	JSON::Object send_data;
	send_data["id"] = patient.key();
	m_res->sendJSON(send_data);
}

void Inmate::edit ()
{
	Patient patient(*m_db);
	if (!patient.load(m_req->body("id"))) {
		m_res->badRequest();
		return;
	}
	patient.name(m_req->body("name"));
	patient.surname(m_req->body("surname"));
	patient.secondName(m_req->body("second_name"));
	patient.date(m_req->body("date"));
	patient.sex(m_req->body("sex"));
	patient.address(m_req->body("address"));
	patient.insurance(m_req->body("insurance"));
	patient.insuranceNumber(m_req->body("insurance_number"));
	patient.card(m_req->body("card"));

	JSON::Object send_data;
	send_data["answer"] = patient.save() ? "success" : "Error";
	m_res->sendJSON(send_data);
}

void Inmate::search ()
{
	PatientList patients;
	Patient::search(*m_db, m_req->body("search_string"), patients);

	sendPatients(patients);
}

void Inmate::all ()
{
	PatientList patients;
	Patient::all(*m_db, patients);

	sendPatients(patients);
}

void Inmate::get ()
{
	PatientList patients;
	Patient::get(*m_db, m_req->body("id"), patients);

	sendPatients(patients);
}

void Inmate::del ()
{
	bool succ = Patient::del(*m_db, m_req->body("id"));
	m_res->writeHead(200);
	m_res->header("Content-Type", "text/plain");
	m_res->end(succ ? "success" : "Error: patient not found");
}

void Inmate::sendPatients (PatientList& patients)
{
	JSON::Object send_data;

	for (auto it = patients.begin(); it != patients.end(); ++it) {
		JSON::Object patient;
		patient["name"] = it->name();
		patient["surname"] = it->surname();
		patient["second_name"] = it->secondName();
		patient["date"] = it->date();
		patient["sex"] = it->sex();
		patient["address"] = it->address();
		patient["insurance"] = it->insurance();
		patient["insurance_number"] = it->insurance_number();
		patient["card"] = it->card();
		patient["id"] = it->key();

		send_data["inmates"].addToArray(patient);
	}
	m_res->sendJSON(send_data);
}

} // namespace doctor
