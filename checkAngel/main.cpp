#include <QCoreApplication>
#include <angelscript.h>
#include <scriptstdstring/scriptstdstring.h>
#include <scriptbuilder/scriptbuilder.h>
#include <iostream>
#include <string>

#include "inherit.h"
#include "inherit_2.h"
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




void print_2(string &msg)
{
  printf("engine_2_%s", msg.c_str());
}



int main(int argc, char *argv[])
{

    asIScriptEngine *engine = asCreateScriptEngine();
    asIScriptEngine *engine_2 = asCreateScriptEngine();
    RegisterStdString(engine);
    int r = engine->RegisterGlobalFunction("void print(const string &in)", asFUNCTION(print), asCALL_CDECL);
    if( r < 0 )
    {
      printf("Error with Print\n");
      return 0;
    }


    RegisterStdString(engine_2);
    r = engine_2->RegisterGlobalFunction("void print(const string &in)", asFUNCTION(print_2), asCALL_CDECL);
    if( r < 0 )
    {
      printf("Error with Print\n");
      return 0;
    }



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



    CScriptBuilder builder_2;
    r = builder_2.StartNewModule(engine, "MyModule_2");
    if( r < 0 )
    {
      printf("Unrecoverable error while starting a new module.\n");
      return 0;
    }
    r = builder_2.AddSectionFromFile("test_2.as");
    if( r < 0 )
    {
      printf("Please correct the errors in the script and try again.\n");
      return 0;
    }
    r = builder_2.BuildModule();
    if( r < 0 )
    {
      printf("Please correct the errors in the script and try again.\n");
      return 0;
    }
    asIScriptContext *ctx_2 = engine->CreateContext();



    CScriptBuilder builder_3;
    r = builder_3.StartNewModule(engine_2, "MyModule_3");
    if( r < 0 )
    {
      printf("Unrecoverable error while starting a new module.\n");
      return 0;
    }
    r = builder_3.AddSectionFromFile("test_3.as");
    if( r < 0 )
    {
      printf("Please correct the errors in the script and try again.\n");
      return 0;
    }
    r = builder_3.BuildModule();
    if( r < 0 )
    {
      printf("Please correct the errors in the script and try again.\n");
      return 0;
    }
    asIScriptContext *ctx_3 = engine_2->CreateContext();


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
    A.PostDrawPhase();
    int bb = A.CheckInt();
    A.IfInt();
    cout<<bb<<endl;
    cout<<endl;


    Inherit_2 B(engine, ctx_2, "MyModule_2", "Inherit_2");
    B.PostDrawPhase();
    int cc = B.CheckInt();
    B.IfInt();
    cout<<cc<<endl;
    cout<<endl;


    A.PostDrawPhase();
    bb = A.CheckInt();
    A.IfInt();
    cout<<bb<<endl;
    cout<<endl;


    Inherit C(engine_2, ctx_3, "MyModule_3", "Inherit");
    C.PostDrawPhase();
    bb = C.CheckInt();
    C.IfInt();
    cout<<bb<<endl;
    cout<<endl;

    cout<<engine->GetModuleCount()<<endl;
    ctx->Release();
    ctx_2->Release();
    ctx_3->Release();
    engine->ShutDownAndRelease();
    engine_2->ShutDownAndRelease();
    return 0;
}

