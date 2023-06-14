#include "lib/Interfaces.h"
#include "lib/Interfaces2.h"
#include <windows.h>
#include <iostream>

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


int main() 
{
	CoInitialize(NULL);

CLSID CurrentComponent;
CLSID CLSID_Server;
CLSID CLSID_Server2;

{

const wchar_t* progID = L"M9X";

if(progID = L"9A9") {

    HRESULT resCLSID_ProgID = CLSIDFromProgID(progID, &CLSID_Server);

        if(!(SUCCEEDED(resCLSID_ProgID))) {
            throw "No CLSID form ProgID";
        }
        else {
            std::cout << "CLSID form ProgID OK!" << std::endl;
            CurrentComponent = CLSID_Server;
        }
}
else if (progID = L"M9X") {

    HRESULT resCLSID_ProgID = CLSIDFromProgID(progID, &CLSID_Server2);

        if(!(SUCCEEDED(resCLSID_ProgID))) {
            throw "No CLSID form ProgID";
        }
        else {
            std::cout << "CLSID form ProgID OK!" << std::endl;
            CurrentComponent = CLSID_Server2;
        }
    }
}

IClassFactory* PCF = NULL;

HRESULT resFactory = CoGetClassObject(CurrentComponent, CLSCTX_INPROC_SERVER, NULL, Constants::IID_IClassFactory, (void**) &PCF);

if (!SUCCEEDED(resFactory))
{
std::cout << "No factory" << std::endl;
}

IPower* ip = NULL;
HRESULT resInstance = PCF->CreateInstance(NULL, Constants::IID_IPower, (void**) &ip);

if (!SUCCEEDED(resInstance))
{
std::cout << "No instance" << std::endl;
}

IRoot* ir = NULL;
HRESULT resQuery = ip->QueryInterface(Constants2::IID_IRoot, (void**) &ir);

if (!SUCCEEDED(resQuery))
{
std::cout << "No QueryInterface" << std::endl;
}

// Summation* sum = NULL;
// HRESULT resQuery2 = sub->QueryInterface(Constants::IID_ISummation, (void**) &sum);

// if (!SUCCEEDED(resQuery2))
// {
// std::cout << "No QueryInterface 2" << std::endl;
// }

// fv->fill();
// fv->print();

// sub->subtract();
// sum->sum();
	
// sub->Release();
// sum->Release();
ip->set_num();
ip->calc_pow_num();
ip->res();
// ir->set_num();
ir->res_root();
PCF->Release();
  
IDispatch* pDisp = NULL;
    HRESULT resQueryDisp = ip -> QueryInterface(Constants::IID_IDispatch, (void**)&pDisp);
    if(!(SUCCEEDED(resQueryDisp))) throw "No query dispatch";

    DISPID dispid;

    int namesCount = 1;
    OLECHAR** names = new OLECHAR*[namesCount];
    OLECHAR* name = const_cast<OLECHAR*>(L"set_num");
    names[0] = name;

    HRESULT resID_Name = pDisp -> GetIDsOfNames(
                                                    Constants::IIDNULL,
                                                    names,
                                                    namesCount,
                                                    GetUserDefaultLCID(),
                                                    &dispid
    );

    if(!(SUCCEEDED(resID_Name))) {
        std::cout << "No ID of name " << std::endl;
    }
    else {
        DISPPARAMS dispparamsNoArgs = {
                                        NULL,
                                        NULL,
                                        0,
                                        0,
                                       };

        HRESULT resInvoke = pDisp -> Invoke(
                                                dispid,
                                                Constants::IIDNULL,
                                                GetUserDefaultLCID(),
                                                DISPATCH_METHOD,
                                                &dispparamsNoArgs,
                                                NULL,
                                                NULL,
                                                NULL
                                            );

        if(!(SUCCEEDED(resInvoke))) {
            std::cout << "Invoke error!" << std::endl;
        }
    }
  CoUninitialize();  
	return 0;
}
// {
// 	std::cout << "Client start" << std::endl;

// 	try {
// 		BServer b;
// 		b.set_num();
// 		b.calc_pow_num();
// 		b.res();
// 	}
// 	catch (AServer& a) {
// 		std::cout << a.GetMessage() << std::endl;
// 	}

// 	return 0;
// }