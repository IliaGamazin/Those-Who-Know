#ifndef MESSENGER_H
#define MESSENGER_H

#include "../inc/libs.h"
#include "../inc/headerbar.h"

#define MAIN_WINDOW_WIDTH 1280
#define MAIN_WINDOW_HEIGHT 720

void import_css_theme(const char* theme);
void create_main_window(GtkApplication* app, gpointer user_data);

#endif
