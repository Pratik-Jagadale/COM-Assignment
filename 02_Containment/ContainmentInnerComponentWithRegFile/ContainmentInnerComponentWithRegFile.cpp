
#include<Windows.h>
#include"ContainmentInnerComponentWithRegFile.h"
//class declarations
class CMultiplicationDivision:public IMultiplication,IDivision
{
private:
	long m_cRef;
public:
	//constructor method declarations
	CMultiplicationDivision(void);
	//destructor method declarations
	~CMultiplicationDivision(void);
	//IUnknown specific method declaration (inherite)
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);
	//ISum specific method declarations (inherited)
	HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*);
	//ISubtract specific method declarations (inherited)
	HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*);
};
class CMultiplicationDivisionClassFactory:public IClassFactory
{
private:
	long m_cRef;
public:
	//constructor method declarations
	CMultiplicationDivisionClassFactory(void);
	//destructor method declarations
	~CMultiplicationDivisionClassFactory(void);
	//IUnknown specific mehtod declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);
	//IClassFactory specific method declarations (inherited)
	HRESULT __stdcall CreateInstance(IUnknown*, REFIID, void**);
	HRESULT __stdcall LockServer(BOOL);
};
//global variable declarations
long glNumberOfActiveComponents = 0;//number of active components
long glNumberOfServerLocks = 0;//number of locks on this dll
//DllMain
BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID Reserved)
{
	//code
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	}
	return(TRUE);
}
//Implemention of CSumSubtract's Constructor method
CMultiplicationDivision::CMultiplicationDivision(void)
{
	//code
	m_cRef = 1; //Hardcoded Initialization to anticipate possible failure of QueryInterface()
	InterlockedIncrement(&glNumberOfActiveComponents);//Increment Globle Counter
}
//Implementaion of CSumSubtract Decrement Method
CMultiplicationDivision::~CMultiplicationDivision(void)
{
	//code
	InterlockedDecrement(&glNumberOfActiveComponents);//Decrement Globle Counter
}
//Implementation of CSumSubtract IUnknown Methods
HRESULT CMultiplicationDivision::QueryInterface(REFIID riid, void** ppv)
{
	//code
	if (riid == IID_IUnknown)
		*ppv = static_cast<IMultiplication*>(this);
	else if (riid == IID_IMultiplication)
		*ppv = static_cast<IMultiplication*>(this);
	else if (riid == IID_IDivision)
		*ppv = static_cast<IDivision*>(this);
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return(S_OK);
}
ULONG CMultiplicationDivision::AddRef(void)
{
	//code
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}
ULONG CMultiplicationDivision::Release(void)
{
	//code
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}
//Implementation of ISum's Methods
HRESULT CMultiplicationDivision::MultiplicationOfTwoIntegers(int num1, int num2, int *pMultiplication)
{
	//code
	*pMultiplication = num1 * num2;
	return(S_OK);
}
//Implementation of ISubtract's Methods
HRESULT CMultiplicationDivision::DivisionOfTwoIntegers(int num1, int num2, int *pDivision)
{
	*pDivision = num1 / num2;
	return(S_OK);
}
//Implementation of CSumSubtractClassFactory's Constructor Method
CMultiplicationDivisionClassFactory::CMultiplicationDivisionClassFactory(void)
{
	//code
	m_cRef = 1;//hardcoded initialization to anticipate possible failure of QueryInterface()
}
//Implenetation of CSumSubtractClassFactory's Destructor Method
CMultiplicationDivisionClassFactory::~CMultiplicationDivisionClassFactory(void)
{
	//code
}
//Implementation of CSumSubtractClassFactory's IClassFactory's IUnknown's Methods
HRESULT CMultiplicationDivisionClassFactory::QueryInterface(REFIID riid, void** ppv)
{
	//code
	if (riid == IID_IUnknown)
		*ppv = static_cast<IClassFactory*>(this);
	else if (riid == IID_IClassFactory)
		*ppv = static_cast<IClassFactory*>(this);
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return(S_OK);
}
ULONG CMultiplicationDivisionClassFactory::AddRef(void)
{
	//code
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}
ULONG CMultiplicationDivisionClassFactory::Release(void)
{
	//code
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}

HRESULT CMultiplicationDivisionClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv)
{
	
	CMultiplicationDivision * pCMultiplicationDivision = NULL;
	HRESULT hr;
	
	if (pUnkOuter != NULL)
		return(CLASS_E_NOAGGREGATION);
	
	pCMultiplicationDivision = new CMultiplicationDivision;
	if (pCMultiplicationDivision == NULL)
		return(E_OUTOFMEMORY);
	
	hr = pCMultiplicationDivision->QueryInterface(riid, ppv);
	pCMultiplicationDivision->Release();//anticipate possible failure of QueryInterface()
	return(hr);
}
HRESULT CMultiplicationDivisionClassFactory::LockServer(BOOL fLock)
{
	
	if (fLock)
		InterlockedIncrement(&glNumberOfServerLocks);
	else
		InterlockedDecrement(&glNumberOfServerLocks);
	return(S_OK);
}
//Implementaion of Exported Functions From This Dll
extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv)
{
	//variable declarations
	CMultiplicationDivisionClassFactory* pCMultiplicationDivisionClassFactory = NULL;
	HRESULT hr;
	//code
	if (rclsid != CLSID_MultiplicationDivision)
		return(CLASS_E_CLASSNOTAVAILABLE);
	//Create class factory
	pCMultiplicationDivisionClassFactory = new CMultiplicationDivisionClassFactory;
	if (pCMultiplicationDivisionClassFactory == NULL)
		return(E_OUTOFMEMORY);
	hr = pCMultiplicationDivisionClassFactory->QueryInterface(riid, ppv);
	pCMultiplicationDivisionClassFactory->Release();//anticipate possible failure of QueryInterFace()
	return(hr);
}
extern "C" HRESULT __stdcall DllCanUnloadNow(void)
{
	//code
	if ((glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0))
		return(S_OK);
	else
		return(S_FALSE);
}
