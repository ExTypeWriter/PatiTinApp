#include <gtk/gtk.h>
#include <stdio.h>

void activate(GtkApplication* app, gpointer user_data)
{
    // Create a new window
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Hello, Gtk!");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 100);

    // Create a label widget
    GtkWidget *label = gtk_label_new(NULL);
    gtk_container_add(GTK_CONTAINER(window), label);

    // Use printf to update the label text
    char text[100];
    sprintf(text, "Paitin app.");
    gtk_label_set_markup(GTK_LABEL(label), text);

    gtk_widget_show_all(window);
}


int main(int argc, char **argv)
{
    GtkApplication *app = gtk_application_new("com.example.gtkapp", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), "Fuck up");
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
