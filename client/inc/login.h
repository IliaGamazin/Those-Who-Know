#ifndef LOGIN_H
#define LOGIN_H

/* This defines the functions used for managing the login window */

#include "../inc/libs.h"
#include "../inc/messenger.h"

#define LOGIN_WINDOW_WIDTH 480
#define LOGIN_WINDOW_HEIGHT 900

void create_login_window(GtkApplication* app, gpointer user_data);

#endif
