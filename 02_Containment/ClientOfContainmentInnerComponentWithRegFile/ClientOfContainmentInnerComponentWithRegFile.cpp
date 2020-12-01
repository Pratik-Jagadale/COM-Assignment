//header
#include<windows.h>
#include"ClientOfContainmentInnerComponentWithRegFile.h"

//global function declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//global Variable Declaration
ISum* pISum = NULL;
ISubtract* pISubtract = NULL;
IMultiplication *pIMultiplication = NULL;
IDivision *pIDivision = NULL;


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
	int iNum1, iNum2, iSum,iSubstraction,iMultiplication,iDivision,iUnknown;
	TCHAR str[255];
	IUnknown* pIUnknownFromISum = NULL;
	IUnknown* pIUnknownFromIMultiplication = NULL;
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
		pISum->Release();
		pISum = NULL;
		
		//again initialize arguments hardcoded
		iNum1 = 155;
		iNum2 = 145;
		
		//again call SubstractionOfTwoIntegers() of ISum to get the new sum
		pISubtract->SubtrctionOfTwoIntegers(iNum1, iNum2, &iSum);	

		//display the result
		wsprintf(str, TEXT("Subtraction of %d and %d = %d"), iNum1, iNum2, iSum);
		MessageBox(hwnd, str, TEXT("Result"), MB_OK);

		hr = pISubtract->QueryInterface(IID_IMultiplication, (void**) &pIMultiplication);

		if(FAILED(hr))
		{
			MessageBox(hwnd,TEXT("ISubstraction Interface Can Not be obtained"),TEXT("ERROR"),MB_OK);
				DestroyWindow(hwnd);
		}

		pISubtract->Release();
		pISubtract = NULL;//Make relesed interface NULL


		iNum1 = 30;
		iNum2 = 40;

		pIMultiplication->MultiplicationOfTwoIntegers(iNum1, iNum2, &iMultiplication);

		//display the result
		wsprintf(str, TEXT("Multiplication of %d and %d = %d"), iNum1, iNum2, iMultiplication);
		MessageBox(hwnd, str, TEXT("Result"), MB_OK);

		hr = pIMultiplication->QueryInterface(IID_IDivision, (void**)&pIDivision);

		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("IMultiplication Interface Can Not be obtained"),TEXT("ERROR"),MB_OK );
			DestroyWindow(hwnd);
		}

		pIMultiplication->Release();
		pIMultiplication = NULL;//Make relesed interface NULL


		iNum1 = 200;
		iNum2 = 5;
		
		pIDivision->DivisionOfTwoIntegers(iNum1, iNum2, &iDivision);

		wsprintf(str, TEXT("Division of %d and %d = %f"), iNum1, iNum2, iDivision);
		MessageBox(hwnd, str, TEXT("Result"), MB_OK);


		pIDivision->Release();
		pIDivision = NULL;//Make relesed interface NULL



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