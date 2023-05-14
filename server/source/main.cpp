#include "component.h"

extern "C" HRESULT __stdcall __declspec(dllexport) DllGetClassObject(const CLSID& clsid, const IID& iid, void** object)
{
    std::cout<<"Global GetClassObject"<<std::endl;

    IUnknown* s = NULL;

    if (clsid == Constants::CLSID_Server)
    {
        s = (IUnknown*) (IClassFactory*) new PowerClassFactory(); //PowerClassFactory
    }
    else
    {
        *object = NULL;
        return E_NOTIMPL;
    }

    s->AddRef();
    HRESULT res = s->QueryInterface(iid, object);
    s->Release();

    return S_OK;
}

BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            std::cout<<"PROCESS INFO DLL CONNECTED"<<std::endl;
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
