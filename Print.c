#include <gtk/gtk.h>

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *button1, *button2, *button3;
    GtkWidget *hbox;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Button Example");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_container_add(GTK_CONTAINER(window), hbox);

    button1 = gtk_button_new_with_label("Button 1");
    gtk_box_pack_start(GTK_BOX(hbox), button1, TRUE, TRUE, 0);

    button2 = gtk_button_new_with_label("Button 2");
    gtk_box_pack_start(GTK_BOX(hbox), button2, TRUE, TRUE, 0);

    button3 = gtk_button_new_with_label("Button 3");
    gtk_box_pack_start(GTK_BOX(hbox), button3, TRUE, TRUE, 0);

    g_signal_connect(button1, "clicked", G_CALLBACK(g_print), "Button 1 clicked\n");
    g_signal_connect(button2, "clicked", G_CALLBACK(g_print), "Button 2 clicked\n");
    g_signal_connect(button3, "clicked", G_CALLBACK(g_print), "Button 3 clicked\n");

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
