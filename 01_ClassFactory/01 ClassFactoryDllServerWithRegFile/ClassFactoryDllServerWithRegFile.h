#pragma once
//Class Factory Dll Server With Reg File
class ISum:public IUnknown
{
public: 
	//Create spcfic method declaration
	virtual HRESULT __stdcall SumOfTwoInteger(int, int, int*) =0;//Pure Virtual Func
};

class ISub:public IUnknown
{
public:
	//create specific method declartion
	virtual HRESULT __stdcall SubOfTwoInteger(int, int, int*) = 0; //Pure Virtual Func

};

class IMult:public IUnknown
{
public:
	//create specific method declartion
	virtual HRESULT __stdcall MultOfTwoInteger(int, int, int*) = 0; //Pure Virtual Func

};

// {99AA1107-8075-4619-AEA4-A5AA771B7506}
static const CLSID CLSID_SumSub =
{ 0x99aa1107, 0x8075, 0x4619, { 0xae, 0xa4, 0xa5, 0xaa, 0x77, 0x1b, 0x75, 0x6 } };

// {64649219-43E7-4E00-8E8F-9F19F3963EA8}
static const IID IID_ISum =
{ 0x64649219, 0x43e7, 0x4e00, { 0x8e, 0x8f, 0x9f, 0x19, 0xf3, 0x96, 0x3e, 0xa8 } };

// {2E776852-5D2F-484E-8078-BC450A273208}
static const IID IID_ISub=
{ 0x2e776852, 0x5d2f, 0x484e, { 0x80, 0x78, 0xbc, 0x45, 0xa, 0x27, 0x32, 0x8 } };

// {EE14DB45-8522-46CD-9A3F-1EF9004117D8}
static const IID IID_IMult=
{ 0xee14db45, 0x8522, 0x46cd, { 0x9a, 0x3f, 0x1e, 0xf9, 0x0, 0x41, 0x17, 0xd8 } };
