#include "menu.h"

void CreateMenuBar(GtkWidget *vbox)
{
    GtkWidget *menu_bar;
    GtkWidget *file_menu;

    GtkWidget *file;
    GtkWidget *quit;
    GtkWidget *shutdown;
    GtkWidget *reboot;


    menu_bar = gtk_menu_bar_new();
    file_menu = gtk_menu_new();

    file = gtk_menu_item_new_with_label("文件");
    quit = gtk_menu_item_new_with_label("退出");
    shutdown = gtk_menu_item_new_with_label("关机");
    reboot = gtk_menu_item_new_with_label("重启");

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(file), file_menu);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), shutdown);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), reboot);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), quit);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), file);

    gtk_box_pack_start(GTK_BOX(vbox), menu_bar, FALSE, FALSE, 3);


    g_signal_connect(G_OBJECT(quit), "activate", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(G_OBJECT(shutdown), "activate", G_CALLBACK(MenuShutDown), NULL);
    g_signal_connect(G_OBJECT(reboot), "activate", G_CALLBACK(MenuReboot), NULL);
}


void MenuShutDown(GtkWidget *widget,gpointer data)
{
    system("shutdown -t 0");

}

void MenuReboot(GtkWidget *widget,gpointer data)
{
    system("reboot");
}



