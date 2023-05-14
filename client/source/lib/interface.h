#pragma once

#include <string>
#include <vector>
#include <windows.h>
#include <iostream>
#include <objbase.h>


class Constants{
    public:
     static IID IID_IUnknown;
     static IID IID_IClassFactory;

     static IID IID_IPower;
     static IID IID_IPowerClassFactory;

     static CLSID CLSID_Server;
     static CLSID CLSID_PowerFactory;
};

class IPower : public IUnknown{
    public:
        virtual HRESULT __stdcall set_num() = 0;
        virtual HRESULT __stdcall pow_num() = 0;
        virtual HRESULT __stdcall res() = 0;
};

class IPowerClassFactory : public IUnknown{
    public:
        virtual HRESULT __stdcall CreateInstance(const IID& iid, void** object, int license[]) = 0;
};

extern "C" HRESULT __stdcall __declspec(dllexport) DllGetClassObject(const CLSID& clsid, const IID& iid, void** object);
