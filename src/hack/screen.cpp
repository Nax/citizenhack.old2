#include <hack/screen.h>

Screen::Screen()
{
    term = wish_init();
    msg_bar = wish_view_create(term);
    fullscreen = wish_view_create(term);
    main_view = wish_view_create(term);
    status_bar = wish_view_create(term);
    handle_resize();
}

Screen::~Screen()
{
    wish_view_free(status_bar);
    wish_view_free(main_view);
    wish_view_free(fullscreen);
    wish_view_free(msg_bar);
    wish_quit(term);
}

void Screen::handle_resize()
{
    wish_size size;

    wish_get_size(term, &size);
    wish_view_fullscreen(fullscreen);
    wish_view_resize(msg_bar, 0, 0, size.x, 1);
    wish_view_resize(main_view, 0, 1, 80, 21);
    wish_view_resize(status_bar, 0, 22, 80, 2);
}

void Screen::swap()
{
    wish_draw(term);
}

void Screen::clear()
{
    wish_clear(term);
}

wish_unicode Screen::getchar()
{
    return wish_getchar(term);
}
