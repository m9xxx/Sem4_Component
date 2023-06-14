#include "Components.h"

BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            // attach to process
            // return FALSE to fail DLL load
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

extern "C" HRESULT __stdcall __declspec(dllexport) DllGetClassObject(const CLSID& clsid, const IID& iid, void** object)
{
    std::cout<<"Global GetClassObject"<<std::endl;

    IUnknown* s = NULL;

    if (clsid == Constants::CLSID_Server)
    {
        s = (IUnknown*) (IClassFactory*) new PowerClassFactory();
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

