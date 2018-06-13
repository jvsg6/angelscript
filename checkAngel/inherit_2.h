#ifndef INHERIT_2_H
#define INHERIT_2_H
#include <angelscript.h>
#include <scriptstdstring/scriptstdstring.h>
#include <scriptbuilder/scriptbuilder.h>

class Inherit_2
{
    public:
        Inherit_2(asIScriptEngine *engine, asIScriptContext *ctx, const std::string &module_name, const std::string &class_name);
        ~Inherit_2();

    void PreDrawPhase();
    void PostDrawPhase();
    int CheckInt();
    void IfInt();

    private:
        asIScriptContext *ctx;
        asIScriptObject *obj;
        asIScriptFunction *PreDrawPhaseFunc, *PostDrawPhaseFunc, *CheckIntFunc, *IfIntFunc;
};


#endif // INHERIT_2_H
