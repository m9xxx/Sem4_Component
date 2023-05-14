#include "wrapper.h"

using namespace std;

AServer::AServer(const char* msg)
{
    this->msg = msg;
}

const char* AServer::GetMessage()
{
    return msg;
}

BServer::BServer()
{
    cout << "Bserver" << endl;
    CoInitialize(NULL);

    IClassFactory* MCF = NULL;

    HRESULT resFactory = CoGetClassObject(Constants::CLSID_Server, CLSCTX_INPROC_SERVER, NULL, Constants::IID_IClassFactory, (void**) &MCF);


    if(!SUCCEEDED(resFactory)){
        throw AServer("No Factory");
    }
    
    HRESULT resInstance = MCF->CreateInstance(NULL, Constants::IID_IPower, (void**) &ppm);

    if (!SUCCEEDED(resInstance))
    {
        throw AServer("No instance");
    }

    HRESULT resQuery = ppm->QueryInterface(Constants::IID_IPower, (void**) &pm);

    if (!SUCCEEDED(resQuery))
    {
        throw AServer("No QueryInterface");
    }

    MCF->Release();
}

BServer::BServer(int license[])
{
    cout << "Bserver::license" << endl;
    CoInitialize(NULL);

    IClassFactory* MCF = NULL;

    HRESULT resFactory = CoGetClassObject(Constants::CLSID_Server, CLSCTX_INPROC_SERVER, NULL, Constants::IID_IClassFactory, (void**) &MCF);


    if(!SUCCEEDED(resFactory)){
        throw AServer("No Factory");
    }


    HRESULT resInstance = MCF->CreateInstance(NULL, Constants::IID_IPower, (void**) &ppm);

    if (!SUCCEEDED(resInstance))
    {
        throw AServer("No license");
    }

    HRESULT resQuery = ppm->QueryInterface(Constants::IID_IPower, (void**) &pm);

    if (!SUCCEEDED(resQuery))
    {
        throw AServer("No QueryInterface");
    }

    MCF->Release();
}

HRESULT __stdcall BServer::set_num()
{
    return dm->set_num();
}

HRESULT __stdcall BServer::pow_num()
{
    return dm->pow_num();
}

HRESULT __stdcall BServer::res(){
    return dm->res();
}

BServer::~BServer()
{
    dm->Release();
    pm->Release();

    CoUninitialize();
}
