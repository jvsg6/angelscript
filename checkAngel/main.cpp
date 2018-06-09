#include <QCoreApplication>
#include <angelscript.h>
#include <scriptstdstring/scriptstdstring.h>
#include <scriptbuilder/scriptbuilder.h>
#include <iostream>
#include <string>

#include "inherit.h"
using namespace std;
void MessageCallback(const asSMessageInfo *msg, void *param)
{
  const char *type = "ERR ";
  if( msg->type == asMSGTYPE_WARNING )
    type = "WARN";
  else if( msg->type == asMSGTYPE_INFORMATION )
    type = "INFO";
  printf("%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, type, msg->message);
}

// Print the script string to the standard output stream
void print(string &msg)
{
  printf("%s", msg.c_str());
}

class CObject
{
public:
    int k;
};




int main(int argc, char *argv[])
{

    asIScriptEngine *engine = asCreateScriptEngine();
    RegisterStdString(engine);
    int r = engine->RegisterGlobalFunction("void print(const string &in)", asFUNCTION(print), asCALL_CDECL);
    if( r < 0 )
    {
      printf("Error with Print\n");
      return 0;
    }
    string script;
    //LoadScriptFile("test.as", script);
    //mod->AddScriptSection(".as", script.c_str());
    CScriptBuilder builder;
    r = builder.StartNewModule(engine, "MyModule");
    if( r < 0 )
    {
      printf("Unrecoverable error while starting a new module.\n");
      return 0;
    }
    r = builder.AddSectionFromFile("test.as");
    if( r < 0 )
    {
      printf("Please correct the errors in the script and try again.\n");
      return 0;
    }
    r = builder.BuildModule();
    if( r < 0 )
    {
      printf("Please correct the errors in the script and try again.\n");
      return 0;
    }
    asIScriptContext *ctx = engine->CreateContext();
    /*
    asIScriptModule *module = engine->GetModule("MyModule");
    auto type_id=module->GetTypeIdByDecl("Inherit");
    if( type_id < 0 )
    {
      printf("Wrong With type id.\n");
      return 0;
    }
    asITypeInfo *type = engine->GetTypeInfoById(type_id);
    if( type == nullptr )
    {
      printf("Wrong With type.\n");
      return 0;
    }
    asIScriptFunction *PreDrawPhaseFunc;
    PreDrawPhaseFunc=type->GetMethodByDecl("void PreDrawPhase()");
    asIScriptFunction *factory = type->GetFactoryByDecl("Inherit @Inherit()");*/
    Inherit A(engine, ctx, "MyModule", "Inherit");
    Inherit B(engine, ctx, "MyModule", "Inherit");
    A.PostDrawPhase();
    int bb = A.CheckInt();
    A.IfInt();
    cout<<bb<<endl;
    ctx->Release();
    engine->ShutDownAndRelease();
    return 0;
}

