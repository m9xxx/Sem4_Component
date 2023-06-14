#include "Components2.h"

IID Constants::IID_IUnknown = {0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}};
IID Constants::IID_IClassFactory = {0x00000100,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}};

IID Constants::IID_IPower = {0x00000001,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}};
IID Constants::IID_IPowerFactory = {0x00000101,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}};

//{8428A10A-C00C-4A71-A2AA-917E6FE388D4}
CLSID Constants::CLSID_Server = {0x8428A10A,0xC00C,0x4A71,{0xA2,0xAA,0x91,0x7E,0x6F,0xE3,0x88,0xD4}};

IID Constants::IID_IDispatch =  {0x00020400,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}};
IID Constants::IIDNULL = {0x10000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}};

IID Constants2::IID_IRoot = {0x00000004,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}};
IID Constants2::IID_IRootFactory = {0x00000005,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}};

// {89F2E888-DE98-4EF6-B29C-98E9F9CD00D8}
CLSID Constants2::CLSID_Server2 = {0x89F2E888, 0xDE98, 0x4EF6, {0xB2,0x9C, 0x98, 0xE9, 0xF9, 0xCD, 0x00, 0xD8}};

using namespace std;

Server2::Server2()
{
    cout<<"Server2::Server2()"<<endl;
    refCount = 0;
    CoInitialize(NULL);

    IClassFactory* pCF = NULL;

    HRESULT resFactory = CoGetClassObject(Constants::CLSID_Server, CLSCTX_INPROC_SERVER, NULL, Constants::IID_IClassFactory, (void**)&pCF);

    if(!SUCCEEDED(resFactory)) {
    std::cout << "No factory detected. Please, try again." << std::endl;
    }

    HRESULT resInstance = pCF -> CreateInstance(NULL, Constants::IID_IPower, (void**)&pm);

    if (!SUCCEEDED(resInstance)) {
    std::cout << "No such function detected. Please, try again." << std::endl;
    }

    HRESULT resQuery = pm-> QueryInterface(Constants2::IID_IRoot, (void**)&rm);

    if(!SUCCEEDED(resQuery)) {
    std::cout << "Error while trying to perform server2/component.cpp:pm -> QueryInterface " << std::endl;
    }

    pCF -> Release();
    CoUninitialize();
}

HRESULT Server2::QueryInterface(const IID& iid, void** object)
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
    else if (iid == Constants2::IID_IRoot)
    {
        *object = static_cast<IRoot*>(this);
    }
    else
    {
        *object = NULL;
        return E_NOINTERFACE;
    }
    
    this->AddRef();
    return S_OK;
}

ULONG Server2::AddRef()
{
    refCount++;

    return refCount;
}

ULONG Server2::Release()
{
    refCount--;

    if (refCount == 0)
    {
        delete this;
    }
    
    return refCount;
}

HRESULT Server2::set_num()
{
    cout << "Set num func, enter num" << endl;
    cin >> this->num;
    cout << "Num entered succesfully, num = " << this->num << endl;
    return S_OK;
}

HRESULT Server2::res_root()
{
    int a = this->num;
    this->root_result = a;
    this->root_result *= sqrt(this->num);
    cout << "result : " << "sqrt(" << this->num << ")" << " = " << this->root_result << endl;
    return S_OK;
}

HRESULT Server2::calc_pow_num()
{
    cout << "Set pow func, enter pow" << endl;
    cin >> this->pow_num;
    cout << "Pow entered succesfully, pow = " << this->pow_num << endl;
    return S_OK;
}

HRESULT Server2::res()
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
Server2::~Server2()
{
    cout<<"Server2::~Server2()"<<endl;
    rm -> Release();
    pm -> Release();
}

HRESULT __stdcall Server2::GetTypeInfoCount(UINT* pctinfo) {
    std::cout << "Server2::GetTypeInfoCount" << std::endl;
    return S_OK;
}

HRESULT __stdcall Server2::GetTypeInfo(UINT iTInfo, LCID lcid, ITypeInfo** ppTInfo) {
    std::cout << "Server2::GetTypeInfo" << std::endl;
}

HRESULT __stdcall Server2::GetIDsOfNames(REFIID riid, LPOLESTR* rgszNames, UINT cNames,
                                        LCID lcid, DISPID* rgDispId) {

    std::cout << "Server2::GetIDsOfNames" << std::endl;

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
   else if(wcscmp(rgszNames[0], L"res_root")==0) {
        rgDispId[0] = 4;
   }
   else {
    return E_NOTIMPL;
   }

   return S_OK;

    }

HRESULT _stdcall Server2::Invoke(DISPID dispIdMember, REFIID riid, LCID lcid,WORD wFlags, DISPPARAMS* pDispParams,VARIANT* pVarResult,
                             EXCEPINFO* pExcepInfo, UINT* puArgErr) 
                             {

    std::cout << "Server2::Invoke" << std::endl;

    if(dispIdMember == 1) {
        set_num();
    }

    else if (dispIdMember == 2) {
        calc_pow_num();
    }

    else if (dispIdMember == 3) {
        res();
    }
        else if (dispIdMember == 4) {
        res_root();
    }

    else {
        return E_NOTIMPL;
    }
    return S_OK;
                             }

// -----------------------------------------------------------------------------------------

RootClassFactory::RootClassFactory()
{
    cout<<"RootClassFactory::RootClassFactory()"<<endl;
    this->refCount = 0;
}

HRESULT RootClassFactory::QueryInterface(const IID& iid, void** object)
{
    cout<<"RootClassFactory::QueryInterface"<<endl;

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

ULONG RootClassFactory::AddRef()
{
    refCount++;

    return refCount;
}

ULONG RootClassFactory::Release()
{
    refCount--;

    if (refCount == 0)
    {
        delete this;
    }
    
    return refCount;
}

HRESULT RootClassFactory::CreateInstance(IUnknown* pUnknownOuter, const IID& iid, void** object)
{
    cout<<"RootClassFactory::CreateInstance"<<endl;

    if (pUnknownOuter != NULL)
    {
        return E_NOTIMPL;
    }

    IUnknown* s = (IUnknown*) (IRoot*) new Server2();

    HRESULT res = s->QueryInterface(iid, object);
    
    return res;
}

HRESULT RootClassFactory::CreateInstance(const IID& iid, void** object, int license[])
{
    cout<<"RootClassFactory::CreateInstance with license"<<endl;

    HRESULT res = E_NOTIMPL;

    if (license != NULL)
    {
        IUnknown* s = (IUnknown*) (IRoot*) new Server2();

        res = s->QueryInterface(iid, object);
    }
    
    return res;
}

HRESULT RootClassFactory::LockServer(BOOL bLock)
{
    return S_OK;
}

RootClassFactory::~RootClassFactory()
{
    cout<<"RootClassFactory::~RootClassFactory()"<<endl;
}
