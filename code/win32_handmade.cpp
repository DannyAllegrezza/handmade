#include <windows.h>

LRESULT CALLBACK MainWindowCallback(HWND Window,
	UINT Message,
	WPARAM WParam,
	LPARAM LParam)
{
	LRESULT Result = 0;

	switch (Message)
	{
		case WM_SIZE:
		{
			OutputDebugString("WM_SIZE\n");
		} break;

		case WM_DESTROY:
		{
			OutputDebugString("WM_DESTROY\n");
		} break;
		
		case WM_CLOSE:
		{
			OutputDebugString("WM_CLOSE\n");
		} break;

		case WM_ACTIVATEAPP:
		{
			OutputDebugString("WM_ACTIVATEAPP\n");
		} break;

		case WM_PAINT:
		{
			PAINTSTRUCT Paint;
			HDC DeviceContext = BeginPaint(Window, &Paint);

			int X = Paint.rcPaint.left;
			int Y = Paint.rcPaint.right;
			LONG Width = Paint.rcPaint.bottom - Paint.rcPaint.top;
			LONG Height = Paint.rcPaint.right - Paint.rcPaint.left;
			
			static DWORD Operation = WHITENESS;
			PatBlt(DeviceContext, X, Y, Width, Height, Operation);
			
			if (Operation == WHITENESS)
			{
				Operation = BLACKNESS;
			}
			else
			{
				Operation = WHITENESS;
			}

			EndPaint(Window, &Paint);

		} break;

		default:
		{
			//OutputDebugString("Default message\n\n");
			Result = DefWindowProc(Window, Message, WParam, LParam);
		} break;
	}

	return (Result);
}

int CALLBACK WinMain(
    HINSTANCE Instance,
    HINSTANCE PrevInstance,
    LPSTR CommandLine,
    int ShowCode)
{
    WNDCLASS WindowClass = {}; // "ZII" - Zero is initialization 
    
	//TODO(danny): Check if HREDRAW/VREDRAW/OWNDC still matter?
	WindowClass.style = CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
	WindowClass.lpfnWndProc = MainWindowCallback;
	WindowClass.hInstance = Instance;
	WindowClass.lpszClassName = "HandmadeHeroWindowClass";
	
	if (RegisterClass(&WindowClass)) 
	{
		HWND WindowHandle = 
			CreateWindowEx(
				0, 
				WindowClass.lpszClassName, 
				"Handmade Hero", 
				WS_OVERLAPPEDWINDOW | WS_VISIBLE, 
				CW_USEDEFAULT, 
				CW_USEDEFAULT, 
				CW_USEDEFAULT, 
				CW_USEDEFAULT, 
				0, 
				0, 
				Instance, 
				0);

		if (WindowHandle)
		{
			for (;;)
			{
				MSG Message;
				BOOL MessageResult = GetMessage(&Message, 0, 0, 0);
				if (MessageResult > 0)
				{
					// Translate and dispatch the message
					TranslateMessage(&Message);
					DispatchMessage(&Message);
				}
				else
				{
					break;
				}
			}
			
		}
		else 
		{

		}
	}
	else
	{
		//TODO(danny): add logging
	}

    return (0);
}
