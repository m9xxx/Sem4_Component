#include "Components.h"

IID Constants::IID_IUnknown = {0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}};
IID Constants::IID_IClassFactory = {0x00000100,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}};

IID Constants::IID_IPower = {0x00000001,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}};
IID Constants::IID_IPowerFactory = {0x00000101,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}};

//{8428A10A-C00C-4A71-A2AA-917E6FE388D4}
CLSID Constants::CLSID_Server = {0x8428A10A,0xC00C,0x4A71,{0xA2,0xAA,0x91,0x7E,0x6F,0xE3,0x88,0xD4}};

IID Constants::IID_IDispatch =  {0x00020400,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}};
IID Constants::IIDNULL = {0x10000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}};

using namespace std;

Server::Server()
{
    cout<<"Server::Server()"<<endl;
    refCount = 0;
}

HRESULT Server::QueryInterface(const IID& iid, void** object)
{
    cout<<"EquationSolver::QueryInterface"<<endl;
    if (iid == Constants::IID_IUnknown)
    {
        *object = (IUnknown*) (IPower*) this;
    }
    else if (iid == Constants::IID_IPower)
    {
        *object = static_cast<IPower*>(this);
    }
    else if(iid == Constants::IID_IDispatch) 
    {
        *object = static_cast<IDispatch*>(this);
    }
    else
    {
        *object = NULL;
        return E_NOINTERFACE;
    }
    
    this->AddRef();
    return S_OK;
}

ULONG Server::AddRef()
{
    refCount++;

    return refCount;
}

ULONG Server::Release()
{
    refCount--;

    if (refCount == 0)
    {
        delete this;
    }
    
    return refCount;
}

HRESULT Server::set_num()
{
    cout << "Set num func, enter num" << endl;
    cin >> this->num;
    cout << "Num entered succesfully, num = " << this->num << endl;
    return S_OK;
}

HRESULT Server::calc_pow_num()
{
    cout << "Set pow func, enter pow" << endl;
    cin >> this->pow_num;
    cout << "Pow entered succesfully, pow = " << this->pow_num << endl;
    return S_OK;
}

HRESULT Server::res()
{
    int a = this->num;
    int b = this->pow_num;
    this->result = a;
    for (int i = 0; i < b-1; i++) {
        this->result *= a;
    }
    cout << "result : " << this->num << "^" << this->pow_num << " = " << this->result << endl;
    return S_OK;
}

Server::~Server()
{
    cout<<"Server::~Server()"<<endl;
}

HRESULT __stdcall Server::GetTypeInfoCount(UINT* pctinfo) {
    cout << "Server::GetTypeInfoCount" << endl;
    return S_OK;
}

HRESULT __stdcall Server::GetTypeInfo(UINT iTInfo, LCID lcid, ITypeInfo** ppTInfo) {
    cout << "Server::GetTypeInfo" << endl;
}

HRESULT __stdcall Server::GetIDsOfNames(REFIID riid, LPOLESTR* rgszNames, UINT cNames,
                                        LCID lcid, DISPID* rgDispId) {
    cout << "Server::GetIDsOfNames" << std::endl;
    if(cNames != 1) {return E_NOTIMPL;}
   if(wcscmp(rgszNames[0], L"set_num")==0) {
        rgDispId[0] = 1;
   }
   else if(wcscmp(rgszNames[0], L"calc_pow_num")==0) {
        rgDispId[0] = 2;
   }
   else if(wcscmp(rgszNames[0], L"res")==0) {
        rgDispId[0] = 3;
   }
   else {
    return E_NOTIMPL;
   }
   return S_OK;
    }

HRESULT _stdcall Server::Invoke(DISPID dispIdMember, REFIID riid, LCID lcid,WORD wFlags, DISPPARAMS* pDispParams,VARIANT* pVarResult,
                             EXCEPINFO* pExcepInfo, UINT* puArgErr) 
                             {
    std::cout << "MyVector::Invoke" << std::endl;
    if(dispIdMember == 1) {
        set_num();
    }
    else if (dispIdMember == 2) {
        calc_pow_num();
    }
    else if (dispIdMember == 3) {
        res();
    }
    else {
        return E_NOTIMPL;
    }
    return S_OK;                         
    }

// -----------------------------------------------------------------------------------------

PowerClassFactory::PowerClassFactory()
{
    cout<<"PowerClassFactory::PowerClassFactory()"<<endl;
    this->refCount = 0;
}

HRESULT PowerClassFactory::QueryInterface(const IID& iid, void** object)
{
    cout<<"PowerClassFactory::QueryInterface"<<endl;

    if (iid == Constants::IID_IClassFactory)
    {
        *object = (IUnknown*) (IClassFactory*) this;
    }
    else if (iid == Constants::IID_IClassFactory)
    {
        *object = (IUnknown*) (IClassFactory*) this;
    }
    else
    {
        *object = NULL;
        return E_NOINTERFACE;
    }
    
    this->AddRef();
    return S_OK;
}

ULONG PowerClassFactory::AddRef()
{
    refCount++;

    return refCount;
}

ULONG PowerClassFactory::Release()
{
    refCount--;

    if (refCount == 0)
    {
        delete this;
    }
    
    return refCount;
}

HRESULT PowerClassFactory::CreateInstance(IUnknown* pUnknownOuter, const IID& iid, void** object)
{
    cout<<"PowerClassFactory::CreateInstance"<<endl;

    if (pUnknownOuter != NULL)
    {
        return E_NOTIMPL;
    }

    IUnknown* s = (IUnknown*) (IPower*) new Server();

    HRESULT res = s->QueryInterface(iid, object);
    
    return res;
}

HRESULT PowerClassFactory::CreateInstance(const IID& iid, void** object, int license[])
{
    cout<<"PowerClassFactory::CreateInstance with license"<<endl;

    HRESULT res = E_NOTIMPL;

    if (license != NULL)
    {
        IUnknown* s = (IUnknown*) (IPower*) new Server();

        res = s->QueryInterface(iid, object);
    }
    
    return res;
}

HRESULT PowerClassFactory::LockServer(BOOL bLock)
{
    return S_OK;
}

PowerClassFactory::~PowerClassFactory()
{
    cout<<"PowerClassFactory::~PowerClassFactory()"<<endl;
}
