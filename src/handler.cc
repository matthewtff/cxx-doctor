#include "handler.hh"

#ifdef _WIN32

void setHandler(int Add, PHANDLER_ROUTINE Routine)
{
	SetConsoleCtrlHandler(Routine, Add);
}

#else /* _WIN32 */

void setHandler(int Sig, HandlerRet(* Routine)(HandlerGet))
{
	signal(Sig, Routine);
}

#endif /* _WIN32 */
