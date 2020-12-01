//header
#include<windows.h>
#include"ClassFactoryDllServerWithRegFile.h"

//global function declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//global Variable Declaration
ISum* pISum = NULL;
ISubtract* pISubtract = NULL;

//Winmain()
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR
	lpszCmdLine, int iCmdShow)
{
	//variable declaration
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyApp");
	HRESULT hr;
	//code
	//COM Initialization
	hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("COM Library Can not be initialized .\nProgram Will Now Exit."), TEXT("Program Error"), MB_OK);
		exit(0);
	}
	//initialization of WNDCLASSEX
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	//register above class
	RegisterClassEx(&wndclass);

	//create window
	hwnd = CreateWindow(szAppName,
		TEXT("My Application"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	//message loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	//COM Un-Initialization
	CoUninitialize();
	return((int)msg.wParam);
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//function declarations
	void SafeInterfaceRelease(void);
	//variable declarations
	HRESULT hr;
	int iNum1, iNum2, iSum;
	TCHAR str[255];
	IUnknown* pIUnknownFromISum = NULL;
	IUnknown* pIUnknownFromISubtract = NULL;
	ISum* pISumAgain = NULL;
	//code
	switch (iMsg)
	{
	case WM_CREATE:
		hr = CoCreateInstance(CLSID_SumSubtract, NULL, CLSCTX_INPROC_SERVER, IID_ISum, (void **)&pISum);

		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("ISum Interface Can Not Be Obtained"), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}

		// initialize arguments hardcoded
		iNum1 = 55;
		iNum2 = 45;

		//call SumOfTwoIntegers() of Isum to get the sum
		pISum->SumOfTwoIntegers(iNum1, iNum2, &iSum);

		//display the result
		wsprintf(str, TEXT("Sum of %d and %d = %d"), iNum1, iNum2, iSum);
		MessageBox(hwnd, str, TEXT("Result"), MB_OK);

		//call QueryInterface() on ISum, to get ISubtract's pointer
		hr = pISum->QueryInterface(IID_ISubtract, (void **)&pISubtract);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("ISubtract Interface Can Not Be obtained"), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}
		//as ISum is now not needed onwords, release it
	
		
		//again initialize arguments hardcoded
		iNum1 = 155;
		iNum2 = 145;
		
		//again call SubstractionOfTwoIntegers() of ISum to get the new sum
		pISubtract->SubtrctionOfTwoIntegers(iNum1, iNum2, &iSum);
		

		pISum->QueryInterface(IID_IUnknown, (void**)&pIUnknownFromISum); //for check identity

		pISubtract->QueryInterface(IID_IUnknown, (void**)&pIUnknownFromISubtract);//get Iunknown from Isubstract
 
		if (pIUnknownFromISum == pIUnknownFromISubtract)
		{
			MessageBox(hwnd, TEXT("Both iUnkonwn are same"), TEXT("Success"), MB_OK); //identity check
			DestroyWindow(hwnd);

			pIUnknownFromISum->Release();
			pIUnknownFromISum = NULL;
			pIUnknownFromISubtract->Release();
			pIUnknownFromISubtract = NULL;
		}
		else
		{
			MessageBox(hwnd, TEXT("Both I Unknown are not same"), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}

		//check symmetric
		pISubtract->QueryInterface(IID_ISum, (void**)pISumAgain);
		if (pISumAgain == pISum)
		{
			MessageBox(hwnd, TEXT("ISum & ISubtract is Symmentic"), TEXT("Success"), MB_OK); //identity check
			DestroyWindow(hwnd);
			pISumAgain->Release();
			pISumAgain = NULL;
		}
		else
		{
			MessageBox(hwnd, TEXT("Not Symmetric"), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}

		//check Reflexive
		pISubtract->QueryInterface(IID_ISum, (void**)pISumAgain);
		if (pISumAgain == pISum)
		{ 
			MessageBox(hwnd, TEXT("ISum & is Reflexive"), TEXT("Success"), MB_OK); //identity check
			DestroyWindow(hwnd);
			pISumAgain->Release();
			pISumAgain = NULL;
		}
		else
		{
			MessageBox(hwnd, TEXT("Not Reflexive"), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}

		pISum->Release();
		pISum = NULL;//make relesed interface null

		//as ISum is now not needed onwords, release it
		pISubtract->Release();
		pISubtract = NULL;//Make relesed interface NULL
		//display the result
		wsprintf(str, TEXT("Subtraction of %d and %d = %d"), iNum1, iNum2, iSum);
		MessageBox(hwnd, str, TEXT("Result"), MB_OK);
		//exit the application
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
void SafeInterfaceRelease(void)
{
	//code
	if (pISum)
	{
		pISum->Release();
		pISum = NULL;
	}
	if (pISubtract)
	{
		pISubtract->Release();
		pISubtract = NULL;
	}
}