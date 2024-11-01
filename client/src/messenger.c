#include "../inc/messenger.h"

static void connect_to_server(GtkLabel *label) {
    int sock;
    struct sockaddr_in serv_addr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        gtk_label_set_text(label, "Socket creation error");
        return;
    }
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        gtk_label_set_text(label, "Invalid address");
        close(sock);
        return;
    }
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == 0) {
        gtk_label_set_text(label, "Connection established!");
    } 
    else {
        gtk_label_set_text(label, "Connection failed");
    }

    close(sock);
}

static void on_connect_button_clicked(GtkButton *button, gpointer user_data) {
    GtkLabel *label = GTK_LABEL(user_data);
    gtk_label_set_text(label, "Reconnecting...");
    connect_to_server(label);
}

void create_main_window(GtkApplication* app, gpointer user_data) {
    GtkWidget *main_window;
    GtkWidget *main_box; 
    GtkWidget *connect_label;
    GtkWidget *connect_button;
    GtkWidget *connect_button_box;

    main_window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(main_window), "Mango-chat-main");
    gtk_window_set_default_size(GTK_WINDOW(main_window), MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);
    gtk_window_set_resizable(GTK_WINDOW(main_window), TRUE);

    headbar_handler(main_window, "img/mango.png", "img/mango.png", "img/mango.png", 1);
    import_css_theme("css/mango.css");

    main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(main_window), main_box);

    connect_label = gtk_label_new("Press to connect!");
    gtk_box_pack_start(GTK_BOX(main_box), connect_label, TRUE, TRUE, 0);

    connect_button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_box_pack_start(GTK_BOX(main_box), connect_button_box, TRUE, TRUE, 0);

    connect_button = gtk_button_new_with_label("Reconnect");
    gtk_container_add(GTK_CONTAINER(connect_button_box), connect_button);

    g_signal_connect(connect_button, "clicked", G_CALLBACK(on_connect_button_clicked), connect_label);

    gtk_widget_show_all(main_window);
}

