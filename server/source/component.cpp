#include "component.h"
using namespace std;

IID Constants::IID_IUnknown = {0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}};
IID Constants::IID_IClassFactory = {0x00000001,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}};

IID Constants::IID_IPower = {0x00000001,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}};
IID Constants::IID_IPowerFactory = {0x00000011,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}};

//91A42CAA-2577-4E80-934E-07DE64502FD6
CLSID Constants::CLSID_Server = {0x91A42CAA,0x2577,0x4E80,{0x93,0x4E,0x07,0xDE,0x64,0x50,0x2F,0xD6}};



Server::Server() 
{
  cout << "Server::Constructor" << endl;

  refCount = 0;

  CoInitialize(NULL);

    IClassFactory* MCF = NULL;

    HRESULT resFactory = CoGetClassObject(Constants::CLSID_Server, CLSCTX_INPROC_SERVER, NULL, Constants::IID_IClassFactory, (void**) &MCF);

    cout << "Server::Constructor::CoGetClassObject" << endl;
    
    if(!SUCCEEDED(resFactory)){
        cout << "No Factory" << endl;
    }
    cout << "Server::Constructor::CreateInstance" << endl;
    HRESULT resInstance = MCF->CreateInstance(NULL, Constants::IID_IPower, (void**) &pm);

    

    if (!SUCCEEDED(resInstance))
    {
        cout << "No instance" << endl;
    }

    HRESULT resQuery = pm->QueryInterface(Constants::IID_IPower, (void**) &pm);

    cout << "Server::Constructor::QueryInterface" << endl;

    if (!SUCCEEDED(resQuery))
    {
        cout << "No QueryInterface" << endl;
    }

    MCF->Release();

  CoUninitialize();

}

HRESULT Server::QueryInterface(const IID& iid, void** object)
{
   cout << "Server QueryInterface" << endl;

   if (iid == Constants::IID_IUnknown)
   {
     *object = (IUnknown*)(IPower*) this;
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
  for (int i = 0; i < b; i++){
    this->result *= a;
  }
  cout << "result = " << this->result << endl;
  return S_OK;

}

Server::~Server()
{
    cout<<"Server::~Server()"<<endl;
    pm->Release();
}

//PowerClassFactory__________________________________________________________________________________

PowerClassFactory::PowerClassFactory(){
    cout<<"PowerClassFactory::PowerClassFactory"<<endl;
    this->refCount = 0;
}

PowerClassFactory::~PowerClassFactory(){
    cout<<"PowerClassFactory::~PowerClassFactory"<<endl;
}


HRESULT PowerClassFactory::QueryInterface(const IID& iid, void** object){
    cout<<"PowerClassFactory::QueryInterface"<<endl;
        if (iid == Constants::IID_IPowerFactory){
            *object = (IUnknown*) (IPowerFactory*) this;
        }
        else{
            *object = NULL;
            return E_NOINTERFACE;
        }

        this->AddRef();
        return S_OK;
}

ULONG PowerClassFactory::AddRef(){
    refCount++;
    return refCount;
}

ULONG PowerClassFactory::Release(){
    refCount--;
    if (refCount == 0){
        delete this;
    }
    return refCount;
}

HRESULT PowerClassFactory::CreateInstance(IUnknown* pUnknownOuter,const IID& iid, void** object){
    cout<<"PowerClassFactory::CreateInstance"<<endl;

    if (pUnknownOuter != NULL){
        return E_NOTIMPL;
    }
    IUnknown* s = (IUnknown*)(IPower*) new Server();

    HRESULT res = s->QueryInterface(iid, object);

    return res;
}

HRESULT PowerClassFactory::CreateInstance(const IID& iid, void** object, int license[]){
    cout<<"PowerClassFactory::CreateInstance with license"<<endl;
    HRESULT res = E_NOTIMPL;

    if (license != NULL){
        IUnknown*s = (IUnknown*)(IPower*) new Server();

        s->AddRef();
        res = s->QueryInterface(iid, object);
        s->Release();
    }
    return res;
}

HRESULT PowerClassFactory::LockServer(BOOL bLock){
    return S_OK;
}