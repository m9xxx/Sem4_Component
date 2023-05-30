#pragma once

#include "lib/Interfaces.h"

#include <windows.h>
#include <iostream>

typedef HRESULT __stdcall (*FunctionType) (const CLSID&, const IID&, void**);

class AServer
{
private:
    const char* msg;
public:
    AServer(const char* msg);
    const char* GetMessage();
};

class BServer
{
private:
    IPower* pm;
    BServer(const BServer&) {};
    BServer& operator=(const BServer&) { return *this; };
public:
    BServer();
    BServer(int license[]);

    virtual HRESULT __stdcall set_num();
    virtual HRESULT __stdcall calc_pow_num();
    virtual HRESULT __stdcall res();

    ~BServer();
};