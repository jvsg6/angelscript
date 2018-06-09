#ifndef INHERIT_H
#define INHERIT_H
#include <angelscript.h>
#include <scriptstdstring/scriptstdstring.h>
#include <scriptbuilder/scriptbuilder.h>

class Inherit
{
    public:
        Inherit(asIScriptEngine *engine, asIScriptContext *ctx, const std::string &module_name, const std::string &class_name);
        ~Inherit();

    void PreDrawPhase();
    void PostDrawPhase();
    int CheckInt();

    private:
        asIScriptContext *ctx;
        asIScriptObject *obj;
        asIScriptFunction *PreDrawPhaseFunc, *PostDrawPhaseFunc;
};

#endif // INHERIT_H
