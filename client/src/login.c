#include "../inc/login.h"

static void on_login_button_clicked(GtkButton *button, gpointer user_data) {
    GtkApplication *app = GTK_APPLICATION(user_data);
    GtkWidget *login_window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_destroy(login_window);
    create_main_window(app, NULL);
}

void create_login_window (GtkApplication* app, gpointer user_data) {
    GtkWidget *login_window;
    GtkWidget *login_box;
    GtkWidget *login_button;
    GtkWidget *login_button_box;

    login_window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(login_window), "Mango-chat-login");
    gtk_window_set_default_size(GTK_WINDOW(login_window), LOGIN_WINDOW_WIDTH, LOGIN_WINDOW_HEIGHT);
    gtk_window_set_resizable(GTK_WINDOW(login_window), FALSE);

    login_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(login_window), login_box);

    login_button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_box_pack_start(GTK_BOX(login_box), login_button_box, TRUE, TRUE, 0);

    login_button = gtk_button_new_with_label("Log in");
    gtk_container_add(GTK_CONTAINER(login_button_box), login_button);

    g_signal_connect(login_button, "clicked", G_CALLBACK(on_login_button_clicked), app);
    gtk_widget_show_all(login_window);
}
