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

// CLSID of SumSubtract Component {7D2AFA5D-D613-4BDE-8748-6E8A345C92BB}
static CLSID CLSID_SumSubtract =
{ 0x7d2afa5d, 0xd613, 0x4bde, { 0x87, 0x48, 0x6e, 0x8a, 0x34, 0x5c, 0x92, 0xbb } };

//IID of ISum Interface {61B62774-D727-417E-8009-6F3A28B58FF7}
static const IID IID_ISum =
{ 0x61b62774, 0xd727, 0x417e, { 0x80, 0x9, 0x6f, 0x3a, 0x28, 0xb5, 0x8f, 0xf7 } };

//IID of ISubtract Interface {1B5200A9-A3DC-4C17-8A29-27450BD1C505}
static const IID IID_ISubtract =
{ 0x1b5200a9, 0xa3dc, 0x4c17, { 0x8a, 0x29, 0x27, 0x45, 0xb, 0xd1, 0xc5, 0x5 } };
