#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <gtk/gtk.h>

gint ShowNum(gpointer label);

int main(int argc, char *argv[])
{

    GtkWidget *window;
    GtkWidget *vbox;  
    GtkWidget *label;
    GtkWidget *text_label;

    gpointer data;


    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_resizable(GTK_WINDOW(window), TRUE);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(window), "输出数字");
    gtk_container_set_border_width(GTK_CONTAINER(window), 20); 

    g_signal_connect_swapped(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit), NULL);
    

    vbox = gtk_vbox_new(FALSE, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_container_border_width(GTK_CONTAINER(vbox), 150);
    gtk_widget_show(vbox);


    text_label = gtk_label_new("");
    gtk_box_pack_start(GTK_BOX(vbox), text_label, FALSE, FALSE, 10);
    label = gtk_label_new("Number = 0");
    gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 10);
    gtk_label_set_markup(
        GTK_LABEL(text_label), "<span foreground='blue' font_desc='30'>输出几个数字：</span>");
    gtk_widget_show(text_label);
    gtk_widget_show(label);


    gtk_widget_show(window);

    g_timeout_add(1000, ShowNum, (gpointer)label);

    gtk_main();
}

gint ShowNum(gpointer label)
{
    int static count = 1;
    char string[100];
  
    sprintf(string, "%d", count++);
    gtk_label_set_text(label, string);

    if(count == 100)
      count = 0;
}
