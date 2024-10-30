#include "../inc/client.h"

static void activate(GtkApplication* app, gpointer user_data) {
    create_login_window(app, user_data);
}

int main(int argc, char **argv) {
    GtkApplication *mango_chat;
    int status;

    mango_chat = gtk_application_new("mango.chat", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(mango_chat, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(mango_chat), argc, argv);

    g_object_unref(mango_chat);
    return status;
}
