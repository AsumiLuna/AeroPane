#include <windows.h>
#include <dwmapi.h>
#include <iostream>
#include <commctrl.h>

#pragma comment(lib, "dwmapi.lib")
#pragma comment(lib, "comctl32.lib") // Link to the common controls library

#define ID_BUTTON_LAUNCH_MAIN 1
#define ID_SUB_WINDOW_CLASS "SubWindowClass"

// IDs for controls in the sub-window
#define ID_TEXT_BOX1 101
#define ID_TEXT_BOX2 102
#define ID_TEXT_BOX3 103
#define ID_TEXT_BOX4 104
#define ID_SPIN1 201
#define ID_SPIN2 202
#define ID_SPIN3 203
#define ID_SPIN4 204

// Function prototypes
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK SubWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// Global variables to store margin values
int margin1 = -1;
int margin2 = -1;
int margin3 = -1;
int margin4 = -1;

// Function to create and initialize controls in the sub-window
void CreateSubWindowControls(HWND hwnd) {
    HWND hTextBox1, hTextBox2, hTextBox3, hTextBox4;
    HWND hSpin1, hSpin2, hSpin3, hSpin4;
    HWND hLaunchButton;

    // Create text boxes without ES_NUMBER style to allow negative numbers
    hTextBox1 = CreateWindowEx(
        0, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
        10, 10, 100, 25, hwnd, (HMENU)ID_TEXT_BOX1,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
    );

    hTextBox2 = CreateWindowEx(
        0, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
        10, 45, 100, 25, hwnd, (HMENU)ID_TEXT_BOX2,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
    );

    hTextBox3 = CreateWindowEx(
        0, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
        10, 80, 100, 25, hwnd, (HMENU)ID_TEXT_BOX3,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
    );

    hTextBox4 = CreateWindowEx(
        0, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
        10, 115, 100, 25, hwnd, (HMENU)ID_TEXT_BOX4,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
    );

    // Create spin buttons with a range that includes negative values
    hSpin1 = CreateWindowEx(
        0, UPDOWN_CLASS, NULL,
        WS_CHILD | WS_VISIBLE | UDS_ALIGNRIGHT | UDS_SETBUDDYINT,
        115, 10, 20, 25, hwnd, (HMENU)ID_SPIN1,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
    );
    SendMessage(hSpin1, UDM_SETRANGE, 0, MAKELPARAM(100, -100)); // Set range -100 to 100

    hSpin2 = CreateWindowEx(
        0, UPDOWN_CLASS, NULL,
        WS_CHILD | WS_VISIBLE | UDS_ALIGNRIGHT | UDS_SETBUDDYINT,
        115, 45, 20, 25, hwnd, (HMENU)ID_SPIN2,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
    );
    SendMessage(hSpin2, UDM_SETRANGE, 0, MAKELPARAM(100, -100)); // Set range -100 to 100

    hSpin3 = CreateWindowEx(
        0, UPDOWN_CLASS, NULL,
        WS_CHILD | WS_VISIBLE | UDS_ALIGNRIGHT | UDS_SETBUDDYINT,
        115, 80, 20, 25, hwnd, (HMENU)ID_SPIN3,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
    );
    SendMessage(hSpin3, UDM_SETRANGE, 0, MAKELPARAM(100, -100)); // Set range -100 to 100

    hSpin4 = CreateWindowEx(
        0, UPDOWN_CLASS, NULL,
        WS_CHILD | WS_VISIBLE | UDS_ALIGNRIGHT | UDS_SETBUDDYINT,
        115, 115, 20, 25, hwnd, (HMENU)ID_SPIN4,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
    );
    SendMessage(hSpin4, UDM_SETRANGE, 0, MAKELPARAM(100, -100)); // Set range -100 to 100

    // Associate each spin control with the corresponding edit control
    SendMessage(hSpin1, UDM_SETBUDDY, (WPARAM)hTextBox1, 0);
    SendMessage(hSpin2, UDM_SETBUDDY, (WPARAM)hTextBox2, 0);
    SendMessage(hSpin3, UDM_SETBUDDY, (WPARAM)hTextBox3, 0);
    SendMessage(hSpin4, UDM_SETBUDDY, (WPARAM)hTextBox4, 0);

    // Create a button to launch the main window
    hLaunchButton = CreateWindow(
        "BUTTON", "Launch Main Window",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        10, 150, 150, 30,
        hwnd, (HMENU)ID_BUTTON_LAUNCH_MAIN,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
    );
}

// Function to create the main window and handle messages
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static HBRUSH hBackgroundBrush = nullptr;
    switch (uMsg) {
        case WM_CREATE: {
            // Initialize background brush
            hBackgroundBrush = CreateSolidBrush(RGB(0, 0, 0));
            // Extend the frame into the client area to create a glass effect using dynamic margins
            MARGINS margins = { margin1, margin2, margin3, margin4 };
            DwmExtendFrameIntoClientArea(hwnd, &margins);
            SetWindowPos(hwnd, nullptr, 0, 0, 800, 600, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
            break;
        }
        case WM_PAINT: {

            break;
        }
        case WM_ERASEBKGND: {
            // Prevent background erasing to handle transparency
            return 1;
        }
        case WM_NCHITTEST: {
            // Custom hit-testing for draggable areas
            LRESULT result = DefWindowProc(hwnd, uMsg, wParam, lParam);
            if (result == HTCLIENT) {
                result = HTCAPTION; // Make the entire window draggable
            }
            return result;
        }
        case WM_DESTROY:
            if (hBackgroundBrush) {
                DeleteObject(hBackgroundBrush);
            }
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

// Function to create the sub-window and handle messages
LRESULT CALLBACK SubWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static HWND hMainWindow = NULL;

    switch (uMsg) {
        case WM_CREATE:
            CreateSubWindowControls(hwnd);
            break;
        case WM_COMMAND: {
            if (LOWORD(wParam) == ID_BUTTON_LAUNCH_MAIN) {
                // Get margin values from the text boxes
                char buffer[10];
                GetWindowText(GetDlgItem(hwnd, ID_TEXT_BOX1), buffer, sizeof(buffer));
                margin1 = atoi(buffer);
                GetWindowText(GetDlgItem(hwnd, ID_TEXT_BOX2), buffer, sizeof(buffer));
                margin2 = atoi(buffer);
                GetWindowText(GetDlgItem(hwnd, ID_TEXT_BOX3), buffer, sizeof(buffer));
                margin3 = atoi(buffer);
                GetWindowText(GetDlgItem(hwnd, ID_TEXT_BOX4), buffer, sizeof(buffer));
                margin4 = atoi(buffer);

                // Create and show the main window
                if (hMainWindow == NULL) {
                    hMainWindow = CreateWindowEx(
                        WS_EX_COMPOSITED | WS_EX_LAYERED,
                        "MainWindowClass", "Aero Pane",
                        WS_OVERLAPPEDWINDOW,
                        CW_USEDEFAULT, CW_USEDEFAULT, 14000, 14000,
                        nullptr, nullptr, reinterpret_cast<HINSTANCE>(GetWindowLongPtr(hwnd, GWLP_HINSTANCE)), nullptr
                    );

                    if (hMainWindow != NULL) {
                        // Initialize DWM effect for the main window
                        MARGINS margins = { margin1, margin2, margin3, margin4 };
                        DwmExtendFrameIntoClientArea(hMainWindow, &margins);

                        ShowWindow(hMainWindow, SW_SHOW);
                        UpdateWindow(hMainWindow);
                    }
                }
                DestroyWindow(hwnd);
            }
            break;
        }
        case WM_DESTROY:
            break;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const char MAIN_WINDOW_CLASS_NAME[] = "MainWindowClass";
    const char SUB_WINDOW_CLASS_NAME[] = ID_SUB_WINDOW_CLASS;

    WNDCLASS wcMain = {};
    wcMain.lpfnWndProc = WindowProc;
    wcMain.hInstance = hInstance;
    wcMain.lpszClassName = MAIN_WINDOW_CLASS_NAME;
    wcMain.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcMain.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    WNDCLASS wcSub = {};
    wcSub.lpfnWndProc = SubWindowProc;
    wcSub.hInstance = hInstance;
    wcSub.lpszClassName = SUB_WINDOW_CLASS_NAME;
    wcSub.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcSub.hbrBackground = (HBRUSH)(COLOR_3DFACE + 1); // 3D face color

    RegisterClass(&wcMain);
    RegisterClass(&wcSub);

    // Create and show the sub-window
    HWND hwndSub = CreateWindowEx(
        WS_EX_CLIENTEDGE, SUB_WINDOW_CLASS_NAME, "Configure Margins",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 200, 250,
        nullptr, nullptr, hInstance, nullptr
    );

    if (hwndSub == NULL) {
        return 0;
    }

    ShowWindow(hwndSub, nCmdShow);
    UpdateWindow(hwndSub);

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
