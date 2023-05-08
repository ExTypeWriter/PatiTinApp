#include <stdio.h>
#include <string.h>
#include <event.h>
#include "event.c"
#include <gtk/gtk.h>
#include <time.h>

static void on_button_clicked(GtkButton *button, gpointer userdata);

static void on_button_clicked_curr_time(GtkButton *button, gpointer userdata);

static gboolean on_update_time(gpointer userdata);

static void activate(GtkApplication *app, gpointer userdata);

int main(int argc, char **argv)
{
    GtkApplication *app;
    int ret;
    app = gtk_application_new("paitin.todo", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    ret = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return 0;
}

static void on_button_clicked(GtkButton *button, gpointer userdata)
{
    const gchar *label = gtk_button_get_label(button);
    Year *Patitin = createYear(-1);
    Stack *outdate = createStack(100);
    char buffer[10];
    int cmd;
    int year = -1, month = -1, day = -1, favorite = -1;
    char start[12], end[12], event[3000];
    readTextFile(Patitin);
    if (strcmp(label, "Create Task") == 0)
    {
        // printf("Incase!\n");
        userInput(&year, &month, &day, start, end, event, &favorite, 1);
        insert(Patitin, year, month, day, start, end, event, favorite);
    }
    else if (strcmp(label, "All Task") == 0)
    {
        // printf("Incase!\n");
        int allTask = 0;
        displayAll(Patitin, 2, &allTask);
    }
    else if (strcmp(label, "Outdated") == 0)
    {
        displayOutdated(outdate);
    }
    else if (strcmp(label, "Favorited") == 0)
    {
        displayFavorite(Patitin);
    }
    else if (strcmp(label, "Delete Task") == 0)
    {
        printf("Please input date to show all Lists in that day\n");
        userInput(&year, &month, &day, start, end, event, &favorite, 2);
        deleteEvent(Patitin, outdate, year, month, day);
    }
    else if (strcmp(label, "Search") == 0)
    {
        printf("Please insert date and name to search\n");
        printf("(leave \"--\" if don't want to search in that fields)\n");
        printf("*** for now you can only search by only one fields at the time "
               "***\n");
        userInput(&year, &month, &day, start, end, event, &favorite, 3);

        // searchByDate
        if (day != -1 && month != -1 && year != -1 && !strcmp(event, "--"))
        {
            displayByDate(Patitin, year, month, day);
        }
        // searchByDay
        else if (day != -1 && month == -1 && year == -1 && !strcmp(event, "--"))
        {
            displayByDay(Patitin, day);
        }
        // searchByMonth
        else if (day == -1 && month != -1 && year == -1 && !strcmp(event, "--"))
        {
            displayByMonth(Patitin, month);
        }
        // searchByYear
        else if (day == -1 && month == -1 && year != -1 && !strcmp(event, "--"))
        {
            displayByYear(Patitin, year);
        }
        // searchByName
        else if (day == -1 && month == -1 && year == -1 && strcmp(event, "--"))
        {
            displayByEvent(Patitin, event);
        }
    }
    else if (strcmp(label, "Edit Task") == 0)
    {
        printf("Please input date to show all Lists in that day\n");
        userInput(&year, &month, &day, start, end, event, &favorite, 2);
        edit(Patitin, year, month, day);
    }
    printf("%s Pressed!\n", label);
}

static void on_button_clicked_curr_time(GtkButton *button, gpointer userdata)
{
    displayCurrentTime();
}

static gboolean on_update_time(gpointer userdata)
{
    GtkWidget *label = GTK_WIDGET(userdata);
    char buffer[256];
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, 256, "%I:%M:%S %p", timeinfo);
    gtk_label_set_text(GTK_LABEL(label), buffer);
    return G_SOURCE_CONTINUE;
}

static void activate(GtkApplication *app, gpointer userdata)
{
    GtkWidget *window, *box1, *btn1, *btn2, *btn3, *btn4, *btn5, *btn6, *btn7, *btn8, *btnCurrtime, *labelC, *labelT, *grid;
    GtkWindow *windows;
    GtkBox *box1s;
    GtkContainer *main_container;
    char *app_title = "PaiTin2";
    window = gtk_application_window_new(app);
    windows = GTK_WINDOW(window);
    main_container = GTK_CONTAINER(window);
    // Windows configuration
    gtk_window_set_title(windows, app_title);
    gtk_window_set_decorated(windows, TRUE);
    gtk_window_set_position(windows, GTK_WIN_POS_CENTER);
    gtk_window_maximize(windows);
    gtk_window_set_resizable(windows, TRUE);
        // Grid configuration
        grid = GTK_WIDGET(gtk_grid_new());
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    // Set the number of columns in the grid to 2
    gtk_grid_insert_column(GTK_GRID(grid), 0); // Insert first column
    gtk_grid_insert_column(GTK_GRID(grid), 1); // Insert second column
    // Box1 configuration
    box1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    box1s = GTK_BOX(box1);
    // Container Widget management
    // Button
    btn1 = gtk_button_new_with_label("Create Task");
    btn2 = gtk_button_new_with_label("All Task");
    btn3 = gtk_button_new_with_label("Outdated Task");
    btn4 = gtk_button_new_with_label("Favorited");
    btn5 = gtk_button_new_with_label("Delete Task");
    btn6 = gtk_button_new_with_label("Search");
    btn7 = gtk_button_new_with_label("Edit Task");
    btnCurrtime = gtk_button_new_with_label("Current time.");
    // Clock widget
    labelC = gtk_label_new(NULL);
    labelT = gtk_label_new(NULL);
    g_timeout_add(100, on_update_time, labelC);
    // Main container
    gtk_container_add(main_container, GTK_WIDGET(grid));
    gtk_grid_attach(GTK_GRID(grid), labelT, 0, 0, 2, 1); // span both columns
    gtk_grid_attach(GTK_GRID(grid), labelC, 0, 1, 2, 1); // span both columns
    gtk_grid_insert_row(GTK_GRID(grid), 2);              // Insert row at index 2
    gtk_grid_attach(GTK_GRID(grid), btn1, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn2, 1, 2, 1, 1);
    gtk_grid_insert_row(GTK_GRID(grid), 3); // Insert row at index 3
    gtk_grid_attach(GTK_GRID(grid), btn3, 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn4, 1, 3, 1, 1);
    gtk_grid_insert_row(GTK_GRID(grid), 4); // Insert row at index 3
    gtk_grid_attach(GTK_GRID(grid), btn5, 0, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn6, 1, 4, 1, 1);
    gtk_grid_insert_row(GTK_GRID(grid), 5); // Insert row at index 3
    gtk_grid_attach(GTK_GRID(grid), btn7, 0, 5, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btnCurrtime, 1, 5, 1, 1); // span both columns
    // Text Label
    gtk_container_add(GTK_CONTAINER(window), labelT);
    // Use printf to update the label text
    char text[100];
    sprintf(text, "Paitin App.");
    gtk_label_set_markup(GTK_LABEL(labelT), text);
    // Button function
    g_signal_connect(btn1, "clicked", G_CALLBACK(on_button_clicked), NULL); // Connect the "clicked" signal of btn1 to the callback function
    g_signal_connect(btn2, "clicked", G_CALLBACK(on_button_clicked), NULL);
    g_signal_connect(btn3, "clicked", G_CALLBACK(on_button_clicked), NULL);
    g_signal_connect(btn4, "clicked", G_CALLBACK(on_button_clicked), NULL);
    g_signal_connect(btn5, "clicked", G_CALLBACK(on_button_clicked), NULL);
    g_signal_connect(btn6, "clicked", G_CALLBACK(on_button_clicked), NULL);
    g_signal_connect(btn7, "clicked", G_CALLBACK(on_button_clicked), NULL);

    g_signal_connect(btnCurrtime, "clicked", G_CALLBACK(on_button_clicked_curr_time), NULL);
    gtk_widget_show_all(window);
}