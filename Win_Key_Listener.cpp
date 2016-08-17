//
// Created by Lachlan Krautz on 18/08/2016.
//

#include "Win_Key_Listener.h"
#include <iostream>

LRESULT CALLBACK Win_Key_Listener::hook_callback(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode >= 0) {
        if (wParam == WM_KEYDOWN) {
            // lParam is the pointer to the struct containing the data needed, so cast and assign it to kdbStruct.
            kbd_struct_ = *((KBDLLHOOKSTRUCT*)lParam);
            handle_key(kbd_struct_.vkCode);
        }
    }
    return CallNextHookEx(hook_, nCode, wParam, lParam);
}

void Win_Key_Listener::handle_key (DWORD code)
{
    switch (code) {
    case VK_F2:
        std::cout << "F2 is pressed!" << std::endl;
        break;
    case VK_F4:
        std::cout << "F4 is pressed, exiting" << std::endl;
        stop_listening();
        break;
    default:
        break;
    }
}

void Win_Key_Listener::start_listening(bool &running)
{
    running_ = running;
    std::thread t([] {
        if (!(hook_ = SetWindowsHookEx(WH_KEYBOARD_LL, hook_callback, NULL, 0))) {
            std::cout << "failed to install hook" << std::endl;
        }
        MSG msg;
        GetMessage(&msg, NULL, 0, 0);
    });
    t.detach();
}

void Win_Key_Listener::stop_listening()
{
    UnhookWindowsHookEx(hook_);
    running_ = false;
}
