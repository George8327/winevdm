#include <Windows.h>
//PROGMAN.EXEなどでCOMMDLGが読み込まれなかったので修正
HMODULE LoadLibraryAWrapper(const char *name)
{
    return LoadLibraryA(name);
}
