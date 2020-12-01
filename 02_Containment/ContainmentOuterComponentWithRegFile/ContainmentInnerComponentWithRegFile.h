#include<Windows.h>
class IMultiplication:public IUnknown
{
public:
	//Isum Specific Method Declarations
	virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int *)=0;//Pure Virtual 
};
class IDivision:public IUnknown
{
public:
	//Isubtract Specific Method Declarations
	virtual HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*)=0;//Pure Virtual
};
// {1CDCBCEB-B24E-4D19-ABAB-79DD8105C761}
const CLSID CLSID_MultiplicationDivision =
{ 0x1cdcbceb, 0xb24e, 0x4d19, { 0xab, 0xab, 0x79, 0xdd, 0x81, 0x5, 0xc7, 0x61 } };

// {DD00AE02-67AB-48AF-B154-87397814AF88}
static const IID IID_IMultiplication =
{ 0xdd00ae02, 0x67ab, 0x48af, { 0xb1, 0x54, 0x87, 0x39, 0x78, 0x14, 0xaf, 0x88 } };

// {175AB6B1-4A59-4C63-933A-BBF495DA9F6F}
static const IID IID_IDivision =
{ 0x175ab6b1, 0x4a59, 0x4c63, { 0x93, 0x3a, 0xbb, 0xf4, 0x95, 0xda, 0x9f, 0x6f } };
