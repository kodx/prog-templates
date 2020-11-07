#ifndef UNICODE
#define UNICODE
#endif 

#define WIN32_LEAN_AND_MEAN

#include <windows.h>

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

auto wWinMain(
        _In_ HINSTANCE hInstance,
        _In_opt_ HINSTANCE hPrevInstance,
        _In_ LPWSTR lpCmdLine,
        _In_ int nShowCmd
    ) 
-> int {
    // supress warnings on unreferenced formal parameters
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nShowCmd);

    auto lpzClass = TEXT("Hello Window Class!");

    WNDCLASS wc{ 0 };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = lpzClass;
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_APPWORKSPACE;

    if (!RegisterClass(&wc)) {
        return 1;
    }

    RECT screen_rect;
    GetWindowRect(GetDesktopWindow(), &screen_rect);
    auto w = screen_rect.right / 4;
    auto h = screen_rect.bottom / 4;
    auto x = screen_rect.right / 2 - (w / 2);
    auto y = screen_rect.bottom / 2 - (h / 2);

    HWND hwnd = CreateWindowEx(
        0,
        lpzClass,
        TEXT("Hello world!"),
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        x, y, w, h,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (hwnd == NULL) {
        return 2;
    }

    MSG msg{ 0 };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}


LRESULT CALLBACK WindowProc(
    HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
    case WM_LBUTTONUP:
        MessageBox(hWnd, TEXT("Clicked!"), TEXT("Event"), 0);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return 0;
}
