//
// Created by Lachlan Krautz on 18/08/2016.
//

#include "Win_Key_Listener.h"
#include <iostream>

namespace {

    HHOOK hook;

    LRESULT CALLBACK hook_callback(int nCode, WPARAM wParam, LPARAM lParam)
    {
        if (nCode < 0) {
            return CallNextHookEx(hook, nCode, wParam, lParam);
        }
        if (wParam==WM_KEYDOWN) {
            // lParam is the pointer to the struct containing the data needed, so cast and assign it to kdbStruct.
            KBDLLHOOKSTRUCT* kbd_struct = (KBDLLHOOKSTRUCT*) lParam;
            Win_Key_Listener& l = Win_Key_Listener::get_instance();
            l.handle_key(kbd_struct->vkCode);
        }
        return CallNextHookEx(hook, nCode, wParam, lParam);
    }
}

Win_Key_Listener& Win_Key_Listener::get_instance()
{
    static Win_Key_Listener instance;
    return instance;
}

void Win_Key_Listener::handle_key(DWORD code)
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

void Win_Key_Listener::start_listening()
{
    listening_ = true;
    std::thread t([&] {
        hook = SetWindowsHookEx(WH_KEYBOARD_LL, hook_callback, NULL, 0);
        if (!hook) {
            std::cout << "failed to install hook" << std::endl;
        }
        std::cout << "listening" << std::endl;
        // Don't mind this, it is a meaningless loop to keep a console application running.
        // I used this to test the keyboard hook functionality. If you want to test it, keep it in ;)
        MSG msg;
        while (GetMessage(&msg, NULL, 0, 0)) {
            std::cout << "get message" << std::endl;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    });
    t.detach();
}

void Win_Key_Listener::stop_listening()
{
    UnhookWindowsHookEx(hook);
    listening_ = false;
}

bool Win_Key_Listener::is_listening()
{
    return listening_;
}

Win_Key_Listener::~Win_Key_Listener()
{
    UnhookWindowsHookEx(hook);
}
