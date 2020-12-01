#pragma once
class ISum :public IUnknown
{
public:
	//Isum Specific Method Declarations
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*)=0;//Pure Virtual 
};
class ISubtract :public IUnknown
{
public:
	//Isubtract Specific Method Declarations
	virtual HRESULT __stdcall SubtrctionOfTwoIntegers(int, int, int*)=0;//Pure Virtual
};
// CLSID of SumSubtract Component  {1FC5FEBE-3D73-4D96-BAA8-44FC6FF17DA8}
const CLSID CLSID_SumSubtract =
{ 0x1fc5febe, 0x3d73, 0x4d96, 0xba, 0xa8, 0x44, 0xfc, 0x6f, 0xf1, 0x7d, 0xa8 };

//IID of ISum Interface {147BBC26-2D78-45AE-BA2F-8D0173628930}
const IID IID_ISum =
{ 0x147bbc26, 0x2d78, 0x45ae, 0xba, 0x2f, 0x8d, 0x1, 0x73, 0x62, 0x89, 0x30 };

//IID of ISubtract Interface {C73F988B-2FED-401F-808C-44C0B7A5E308}
const IID IID_ISubtract =
{ 0xc73f988b, 0x2fed, 0x401f, 0x80, 0x8c, 0x44, 0xc0, 0xb7, 0xa5, 0xe3, 0x8 };
