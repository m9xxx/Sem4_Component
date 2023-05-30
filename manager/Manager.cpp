#include <windows.h>
#include <iostream>

#include "lib/interfaces.h"
#include "lib/interfaces2.h"

typedef HRESULT __stdcall (*FunctionType) (const CLSID&, const IID&, void**);

extern "C" HRESULT __stdcall __declspec(dllexport) CreateInstance(const CLSID& clsid, const IID& iid, void** object)
{
    IClassFactory* s = NULL;
    HRESULT res = GetClassObject(clsid, IID_IClassFactory, (void**) &s);

    if (res == S_OK)
    {
        if (iid == IID_IEquationX)
        {
            IEquationX* iex = NULL;

            res = s->CreateInstance(iid, (void**) &iex);
            *object = (IUnknown*) (IEquationX*) iex;
        }
        else if (iid == IID_IEquationY)
        {
            IEquationY* iey = NULL;

            res = s->CreateInstance(iid, (void**) &iey);
            *object = (IUnknown*) (IEquationY*) iey;
        }
    }
    else
    {
        std::cout<<"Manager CreateInstance ERROR "<<res<<std::endl;
    }

    s->Release();
   
    return res;
}

extern "C" HRESULT __stdcall __declspec(dllexport) GetClassObject(const CLSID& clsid, const IID& iid, void** object)
{
    const char* path;

    if (clsid == CLSID_ESolverClassFactory)
    {
        path = "./build/server/server.dll";
    }
    else if (clsid == CLSID_AdvESolverClassFactory)
    {
        path = "./build/server/server2.dll";
    }
    else
    {
        return E_NOCOMPONENT;
    }
    
    HINSTANCE h = LoadLibrary(path);

    if (!h)
    {
           std::cout<<"No dll!!!"<<std::endl;
    }

    FunctionType GCO=(FunctionType) GetProcAddress(h,"GetClassObject");

    if (!GCO)
    {
          std::cout << "No dll function" << std::endl;
    }

    return GCO(clsid, iid, object);
}

BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            std::cout<<"MANAGER DLL CONNECTED"<<std::endl;
            break;

        case DLL_PROCESS_DETACH:
            // detach from process
            break;

        case DLL_THREAD_ATTACH:
            // attach to thread
            break;

        case DLL_THREAD_DETACH:
            // detach from thread
            break;
    }

    return TRUE; // succesful
}