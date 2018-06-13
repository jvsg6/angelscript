#include "inherit_2.h"

#include <angelscript.h>
#include <scriptstdstring/scriptstdstring.h>
#include <scriptbuilder/scriptbuilder.h>
#include <iostream>


using namespace std;
Inherit_2::Inherit_2(asIScriptEngine *engine, asIScriptContext *ctx, const std::string &module_name, const std::string &class_name):
    ctx(ctx)
{
    asIScriptModule *module = engine->GetModule(module_name.c_str());
    auto type_id=module->GetTypeIdByDecl(class_name.c_str());

    asITypeInfo *type = engine->GetTypeInfoById(type_id);

    PreDrawPhaseFunc=type->GetMethodByDecl("void PreDrawPhase()");
    PostDrawPhaseFunc=type->GetMethodByDecl("void PostDrawPhase()");
    CheckIntFunc=type->GetMethodByDecl("int CheckInt()");
    IfIntFunc=type->GetMethodByDecl("void IfInt(int a)");
    //IfIntFunc=type->GetMethodByDecl("void IfInt()");

    asIScriptFunction *factory = type->GetFactoryByDecl((class_name+" @"+class_name+"()").c_str());
    ctx->Prepare(factory);
    ctx->Execute();
    obj=*(asIScriptObject**)ctx->GetAddressOfReturnValue();
    obj->AddRef();
}

Inherit_2::~Inherit_2()
{
    obj->Release();
}

void Inherit_2::PreDrawPhase()
{
    ctx->Prepare(PreDrawPhaseFunc);
    ctx->SetObject(obj);
    ctx->Execute();
}

void Inherit_2::PostDrawPhase()
{
    ctx->Prepare(PostDrawPhaseFunc);
    ctx->SetObject(obj);
    ctx->Execute();
}

int Inherit_2::CheckInt()
{
    ctx->Prepare(CheckIntFunc);
    ctx->SetObject(obj);
    int r = ctx->Execute();
    if( r == asEXECUTION_FINISHED )
    {
      // The return value is only valid if the execution finished successfully
      asDWORD ret = ctx->GetReturnDWord();
      return ret;
    }
    else
    {
        cout<<"Smth wrong with checkInt"<<endl;
        return -1;
    }

}

void Inherit_2::IfInt()
{
    ctx->Prepare(IfIntFunc);
    int r = ctx->SetObject(obj);
    if(r<0)
        {
            cout<<"Smth Wrong with obj";
        }
    r = ctx->SetArgDWord(0, 1);
    if(r<0)
    {
        cout<<"Smth Wrong with args";
    }
    r = ctx->Execute();
    if( r == asEXECUTION_FINISHED )
    {
      // The return value is only valid if the execution finished successfully
       cout<<"Allok"<<endl;
    }
    else
    {
        cout<<"Smth wrong with ifInt"<<endl;
    }
}
