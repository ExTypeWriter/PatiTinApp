#include <stdio.h>
#include <string.h>
#include <event.h>
#include "event.c"
#include <gtk/gtk.h>
#include <time.h>
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

gboolean cancel = FALSE;

static void on_button_clicked(GtkButton *button, gpointer userdata);

static gboolean on_update_time(gpointer userdata);

int main(int argc, char **argv)
{
    // Interface part
    gtk_init(&argc, &argv);
    GtkWidget *window, *box1, *btn1, *btn2, *btn3, *btn4, *btn5, *btn6, *btn7, *btnCancel, *labelC, *labelT, *grid;
    GtkContainer *main_container;
    GtkCssProvider *provider;
    char *app_title = "Patitin2";
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    main_container = GTK_CONTAINER(window);
    // CSS BG Styling
    GtkStyleContext *context;
    provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(provider, "style.css", NULL);
    context = gtk_widget_get_style_context(window);
    gtk_style_context_add_class(context, "window");
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

    // Windows configuration
    gtk_window_set_title(GTK_WINDOW(window), app_title);
    gtk_window_set_decorated(GTK_WINDOW(window), TRUE);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_maximize(GTK_WINDOW(window));
    gtk_window_set_resizable(GTK_WINDOW(window), TRUE);
    // Grid configuration
    grid = gtk_grid_new();
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    // Set the number of columns in the grid to 2
    gtk_grid_insert_column(GTK_GRID(grid), 0); // Insert first column
    gtk_grid_insert_column(GTK_GRID(grid), 1); // Insert second column
    // Box1 configuration
    box1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    // Button add Label
    btn1 = gtk_button_new_with_label("Create Task");
    btn2 = gtk_button_new_with_label("All Task");
    btn3 = gtk_button_new_with_label("Outdated Task");
    btn4 = gtk_button_new_with_label("Favorited");
    btn5 = gtk_button_new_with_label("Delete Task");
    btn6 = gtk_button_new_with_label("Search");
    btn7 = gtk_button_new_with_label("Edit Task");
    btnCancel = gtk_button_new_with_label("Cancel");
    // CSS BTN1 Styling
    GtkStyleContext *btn_context;
    btn_context = gtk_widget_get_style_context(btn1); // Get CSS Style
    gtk_style_context_add_class(btn_context, "button"); // Get style from class
    gtk_style_context_add_provider(btn_context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER); // Add style to provider
    // CSS BTN2 Styling
    GtkStyleContext *btn_context1;
    btn_context1 = gtk_widget_get_style_context(btn2);
    gtk_style_context_add_class(btn_context1, "buttonN");
    gtk_style_context_add_provider(btn_context1, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    // CSS BTN3 Styling
    GtkStyleContext *btn_context2;
    btn_context2 = gtk_widget_get_style_context(btn3);
    gtk_style_context_add_class(btn_context2, "buttonN");
    gtk_style_context_add_provider(btn_context2, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    // CSS BTN4 Styling
    GtkStyleContext *btn_context3;
    btn_context3 = gtk_widget_get_style_context(btn4);
    gtk_style_context_add_class(btn_context3, "buttonN");
    gtk_style_context_add_provider(btn_context3, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    // CSS BTN5 Styling
    GtkStyleContext *btn_context4;
    btn_context4 = gtk_widget_get_style_context(btn5);
    gtk_style_context_add_class(btn_context4, "buttonB");
    gtk_style_context_add_provider(btn_context4, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    // CSS BTN6 Styling
    GtkStyleContext *btn_context5;
    btn_context5 = gtk_widget_get_style_context(btn6);
    gtk_style_context_add_class(btn_context5, "buttonN");
    gtk_style_context_add_provider(btn_context5, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    // CSS BTN3 Styling
    GtkStyleContext *btn_context6;
    btn_context6 = gtk_widget_get_style_context(btn7);
    gtk_style_context_add_class(btn_context6, "buttonN");
    gtk_style_context_add_provider(btn_context6, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    // CSS CurrBTN Styling
    GtkStyleContext *btn_context7;
    btn_context7 = gtk_widget_get_style_context(btnCancel);
    gtk_style_context_add_class(btn_context7, "buttonB");
    gtk_style_context_add_provider(btn_context7, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    // Clock widget
    labelC = gtk_label_new(NULL);
    // App banner
    labelT = gtk_label_new(NULL);
    g_timeout_add(100, on_update_time, labelC);

    // Main container
    gtk_container_add(main_container, GTK_WIDGET(grid));
    gtk_grid_attach(GTK_GRID(grid), labelT, 0, 0, 2, 1); // span both columns
    gtk_grid_attach(GTK_GRID(grid), labelC, 0, 1, 2, 1); 
    gtk_grid_insert_row(GTK_GRID(grid), 2);  // Insert second row
    gtk_grid_attach(GTK_GRID(grid), btn1, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn2, 1, 2, 1, 1);
    gtk_grid_insert_row(GTK_GRID(grid), 3);
    gtk_grid_attach(GTK_GRID(grid), btn3, 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn4, 1, 3, 1, 1);
    gtk_grid_insert_row(GTK_GRID(grid), 4);
    gtk_grid_attach(GTK_GRID(grid), btn7, 0, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn6, 1, 4, 1, 1);
    gtk_grid_insert_row(GTK_GRID(grid), 5); 
    gtk_grid_attach(GTK_GRID(grid), btn5, 0, 5, 2, 1);
    // CSS Grid Styling
    GtkStyleContext *grid_context;
    grid_context = gtk_widget_get_style_context(grid);
    gtk_style_context_add_class(grid_context, "grid");
    gtk_style_context_add_provider(grid_context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

    // Text Label
    gtk_container_add(GTK_CONTAINER(window), labelT);
    // App Label
    char text[100];
    sprintf(text, "Patitin App.");
    gtk_label_set_markup(GTK_LABEL(labelT), text);
     // CSS App Label Styling
    GtkStyleContext *Label_Patitin;
    Label_Patitin = gtk_widget_get_style_context(labelT);
    gtk_style_context_add_class(Label_Patitin, "Patitin");
    gtk_style_context_add_provider(Label_Patitin, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
     // CSS Clock Styling
    GtkStyleContext *clock_context;
    clock_context = gtk_widget_get_style_context(labelC);
    gtk_style_context_add_class(clock_context, "clock");
    gtk_style_context_add_provider(clock_context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    // Button event 
    g_signal_connect(btn1, "clicked", G_CALLBACK(on_button_clicked), NULL); // Connect the "clicked" signal of btn1 to the callback function
    g_signal_connect(btn2, "clicked", G_CALLBACK(on_button_clicked), NULL);
    g_signal_connect(btn3, "clicked", G_CALLBACK(on_button_clicked), NULL);
    g_signal_connect(btn4, "clicked", G_CALLBACK(on_button_clicked), NULL);
    g_signal_connect(btn5, "clicked", G_CALLBACK(on_button_clicked), NULL);
    g_signal_connect(btn6, "clicked", G_CALLBACK(on_button_clicked), NULL);
    g_signal_connect(btn7, "clicked", G_CALLBACK(on_button_clicked), NULL);
    // Window destroy handler
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL); 
    gtk_widget_show_all(window); // Show widget in application window
    gtk_main();
    return 0;
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

static void on_button_clicked(GtkButton *button, gpointer userdata)
{
    const gchar *label = gtk_button_get_label(button); // Get button Label
    // event.c Declaration
    Year *Patitin = createYear(-1);
    Stack *outdate = createStack(100);
    char buffer[10];
    int cmd;
    int year = -1, month = -1, day = -1, favorite = -1;
    char start[12], end[12], event[3000];
    readTextFile(Patitin);
    cleanOutdatedData(Patitin, outdate);
    // Button statement
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
    else if (strcmp(label, "Outdated Task") == 0)
    {
        displayOutdated(outdate);
    }
    else if (strcmp(label, "Favorited") == 0)
    {
        displayFavorite(Patitin);
    }
    else if (strcmp(label, "Delete Task") == 0)
    {
        printf(YEL"Please input date to show all Lists in that day\n"RESET);
        userInput(&year, &month, &day, start, end, event, &favorite, 2);
        deleteEvent(Patitin, outdate, year, month, day);
    }
    else if (strcmp(label, "Search") == 0)
    {
        printf(YEL"Please insert date and name to search\n");
        printf("(leave \"--\" if don\'t want to search in that fields)\n");
        printf("*** for now you can only search by only one fields at the time "
               "***\n"RESET);
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
        printf(YEL"Please input date to show all Lists in that day\n"RESET);
        userInput(&year, &month, &day, start, end, event, &favorite, 2);
        edit(Patitin, year, month, day);
    }
    saveToText(Patitin);
    saveToOutdated(outdate);
    printf(GRN"%s Pressed!\n"RESET, label);
}