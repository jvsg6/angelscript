#include "inherit.h"
#include <angelscript.h>
#include <scriptstdstring/scriptstdstring.h>
#include <scriptbuilder/scriptbuilder.h>
Inherit::Inherit(asIScriptEngine *engine, asIScriptContext *ctx, const std::string &module_name, const std::string &class_name):
    ctx(ctx)
{
    asIScriptModule *module = engine->GetModule(module_name.c_str());
    auto type_id=module->GetTypeIdByDecl(class_name.c_str());

    asITypeInfo *type = engine->GetTypeInfoById(type_id);

    PreDrawPhaseFunc=type->GetMethodByDecl("void PreDrawPhase()");
    PostDrawPhaseFunc=type->GetMethodByDecl("void PostDrawPhase()");
    CheckInt=type->GetMethodByDecl("int checkInt()");

    asIScriptFunction *factory = type->GetFactoryByDecl((class_name+" @"+class_name+"()").c_str());
    ctx->Prepare(factory);
    ctx->Execute();
    obj=*(asIScriptObject**)ctx->GetAddressOfReturnValue();
    obj->AddRef();
}

Inherit::~Inherit()
{
    obj->Release();
}

void Inherit::PreDrawPhase()
{
    ctx->Prepare(PreDrawPhaseFunc);
    ctx->SetObject(obj);
    ctx->Execute();
}

void Inherit::PostDrawPhase()
{
    ctx->Prepare(PostDrawPhaseFunc);
    ctx->SetObject(obj);
    ctx->Execute();
}

int Inherit::CheckInt()
{
    ctx->Prepare(CheckInt);
    ctx->SetObject(obj);
    ctx->Execute();
}
