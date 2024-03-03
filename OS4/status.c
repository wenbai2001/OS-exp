#include "status.h"

void ShowStatus(GtkWidget *vbox)
{
    GtkWidget *label;

    label = gtk_label_new("当前时间为");
    gtk_box_pack_end(GTK_BOX(vbox), label, FALSE, TRUE, 5);

    g_timeout_add(1000, GetTime, (gpointer)label);
}


gint GetTime(gpointer label)
{
    if(g_update == FALSE)
        return TRUE;
        
    time_t t;
    char string[150];
    time(&t); 
    int hours, mins, sec;
    long int num;
    
    num = GetUptime();
    hours = num/3600;
    mins = num%3600/60;
    sec = num%60;

    sprintf(string, " CPU利用率：%.2f %%   内存使用： %.2fG / %.2fG   系统运行时间：%dh %dm %ds   当前时间：%s",
           stat_info.cpu_ratio, (memo_info.MemTotal - memo_info.MemFree) / 1024.0 /1024.0 ,
         memo_info.MemTotal / 1024.0 /1024.0, hours, mins, sec, ctime(&t));
    string[strlen(string) - 1] = '\0';
    gtk_label_set_text(label, string);

    return TRUE;
}

long int GetUptime(void)
{
    int fd;
    char buf[30];
    long int data;
    if ((fd = open("/proc/uptime", O_RDONLY)) == -1)
    {
        perror("fail to uptime");
        return 0;
    }

    read(fd, buf, sizeof(buf));
    close(fd);

    sscanf(buf, "%ld",(long int*) &data);
    return data;

}
