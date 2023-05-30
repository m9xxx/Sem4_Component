#include "Components.h"

IID Constants::IID_IUnknown = {0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}};
IID Constants::IID_IClassFactory = {0x00000100,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}};

IID Constants::IID_IPower = {0x00000001,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}};
IID Constants::IID_IPowerFactory = {0x00000101,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}};

//{4399E097-D19C-480D-90EE-1AA25B858D31}
CLSID Constants::CLSID_Server = {0x4399E097,0xD19C,0x480D,{0x90,0xEE,0x1A,0xA2,0x5B,0x85,0x8D,0x31}};

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
