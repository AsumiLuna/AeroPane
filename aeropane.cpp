#include <windows.h>
#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void RefreshNonClientArea(HWND hwnd) {
    // Force a redraw of the non-client area
    DwmInvalidateIconicBitmaps(hwnd);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const char CLASS_NAME[] = "Transparent Window Class";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = nullptr; 
    wc.style = CS_HREDRAW | CS_VREDRAW;
    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        WS_EX_COMPOSITED | WS_EX_APPWINDOW,
        CLASS_NAME,
        "Aero Pane",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        nullptr,
        nullptr,
        hInstance,
        nullptr
    );

    if (hwnd == nullptr) {
        return 0;
    }

    MARGINS margins = { -1 }; 
    DwmExtendFrameIntoClientArea(hwnd, &margins);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_NCHITTEST:
            {
                LRESULT hit = DefWindowProc(hwnd, uMsg, wParam, lParam);
                if (hit == HTCLIENT) {
                    
                    return HTCAPTION;
                }
                return hit;
            }

        case WM_ENTERSIZEMOVE:
            OutputDebugString("Window resizing started.\n");
            break;

        case WM_EXITSIZEMOVE:
            OutputDebugString("Window resizing ended.\n");
            RefreshNonClientArea(hwnd);
            break;

        case WM_SIZE:
            break;

        case WM_PAINT:
            {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hwnd, &ps);


                EndPaint(hwnd, &ps);
            }
            break;

        case WM_ERASEBKGND:
            return 1; 

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
