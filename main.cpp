#include <iostream>
#include <Windows.h>
#include <thread>

// variable to store the HANDLE to the hook. Don't declare it anywhere else then globally
// or you will get problems since every function uses this variable.
HHOOK _hook;

// This struct contains the data received by the hook callback. As you see in the callback function
// it contains the thing you will need: vkCode = virtual key code.
KBDLLHOOKSTRUCT kbdStruct;

bool running = true;

void ReleaseHook();

// This is the callback function. Consider it the event that is raised when, in this case,
// a key is pressed.
LRESULT CALLBACK HookCallback(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode >= 0) {
        // the action is valid: HC_ACTION.
        if (wParam == WM_KEYDOWN) {
            // lParam is the pointer to the struct containing the data needed, so cast and assign it to kdbStruct.
            kbdStruct = *((KBDLLHOOKSTRUCT*)lParam);
            // a key (non-system) is pressed.
            if (kbdStruct.vkCode == VK_F2) {
                std::cout << "F2 is pressed!" << std::endl;
            }
            else if (kbdStruct.vkCode == VK_F4) {
                std::cout << "F4 is pressed, exiting" << std::endl;
                ReleaseHook();
            }
        }
    }

    // call the next hook in the hook chain. This is necessary or your hook chain will break and the hook stops
    return CallNextHookEx(_hook, nCode, wParam, lParam);
}

void SetHook()
{
    // Set the hook and set it to use the callback function above
    // WH_KEYBOARD_LL means it will set a low level keyboard hook. More information about it at MSDN.
    // The last 2 parameters are NULL, 0 because the callback function is in the same thread and window as the
    // function that sets and releases the hook. If you create a hack you will not need the callback function
    // in another place then your own code file anyway. Read more about it at MSDN.
    if (!(_hook = SetWindowsHookEx(WH_KEYBOARD_LL, HookCallback, NULL, 0))) {
        MessageBox(NULL, "Failed to install hook!", "Error", MB_ICONERROR);
    } else {
        std::cout << "hook installed" << std::endl;
    }
}

void ReleaseHook()
{
    UnhookWindowsHookEx(_hook);
    running = false;
}

int main()
{
    std::thread t([] {
        // Set the hook
        SetHook();
        MSG msg;
        GetMessage(&msg, NULL, 0, 0);
    });
    t.detach();

    while (running) { }
    return 0;
}