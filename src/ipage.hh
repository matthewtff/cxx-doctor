#ifndef doctor_ipage_hh
#define doctor_ipage_hh

#include <koohar.hh>
#include <oodb.hh>

namespace doctor {

class IPage {

public:

	IPage () {}

	virtual ~IPage () {}

	virtual void process (koohar::Request& Req, koohar::Response& Res,
		oodb::Db& db) = 0;
	virtual void clear () = 0;

}; // class IPage

} // namespace doctor

#endif // doctor_ipage_hh
