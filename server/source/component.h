#pragma once

#include "interface.h"

class Server : public IPower{
    private:
        IPower* pm;
        int refCount;
        int num;
        int pow_num;
        int result;
    public:
        Server();
        
        virtual HRESULT __stdcall QueryInterface(const IID& iid, void** object);
        virtual ULONG __stdcall AddRef();
        virtual ULONG __stdcall Release();

        virtual HRESULT __stdcall set_num();
        virtual HRESULT __stdcall pow_num();
        virtual HRESULT __stdcall res();
        
        ~Server();
};

class PowerClassFactory : public IClassFactory, public IPowerClassFactory{
    private:
        int refCount;
    public:
        PowerClassFactory();

        virtual HRESULT __stdcall QueryInterface(const IID& iid, void** object);
        virtual ULONG __stdcall AddRef();
        virtual ULONG __stdcall Release();

        virtual HRESULT __stdcall CreateInstance(IUnknown* pUnknownOuter, const IID& iid, void** object);
        virtual HRESULT __stdcall CreateInstance(const IID& iid, void** object, int license[]);

        virtual HRESULT __stdcall LockServer(BOOL bLock);

        ~PowerClassFactory();
};