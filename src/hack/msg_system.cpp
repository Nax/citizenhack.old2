#include <cstdarg>
#include <hack/screen.h>
#include <hack/msg_system.h>

size_t MsgSystem::size_max()
{
    return 0;
}

void MsgSystem::printf(const char* format, ...)
{
    va_list ap;
    char buffer[4096];

    va_start(ap, format);
    vsnprintf(buffer, 4096, format, ap);
    va_end(ap);
    puts(buffer);
}

void MsgSystem::puts(const char* str)
{
    _message = str;
}

void MsgSystem::clear()
{
    _message = "";
}

void MsgSystem::more()
{

}
