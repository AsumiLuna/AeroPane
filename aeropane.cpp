#include <windows.h>
#include <dwmapi.h>
#include <iostream>
#include "resource.h"

#pragma comment(lib, "dwmapi.lib")

#define ID_BUTTON_LAUNCH_MAIN 1
#define ID_SUB_WINDOW_CLASS "SubWindowClass"
#define ID_MAIN_WINDOW_CLASS "MainWindowClass"

#define ID_TEXT_BOX1 101
#define ID_TEXT_BOX2 102
#define ID_TEXT_BOX3 103
#define ID_TEXT_BOX4 104
#define ID_SPIN1 201
#define ID_SPIN2 202
#define ID_SPIN3 203
#define ID_SPIN4 204

// DWM frame global variables
int margin1 = -1;
int margin2 = -1;
int margin3 = -1;
int margin4 = -1;

// Function prototypes
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK SubWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// Create and init sub controls
void CreateSubWindowControls(HWND hwnd) {
    HWND hTextBox1, hTextBox2, hTextBox3, hTextBox4;
    HWND hSpin1, hSpin2, hSpin3, hSpin4;
    HWND hLaunchButton;
    HWND hHideButton;

    hTextBox1 = CreateWindowEx(
        0, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
        10, 10, 100, 25, hwnd, (HMENU)ID_TEXT_BOX1,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), nullptr
    );

    hTextBox2 = CreateWindowEx(
        0, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
        10, 45, 100, 25, hwnd, (HMENU)ID_TEXT_BOX2,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), nullptr
    );

    hTextBox3 = CreateWindowEx(
        0, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
        10, 80, 100, 25, hwnd, (HMENU)ID_TEXT_BOX3,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), nullptr
    );

    hTextBox4 = CreateWindowEx(
        0, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
        10, 115, 100, 25, hwnd, (HMENU)ID_TEXT_BOX4,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), nullptr
    );

    // Create spin buttons
    hSpin1 = CreateWindowEx(
        0, UPDOWN_CLASS, nullptr,
        WS_CHILD | WS_VISIBLE | UDS_ALIGNRIGHT | UDS_SETBUDDYINT,
        115, 10, 20, 25, hwnd, (HMENU)ID_SPIN1,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), nullptr
    );
    SendMessage(hSpin1, UDM_SETRANGE, 0, MAKELPARAM(-1699999, 1700000)); // Set range -100 to 100

    hSpin2 = CreateWindowEx(
        0, UPDOWN_CLASS, nullptr,
        WS_CHILD | WS_VISIBLE | UDS_ALIGNRIGHT | UDS_SETBUDDYINT,
        115, 45, 20, 25, hwnd, (HMENU)ID_SPIN2,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), nullptr
    );
    SendMessage(hSpin2, UDM_SETRANGE, 0, MAKELPARAM(-1699999, 1700000)); // Set range -100 to 100

    hSpin3 = CreateWindowEx(
        0, UPDOWN_CLASS, nullptr,
        WS_CHILD | WS_VISIBLE | UDS_ALIGNRIGHT | UDS_SETBUDDYINT,
        115, 80, 20, 25, hwnd, (HMENU)ID_SPIN3,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), nullptr
    );
    SendMessage(hSpin3, UDM_SETRANGE, 0, MAKELPARAM(-1699999, 1700000)); // Set range -100 to 100

    hSpin4 = CreateWindowEx(
        0, UPDOWN_CLASS, nullptr,
        WS_CHILD | WS_VISIBLE | UDS_ALIGNRIGHT | UDS_SETBUDDYINT,
        115, 115, 20, 25, hwnd, (HMENU)ID_SPIN4,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), nullptr
    );
    SendMessage(hSpin4, UDM_SETRANGE, 0, MAKELPARAM(-1699999, 1700000)); // Set range -100 to 100

    SendMessage(hSpin1, UDM_SETBUDDY, (WPARAM)hTextBox1, 0);
    SendMessage(hSpin2, UDM_SETBUDDY, (WPARAM)hTextBox2, 0);
    SendMessage(hSpin3, UDM_SETBUDDY, (WPARAM)hTextBox3, 0);
    SendMessage(hSpin4, UDM_SETBUDDY, (WPARAM)hTextBox4, 0);

    hLaunchButton = CreateWindow(
        "BUTTON", "Create Window",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        10, 150, 150, 30,
        hwnd, (HMENU)ID_BUTTON_LAUNCH_MAIN,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), nullptr
    );
}

// Function to create the main window and handle messages
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    [[maybe_unused]] static HBRUSH hBackgroundBrush = nullptr;
    switch (uMsg) {
        case WM_CREATE: {
            MARGINS margins = { margin1, margin2, margin3, margin4 };
            DwmExtendFrameIntoClientArea(hwnd, &margins);
            SetWindowPos(hwnd, nullptr, 0, 0, 800, 600, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
            break;
        }
        case WM_PAINT: {

            break;
        }
        case WM_ERASEBKGND: {
            // Prevent background erasing
            return 1;
        }
        case WM_NCHITTEST: {
            // Drag
            LRESULT result = DefWindowProc(hwnd, uMsg, wParam, lParam);
            if (result == HTCLIENT) {
                result = HTCAPTION;
            }
            return result;
        }
        case WM_DESTROY:
            DestroyWindow(hwnd);
            break;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

// Conf window procedure
LRESULT CALLBACK SubWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {

        case WM_CREATE:
            CreateSubWindowControls(hwnd);
            break;

        case WM_COMMAND: {
            if (LOWORD(wParam) == ID_BUTTON_LAUNCH_MAIN) {
                // Get set margins
                char buffer[10];
                GetWindowText(GetDlgItem(hwnd, ID_TEXT_BOX1), buffer, sizeof(buffer));
                margin1 = atoi(buffer);
                GetWindowText(GetDlgItem(hwnd, ID_TEXT_BOX2), buffer, sizeof(buffer));
                margin2 = atoi(buffer);
                GetWindowText(GetDlgItem(hwnd, ID_TEXT_BOX3), buffer, sizeof(buffer));
                margin3 = atoi(buffer);
                GetWindowText(GetDlgItem(hwnd, ID_TEXT_BOX4), buffer, sizeof(buffer));
                margin4 = atoi(buffer);


                HWND hMainWindow = CreateWindowEx(
                    WS_EX_COMPOSITED | WS_EX_LAYERED,
                    ID_MAIN_WINDOW_CLASS, nullptr,
                    WS_OVERLAPPEDWINDOW,
                    CW_USEDEFAULT, CW_USEDEFAULT, 14000, 14000,
                    nullptr, nullptr, reinterpret_cast<HINSTANCE>(GetWindowLongPtr(hwnd, GWLP_HINSTANCE)), nullptr
                );



                if (hMainWindow != nullptr) {
                    MARGINS margins = { margin1, margin2, margin3, margin4 };
                    DwmExtendFrameIntoClientArea(hMainWindow, &margins);

                    ShowWindow(hMainWindow, SW_SHOW);
                    UpdateWindow(hMainWindow);
                }
            }
            break;
        }

        case WM_SIZE: {
            RECT rcClient;
            GetClientRect(hwnd, &rcClient);
            int width = rcClient.right;
            int height = rcClient.bottom;

            SetWindowPos(GetDlgItem(hwnd, ID_TEXT_BOX1), nullptr, 22, 10, width - 45, 25, SWP_NOZORDER | SWP_NOACTIVATE);
            SetWindowPos(GetDlgItem(hwnd, ID_TEXT_BOX2), nullptr, 22, 45, width - 45, 25, SWP_NOZORDER | SWP_NOACTIVATE);
            SetWindowPos(GetDlgItem(hwnd, ID_TEXT_BOX3), nullptr, 22, 80, width - 45, 25, SWP_NOZORDER | SWP_NOACTIVATE);
            SetWindowPos(GetDlgItem(hwnd, ID_TEXT_BOX4), nullptr, 22, 115, width - 45, 25, SWP_NOZORDER | SWP_NOACTIVATE);
            SetWindowPos(GetDlgItem(hwnd, ID_SPIN1), nullptr, width - 22, 10, 20, 25, SWP_NOZORDER | SWP_NOACTIVATE);
            SetWindowPos(GetDlgItem(hwnd, ID_SPIN2), nullptr, width - 22, 45, 20, 25, SWP_NOZORDER | SWP_NOACTIVATE);
            SetWindowPos(GetDlgItem(hwnd, ID_SPIN3), nullptr, width - 22, 80, 20, 25, SWP_NOZORDER | SWP_NOACTIVATE);
            SetWindowPos(GetDlgItem(hwnd, ID_SPIN4), nullptr, width - 22, 115, 20, 25, SWP_NOZORDER | SWP_NOACTIVATE);

            SetWindowPos(GetDlgItem(hwnd, ID_BUTTON_LAUNCH_MAIN), nullptr, 10, height - 45, width - 20, 30, SWP_NOZORDER | SWP_NOACTIVATE);
            break;
        }

        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const WNDCLASSEX wcex = {
        sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW, WindowProc, 0, 0, hInstance, LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BLANK)), nullptr,
        (HBRUSH) (COLOR_WINDOW + 1), nullptr, ID_MAIN_WINDOW_CLASS, nullptr
    };
    RegisterClassEx(&wcex);

    const WNDCLASSEX subWcex = {
        sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW, SubWindowProc, 0, 0, hInstance, nullptr, nullptr,
        (HBRUSH) (COLOR_WINDOW + 1), nullptr, ID_SUB_WINDOW_CLASS, nullptr
    };
    RegisterClassEx(&subWcex);


    HWND hSubWindow = CreateWindowEx(
        WS_EX_APPWINDOW,
        ID_SUB_WINDOW_CLASS, "Configure Margins",
        WS_OVERLAPPEDWINDOW,
        800, 600, 300, 250,
        nullptr, nullptr, hInstance, nullptr
    );

    if (!hSubWindow) {
        MessageBox(nullptr, "Something is not right. Failed to create maim window.", "Error", MB_OK);
        return 1;
    }


    HICON hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_AEROICON));
    SendMessage(hSubWindow, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
    SendMessage(hSubWindow, WM_SETICON, ICON_BIG, (LPARAM)hIcon);


    ShowWindow(hSubWindow, nCmdShow);
    UpdateWindow(hSubWindow);

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}
