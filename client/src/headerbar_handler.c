#include "../inc/headerbar.h"

void on_close_button_clicked(GtkWidget *widget, gpointer data) {
    gtk_widget_destroy(GTK_WIDGET(data));
}

void on_minimize_button_clicked(GtkWidget *widget, gpointer data) {
    gtk_window_iconify(GTK_WINDOW(data));
}

void on_fullscreen_button_clicked(GtkWidget *widget, gpointer data) {
    if (gtk_window_is_maximized(GTK_WINDOW(data))) {
        gtk_window_unmaximize(GTK_WINDOW(data));
        gtk_window_present(GTK_WINDOW(data));
    } else {
        gtk_window_maximize(GTK_WINDOW(data));
    }
}

void headbar_handler(GtkWidget* window, const char* png1, const char* png2, const char* png3, WINDOW_TYPE type) {

    GtkHeaderBar *header_bar = GTK_HEADER_BAR(gtk_header_bar_new());   
    gtk_header_bar_set_show_close_button(header_bar, FALSE); 

    GtkWidget *minimize_button = NULL;
    GtkWidget *close_button = NULL;
    GtkWidget *fullscreen_button = NULL;

    if (type == MAIN) {
        minimize_button = gtk_button_new();
        close_button = gtk_button_new();
        fullscreen_button = gtk_button_new();

        gtk_widget_set_name(GTK_WIDGET(minimize_button), "mangoMinimize_button");
        gtk_widget_set_name(GTK_WIDGET(close_button), "mangoClose_button");
        gtk_widget_set_name(GTK_WIDGET(fullscreen_button), "mangoFullscreen_button");

        GtkWidget *minimize_image = gtk_image_new_from_file(png1);
        GtkWidget *close_image = gtk_image_new_from_file(png2);
        GtkWidget *fullscreen_image = gtk_image_new_from_file(png3);

        gtk_button_set_image(GTK_BUTTON(minimize_button), minimize_image);
        gtk_button_set_image(GTK_BUTTON(close_button), close_image);
        gtk_button_set_image(GTK_BUTTON(fullscreen_button), fullscreen_image);

        gtk_button_set_relief(GTK_BUTTON(close_button), GTK_RELIEF_NONE);
        gtk_button_set_relief(GTK_BUTTON(minimize_button), GTK_RELIEF_NONE);
        gtk_button_set_relief(GTK_BUTTON(fullscreen_button), GTK_RELIEF_NONE);

        g_signal_connect(close_button, "clicked", G_CALLBACK(on_close_button_clicked), window);
        g_signal_connect(minimize_button, "clicked", G_CALLBACK(on_minimize_button_clicked), window);
        g_signal_connect(fullscreen_button, "clicked", G_CALLBACK(on_fullscreen_button_clicked), window);

        gtk_header_bar_pack_end(header_bar, close_button);
        gtk_header_bar_pack_end(header_bar, fullscreen_button);
        gtk_header_bar_pack_end(header_bar, minimize_button);
    }
    else if(type == LOGIN) {
        minimize_button = gtk_button_new();
        close_button = gtk_button_new();

        gtk_widget_set_name(GTK_WIDGET(minimize_button), "mangoMinimize_button");
        gtk_widget_set_name(GTK_WIDGET(close_button), "mangoClose_button");

        GtkWidget *minimize_image = gtk_image_new_from_file(png1);
        GtkWidget *close_image = gtk_image_new_from_file(png2);

        gtk_button_set_image(GTK_BUTTON(minimize_button), minimize_image);
        gtk_button_set_image(GTK_BUTTON(close_button), close_image);

        gtk_button_set_relief(GTK_BUTTON(minimize_button), GTK_RELIEF_NONE);
        gtk_button_set_relief(GTK_BUTTON(close_button), GTK_RELIEF_NONE);
        
        g_signal_connect(minimize_button, "clicked", G_CALLBACK(on_minimize_button_clicked), window);
        g_signal_connect(close_button, "clicked", G_CALLBACK(on_close_button_clicked), window);

        gtk_header_bar_pack_end(header_bar, close_button);
        gtk_header_bar_pack_end(header_bar, minimize_button);
    }
    else if(type == MESSAGE) {
        close_button = gtk_button_new();
        
        gtk_widget_set_name(GTK_WIDGET(close_button), "mangoClose_button");

        GtkWidget *close_image = gtk_image_new_from_file(png2);

        gtk_button_set_image(GTK_BUTTON(close_button), close_image);

        g_signal_connect(close_button, "clicked", G_CALLBACK(on_close_button_clicked), window);

        gtk_header_bar_pack_end(header_bar, close_button);
    }

    gtk_window_set_titlebar(GTK_WINDOW(window), GTK_WIDGET(header_bar));
}

