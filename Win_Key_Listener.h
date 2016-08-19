//
// Created by Lachlan Krautz on 18/08/2016.
//

#ifndef WINTEST_WINKEYLISTENER_H
#define WINTEST_WINKEYLISTENER_H

#include <Windows.h>
#include <thread>

class Win_Key_Listener {

public:
    static Win_Key_Listener& get_instance();
    void start_listening();
    void stop_listening();
    bool is_listening();
    void handle_key(DWORD code);
private:
    Win_Key_Listener(): listening_(false) {}
    bool listening_;
public:
    Win_Key_Listener(Win_Key_Listener const&) = delete;
    void operator=(Win_Key_Listener const &)  = delete;

    virtual ~Win_Key_Listener();
};

#endif //WINTEST_WINKEYLISTENER_H
