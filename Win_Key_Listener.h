//
// Created by Lachlan Krautz on 18/08/2016.
//

#ifndef WINTEST_WINKEYLISTENER_H
#define WINTEST_WINKEYLISTENER_H

#include <Windows.h>
#include <thread>

class Win_Key_Listener {

public:
    LRESULT CALLBACK hook_callback(int nCode, WPARAM wParam, LPARAM lParam);
    void start_listening(bool &running);
    void stop_listening();
private:
    void handle_key(DWORD code);
    HHOOK hook_;
    KBDLLHOOKSTRUCT kbd_struct_;
    bool &running_;
};

#endif //WINTEST_WINKEYLISTENER_H
