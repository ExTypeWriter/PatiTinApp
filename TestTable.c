#include <gtk/gtk.h>

void on_activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Table Example");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    
    // Create a new grid and attach the labels to it
    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);
    
    GtkWidget *label1 = gtk_label_new("Label 1");
    gtk_grid_attach(GTK_GRID(grid), label1, 0, 0, 1, 1);
    
    GtkWidget *label2 = gtk_label_new("Label 2");
    gtk_grid_attach(GTK_GRID(grid), label2, 1, 0, 1, 1);
    
    GtkWidget *label3 = gtk_label_new("Label 3");
    gtk_grid_attach(GTK_GRID(grid), label3, 0, 1, 1, 1);
    
    GtkWidget *label4 = gtk_label_new("Label 4");
    gtk_grid_attach(GTK_GRID(grid), label4, 1, 1, 1, 1);

    gtk_widget_show_all(window);
}

int main(int argc, char *argv[]) {
    GtkApplication *app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
