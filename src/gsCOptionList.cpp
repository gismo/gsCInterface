
#include <gismo.h>
#include <gsCInterface/gsCTypes.h>
#include <gsCInterface/gsMacros.h>
#include <gsCInterface/gsCOptionList.h>

using namespace gismo;

#ifdef __cplusplus
extern "C"
{
#endif

GISMO_EXPORT gsCOptionList * gsOptionList_create()
{
    return reinterpret_cast<gsCOptionList*>(new gsOptionList());
}

GISMO_EXPORT void gsOptionList_delete(gsCOptionList * ol)
{
    delete reinterpret_cast<gsOptionList*>(ol);
}

GISMO_EXPORT void gsOptionList_print(gsCOptionList * ol)
{
    reinterpret_cast<gsOptionList*>(ol)->print(gsInfo);
}

GISMO_EXPORT void gsOptionList_addString(gsCOptionList * ol, const char * label, const char * description, const char * value)
{
    reinterpret_cast<gsOptionList*>(ol)->addString(label, description, value);
}

GISMO_EXPORT void gsOptionList_addInt(gsCOptionList * ol, const char * label, const char * description, int value)
{
    reinterpret_cast<gsOptionList*>(ol)->addInt(label, description, value);
}

GISMO_EXPORT void gsOptionList_addReal(gsCOptionList * ol, const char * label, const char * description, double value)
{
    reinterpret_cast<gsOptionList*>(ol)->addReal(label, description, value);
}

GISMO_EXPORT void gsOptionList_addSwitch(gsCOptionList * ol, const char * label, const char * description, int value)
{
    reinterpret_cast<gsOptionList*>(ol)->addSwitch(label, description, value);
}

GISMO_EXPORT void gsOptionList_setString(gsCOptionList * ol, const char * label, const char * value)
{
    reinterpret_cast<gsOptionList*>(ol)->setString(label, value);
}

GISMO_EXPORT void gsOptionList_setInt(gsCOptionList * ol, const char * label, int value)
{
    reinterpret_cast<gsOptionList*>(ol)->setInt(label, value);
}

GISMO_EXPORT void gsOptionList_setReal(gsCOptionList * ol, const char * label, double value)
{
    reinterpret_cast<gsOptionList*>(ol)->setReal(label, value);
}

GISMO_EXPORT void gsOptionList_setSwitch(gsCOptionList * ol, const char * label, int value)
{
    reinterpret_cast<gsOptionList*>(ol)->setSwitch(label, value);
}

GISMO_EXPORT char* gsOptionList_getString(gsCOptionList * ol, const char * label)
{
    return const_cast<char*>(reinterpret_cast<gsOptionList*>(ol)->getString(label).c_str());
}

GISMO_EXPORT int gsOptionList_getInt(gsCOptionList * ol, const char * label)
{
    return reinterpret_cast<gsOptionList*>(ol)->getInt(label);
}

GISMO_EXPORT double gsOptionList_getReal(gsCOptionList * ol, const char * label)
{
    return reinterpret_cast<gsOptionList*>(ol)->getReal(label);
}

GISMO_EXPORT int gsOptionList_getSwitch(gsCOptionList * ol, const char * label)
{
    return reinterpret_cast<gsOptionList*>(ol)->getSwitch(label);
}

#ifdef __cplusplus
}
#endif