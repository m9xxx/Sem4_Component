#pragma once

#include "Interfaces.h"

class Server : public IPower, public IDispatch
{
    private:
        IPower* pm;
        int num;
        int pow_num;
        int result;
        int refCount;
    public:
        Server();

        virtual HRESULT __stdcall QueryInterface(const IID& iid, void** object);
        virtual ULONG __stdcall AddRef();
        virtual ULONG __stdcall Release();

        virtual HRESULT __stdcall set_num();
        virtual HRESULT __stdcall calc_pow_num();
        virtual HRESULT __stdcall res();

        virtual HRESULT __stdcall GetIDsOfNames(REFIID riid, LPOLESTR* rgszNames, UINT cNames, LCID lcid, DISPID* rgDispId);
        virtual HRESULT __stdcall Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS* pDIspParams,
                                        VARIANT* pVarResult, EXCEPINFO* pExcepInfo, UINT* puArgErr);

        virtual HRESULT __stdcall GetTypeInfoCount(UINT* pctinfo);
        virtual HRESULT __stdcall GetTypeInfo(UINT iTInfo, LCID lcid, ITypeInfo** ppTInfo);

        ~Server();
};

class PowerClassFactory : public IClassFactory, public IPowerFactory
{
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