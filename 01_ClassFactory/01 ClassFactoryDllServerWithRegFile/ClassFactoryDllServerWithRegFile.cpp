//
#include<Windows.h>
#include"ClassFactoryDllServerWithRegFile.h"
//class Declaration
class CSumSubstract:public ISum, ISub, IMult
{
	private:
		long m_cRef;

    public:
		CSumSubstract(void);
		//constructor Method declartion

		//destructor method declaration
		~CSumSubstract(void);

		//iUnkonwn specific mathod declaration (inherited)
		HRESULT __stdcall QueryInterface(REFIID, void **);

		ULONG __stdcall AddRef(void);

		ULONG __stdcall Release(void);


		HRESULT __stdcall SumOfTwoInteger(int, int, int*);
		HRESULT __stdcall SubOfTwoInteger(int, int, int*);
		HRESULT __stdcall MultOfTwoInteger(int, int, int*);

};
//
class CSumSubstractClassFactory:public IClassFactory
{
private:
	long m_cRef;

public:
	CSumSubstractClassFactory(void);

	~CSumSubstractClassFactory(void);


	HRESULT __stdcall QueryInterface(REFIID, void**);

	ULONG __stdcall AddRef(void);

	ULONG __stdcall Release(void); 

	HRESULT __stdcall CreateInstance(IUnknown*, REFIID, void**);
	HRESULT __stdcall LockServer(BOOL);
};

//global varible declaration
long glNumberOfActiveComponent = 0; //number of active component
long glNumberOfServerLocks = 0; //number of locks on this dll
//Dll main

BOOL WINAPI DllMain(HINSTANCE HDll, DWORD dwReason, LPVOID Reserved)
{
	//code
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return(TRUE);
};
//Implementation of CCreateMaker IUnkown's Mathod
CSumSubstract::CSumSubstract(void)
{
	//code
	m_cRef = 1; //hard code initialization to anticipate possible failure of QueryInterface

	InterlockedIncrement(&glNumberOfActiveComponent);//increment global counter
}
//implementation of CSumSubstract Destructor Method
CSumSubstract::~CSumSubstract(void)
{
	//code
	InterlockedDecrement(&glNumberOfActiveComponent);
}
//Implementation of CSumSubstract IUnknown Methods
HRESULT CSumSubstract::QueryInterface(REFIID riid, void **ppv)
{
	//code
	if (riid == IID_IUnknown)
		*ppv = static_cast<ISum*>(this);
	else if(riid == IID_ISum)
		*ppv = static_cast<ISum*>(this);
	else if(riid == IID_ISub)
		*ppv = static_cast<ISub *>(this);
	else if (riid == IID_IMult)
		*ppv = static_cast<IMult*>(this);
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return(S_OK);
}
ULONG CSumSubstract::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}
ULONG CSumSubstract::Release(void)
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
//Implementation of ISum
HRESULT CSumSubstract::SumOfTwoInteger(int iNum1,int iNum2,int *pSum)
{
	*pSum = iNum1 + iNum2;
	return(S_OK);
}
//Implementation of IISub
HRESULT CSumSubstract::SubOfTwoInteger(int iNum1, int iNum2, int* pSub)
{
	*pSub = iNum1 - iNum2;
	return(S_OK);
}
//Implementation of IMult
HRESULT CSumSubstract::MultOfTwoInteger(int iNum1, int iNum2, int* pMult)
{
	*pMult = iNum1 * iNum2;
	return(S_OK);
}

//ClassFactory implementation
CSumSubstractClassFactory::CSumSubstractClassFactory(void)
{
	m_cRef = 1;
}
CSumSubstractClassFactory::~CSumSubstractClassFactory(void)
{
	//code
}

HRESULT CSumSubstractClassFactory::QueryInterface(REFIID riid, void **ppv)
{
	//code
	if (riid == IID_IUnknown)
		*ppv = static_cast<IClassFactory*>(this);
	else if(riid == IID_ICallFactory)
		*ppv = static_cast<IClassFactory *>(this);
	else
	{
		*ppv = NULL;
			return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return(S_OK);
}
ULONG CSumSubstractClassFactory::AddRef(void)
{
	//code
	InterlockedIncrement(&m_cRef);
	return(S_OK);
}
ULONG CSumSubstractClassFactory::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}

HRESULT CSumSubstractClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv)
{
	//varible declaration
	CSumSubstract* pCSumSubstract = NULL;
	HRESULT hr;
	//code
	if (pUnkOuter != NULL)	
		return(CLASS_E_NOAGGREGATION);

	//Create the instance of component i.e of CSumSubstract class
	pCSumSubstract = new CSumSubstract;
	if (pCSumSubstract == NULL)
			return(E_OUTOFMEMORY);
	//get the request interface 
	hr = pCSumSubstract->QueryInterface(riid, ppv);
	pCSumSubstract->Release();//anticipate possible failure of Query Interface
	return(hr);
}

HRESULT CSumSubstractClassFactory::LockServer(BOOL fLock)
{
	//code
	if (fLock)
	{
		InterlockedIncrement(&glNumberOfServerLocks);
	}
	else
	{
		InterlockedDecrement(&glNumberOfServerLocks);
	}
	return(S_OK);
}
//implementation of Exported function From Thid Dll
extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv)
{
	//variable declaration
	CSumSubstractClassFactory* pCSumSubstractClassFactory = NULL;
	HRESULT hr;

	//code
	if (rclsid != CLSID_SumSub)
		return(CLASS_E_CLASSNOTAVAILABLE);
	//create class factory
	pCSumSubstractClassFactory = new CSumSubstractClassFactory;
	if (pCSumSubstractClassFactory == NULL)
	{
		return(E_OUTOFMEMORY);
	}
	hr = pCSumSubstractClassFactory->QueryInterface(riid, ppv);
	pCSumSubstractClassFactory->Release();
	return(hr);
}

extern "C" HRESULT __stdcall DllCanUnloadNow(void)
{
	//code
	if ((glNumberOfActiveComponent == 0) && (glNumberOfServerLocks == 0))
		return(S_OK);
	else
		return(S_FALSE);
}
