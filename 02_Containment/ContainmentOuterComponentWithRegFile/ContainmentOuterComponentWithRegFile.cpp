#include<Windows.h>
#include"ContainmentOuterComponentWithRegFile.h"
#include"ContainmentInnerComponentWithRegFile.h"

//class declarations
class CSumSubtract :public ISum, ISubtract ,IMultiplication,IDivision
{
private:
	long m_cRef;
	IMultiplication *m_pIMultiplication;
	IDivision* m_pIDivision;
public:
	//constructor method declarations
	CSumSubtract(void);
	//destructor method declarations
	~CSumSubtract(void);
	//IUnknown specific method declaration (inherite)
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);
	//ISum specific method declarations (inherited)
	HRESULT __stdcall SumOfTwoIntegers(int, int, int*);
	//ISubtract specific method declarations (inherited)
	HRESULT __stdcall SubtrctionOfTwoIntegers(int, int, int*);

	HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*);

	HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*);

	HRESULT __stdcall InitializeInner(void); //Custom method for inner componet creation

};
class CSumSubtractClassFactory :public IClassFactory
{
private:
	long m_cRef;
public:
	//constructor method declarations
	CSumSubtractClassFactory(void);
	//destructor method declarations
	~CSumSubtractClassFactory(void);
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
CSumSubtract::CSumSubtract(void)
{
	m_pIMultiplication = NULL;
	m_pIDivision = NULL;
	m_cRef = 1; //Hardcoded Initialization to anticipate possible failure of QueryInterface()
	InterlockedIncrement(&glNumberOfActiveComponents);//Increment Globle Counter

}
//Implementaion of CSumSubtract Decrement Method
CSumSubtract::~CSumSubtract(void)
{
	InterlockedDecrement(&glNumberOfActiveComponents);//Decrement Globle Counter
	
	if (m_pIMultiplication)
	{
		m_pIMultiplication->Release();
		m_pIMultiplication = NULL;
	}
	if (m_pIDivision)
	{
		m_pIDivision->Release();
		m_pIDivision = NULL;
	}
}
//Implementation of CSumSubtract IUnknown Methods
HRESULT CSumSubtract::QueryInterface(REFIID riid, void** ppv)
{
	//code
	if (riid == IID_IUnknown)
		*ppv = static_cast<ISum *>(this);
	else if (riid == IID_ISum)
		*ppv = static_cast<ISum *>(this);
	else if (riid == IID_ISubtract)
		*ppv = static_cast<ISubtract *>(this);
	else if (riid == IID_IMultiplication)
		*ppv = static_cast<IMultiplication*>(this);
	else if(riid == IID_IDivision)
		*ppv = static_cast<IDivision*>(this);
	else
	{

	} {
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return(S_OK);
}
ULONG CSumSubtract::AddRef(void)
{
	//code
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}
ULONG CSumSubtract::Release(void)
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
HRESULT CSumSubtract::SumOfTwoIntegers(int num1, int num2, int* pSum)
{
	//code
	*pSum = num1 + num2;
	return(S_OK);
}
//Implementation of ISubtract's Methods
HRESULT CSumSubtract::SubtrctionOfTwoIntegers(int num1, int num2, int* pSubtract)
{
	*pSubtract = num1 - num2;
	return(S_OK);
}
HRESULT CSumSubtract::MultiplicationOfTwoIntegers(int num1, int num2, int* pMultiplication)
{
	m_pIMultiplication->MultiplicationOfTwoIntegers(num1, num2, pMultiplication);
	return(S_OK);
}
HRESULT CSumSubtract::DivisionOfTwoIntegers(int num1, int num2, int* pDivision)
{
	m_pIDivision->DivisionOfTwoIntegers(num1, num2, pDivision);
	return(S_OK);
}

HRESULT CSumSubtract::InitializeInner(void)
{
	HRESULT hr;

	hr = CoCreateInstance(CLSID_MultiplicationDivision, NULL, CLSCTX_INPROC_SERVER, IID_IMultiplication, (void**)&m_pIMultiplication);

	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("IMultipliccation Interface can not obtained from Inner Component"), TEXT("Error"), MB_OK);
		return(E_FAIL);
	}

	hr = CoCreateInstance(CLSID_MultiplicationDivision, NULL, CLSCTX_INPROC_SERVER, IID_IDivision, (void**)&m_pIDivision);

	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("IDivision Interface can not obtained from Inner Component"), TEXT("Error"), MB_OK);
		return(E_FAIL);
	}
	return(S_OK);
}
//Implementation of CSumSubtractClassFactory's Constructor Method
CSumSubtractClassFactory::CSumSubtractClassFactory(void)
{
	//code
	m_cRef = 1;//hardcoded initialization to anticipate possible failure of QueryInterface()
}
//Implenetation of CSumSubtractClassFactory's Destructor Method
CSumSubtractClassFactory::~CSumSubtractClassFactory(void)
{
	//code
}
//Implementation of CSumSubtractClassFactory's IClassFactory's IUnknown's Methods
HRESULT CSumSubtractClassFactory::QueryInterface(REFIID riid, void** ppv)
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
ULONG CSumSubtractClassFactory::AddRef(void)
{
	//code
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}
ULONG CSumSubtractClassFactory::Release(void)
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
//Implementation of CSumSubtractClassFactory's IClassFactory's Methods
HRESULT CSumSubtractClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv)
{
	//variable declarations
	CSumSubtract* pCSumSubtract = NULL;
	HRESULT hr;
	//code
	if (pUnkOuter != NULL)
		return(CLASS_E_NOAGGREGATION);
	//create the instance of componenet i.e. of CSumSubtract class
	pCSumSubtract = new CSumSubtract;
	if (pCSumSubtract == NULL)
		return(E_OUTOFMEMORY);
	//get the requested interface
	hr = pCSumSubtract->InitializeInner();
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("Failed to Intialize Inner Component"), TEXT("Error"), MB_OK);
		pCSumSubtract->Release();
		return(hr);
	}
	hr = pCSumSubtract->QueryInterface(riid, ppv);
	pCSumSubtract->Release();//anticipate possible failure of QueryInterface()
	return(hr);
}
HRESULT CSumSubtractClassFactory::LockServer(BOOL fLock)
{
	//code
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
	CSumSubtractClassFactory* pCSumSubtractClassFactory = NULL;
	HRESULT hr;
	//code
	if (rclsid != CLSID_SumSubtract)
		return(CLASS_E_CLASSNOTAVAILABLE);
	//Create class factory
	pCSumSubtractClassFactory = new CSumSubtractClassFactory;
	if (pCSumSubtractClassFactory == NULL)
		return(E_OUTOFMEMORY);
	hr = pCSumSubtractClassFactory->QueryInterface(riid, ppv);
	pCSumSubtractClassFactory->Release();//anticipate possible failure of QueryInterFace()
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
