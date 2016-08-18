#include "Win_Key_Listener.h"

int main()
{
    Win_Key_Listener &l = Win_Key_Listener::get_instance();
    l.start_listening();

    while (l.is_listening()) { }
    return 0;
}