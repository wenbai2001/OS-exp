#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <gtk/gtk.h>

gint SumNum(gpointer label);

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
    gtk_window_set_title(GTK_WINDOW(window), "计算总和");
    gtk_container_set_border_width(GTK_CONTAINER(window), 20); 

    g_signal_connect_swapped(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit), NULL);
    

    vbox = gtk_vbox_new(FALSE, 10); //每个对象是否有相同的大小
    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_container_border_width(GTK_CONTAINER(vbox), 150);
    gtk_widget_show(vbox);

    
    text_label = gtk_label_new("111");
    gtk_box_pack_start(GTK_BOX(vbox), text_label, FALSE, FALSE, 10);
    label = gtk_label_new("count = 0   sum = 0");
    gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 10);
    gtk_label_set_markup(
        GTK_LABEL(text_label), "<span foreground='red' font_desc='30'>打印累加和：</span>");
    gtk_widget_show(text_label);
    gtk_widget_show(label);

    // 显示窗口
    gtk_widget_show(window);
    // 延时1000ms 循环调用函数
    g_timeout_add(1000, SumNum, (gpointer)label);

    gtk_main();
}

gint SumNum(gpointer label) //gpointer指针结构体
{
    int static count = 1;
    int static sum = 0;
    char string[100];
  
    sum += count;
    sprintf(string, "总和 = %d", sum);
    gtk_label_set_text(label, string);
    count++;

    if(count == 1000)
      count = 0;
}
