#include "Win_Key_Listener.h"

int main()
{
    bool running = true;
    Win_Key_Listener l;
    l.start_listening(&running);

    while (running) { }
    return 0;
}