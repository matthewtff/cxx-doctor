#ifndef doctor_sync_hh
#define doctor_sync_hh

#include <string>

#include <oodb/oodb.hh>

namespace doctor {

bool syncronizeDb (oodb::Db& db, const std::string& ip, const short port);

} // namespace doctor

#endif // doctor_sync_hh
