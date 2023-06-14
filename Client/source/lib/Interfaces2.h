#pragma once

#include <string>
#include <vector>
#include <windows.h>
#include <iostream>
#include <cmath>
#include <objbase.h>

class Constants2
{
    public:
     static IID IID_IDispatch;
     static IID IID_IRoot;
     static IID IID_IRootFactory;
     static CLSID CLSID_Server2;
};

class IRoot : public IUnknown 
{
    public:
        virtual HRESULT __stdcall res_root() = 0;
        virtual HRESULT __stdcall set_num() = 0;
};

class IRootFactory : public IUnknown
{
    public:
        virtual HRESULT __stdcall CreateInstance(const IID& iid, void** object, int license[]) = 0;
};

extern "C" HRESULT __stdcall __declspec(dllexport) DllGetClassObject(const CLSID& clsid, const IID& iid, void** object);