#ifndef koohar_win_hh
#define koohar_win_hh

#ifdef _WIN32

#include <winsock2.h>

#define HandlerRet BOOL WINAPI
typedef DWORD HandlerGet;

static const DWORD QUIT_EVENT = CTRL_CLOSE_EVENT;
static const DWORD TERM_EVENT = CTRL_SHUTDOWN_EVENT;

void setHandler(int Add, PHANDLER_ROUTINE Routine);

#else /* _WIN32 */

#include <signal.h>

typedef void HandlerRet;
typedef int HandlerGet;

enum {
	CTRL_C_EVENT = SIGINT,
	QUIT_EVENT = SIGQUIT,
	TERM_EVENT = SIGTERM
};

void setHandler(int Sig, HandlerRet(* Routine)(HandlerGet));

#endif /* _WIN32 */

#endif // koohar_win_hh
