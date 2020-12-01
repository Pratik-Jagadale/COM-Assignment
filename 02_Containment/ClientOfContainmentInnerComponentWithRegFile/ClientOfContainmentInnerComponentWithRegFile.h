#include<Windows.h>
class ISum:public IUnknown
{
public:
	//Isum Specific Method Declarations
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*)=0;//Pure Virtual 
};
class ISubtract:public IUnknown
{
public:
	//Isubtract Specific Method Declarations
	virtual HRESULT __stdcall SubtrctionOfTwoIntegers(int, int, int*)=0;//Pure Virtual
};
class IMultiplication :public IUnknown
{
public:
	//Isum Specific Method Declarations
	virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*) = 0;//Pure Virtual 
};
class IDivision :public IUnknown
{
public:
	//Isubtract Specific Method Declarations
	virtual HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*) = 0;//Pure Virtual
};

// CLSID of SumSubtract Component {7D2AFA5D-D613-4BDE-8748-6E8A345C92BB}
static CLSID CLSID_SumSubtract =
{ 0x7d2afa5d, 0xd613, 0x4bde, { 0x87, 0x48, 0x6e, 0x8a, 0x34, 0x5c, 0x92, 0xbb } };

//IID of ISum Interface {61B62774-D727-417E-8009-6F3A28B58FF7}
static const IID IID_ISum =
{ 0x61b62774, 0xd727, 0x417e, { 0x80, 0x9, 0x6f, 0x3a, 0x28, 0xb5, 0x8f, 0xf7 } };

//IID of ISubtract Interface {1B5200A9-A3DC-4C17-8A29-27450BD1C505}
static const IID IID_ISubtract =
{ 0x1b5200a9, 0xa3dc, 0x4c17, { 0x8a, 0x29, 0x27, 0x45, 0xb, 0xd1, 0xc5, 0x5 } };

// {DD00AE02-67AB-48AF-B154-87397814AF88}
static const IID IID_IMultiplication =
{ 0xdd00ae02, 0x67ab, 0x48af, { 0xb1, 0x54, 0x87, 0x39, 0x78, 0x14, 0xaf, 0x88 } };

// {175AB6B1-4A59-4C63-933A-BBF495DA9F6F}
static const IID IID_IDivision =
{ 0x175ab6b1, 0x4a59, 0x4c63, { 0x93, 0x3a, 0xbb, 0xf4, 0x95, 0xda, 0x9f, 0x6f } };
