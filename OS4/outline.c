#include "outline.h"
#include "status.h"


void CreateOutline(GtkWidget *notebook)
{

    GtkWidget *hbox;
    GtkWidget *vbox;
    OUTLINE_INFO oinfo;

    
    memset(&oinfo, '\0', sizeof(oinfo));


    hbox = gtk_hbox_new(TRUE, 5);
    gtk_container_border_width(GTK_CONTAINER(hbox), 5);


    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), hbox, gtk_label_new("系统概要"));


    GetOutlineInfo(&oinfo);

    vbox = gtk_vbox_new(TRUE, 5);
    gtk_container_border_width(GTK_CONTAINER(vbox), 20);
    gtk_container_add(GTK_CONTAINER(hbox), vbox);

    ShowInfo(vbox, oinfo);
}

void GetOutlineInfo(p_outline_info oinfo)
{
    int fd;
    int bytes;
    char buf[50];
    char *pchar, *tp;

    if ((fd = open("/proc/sys/kernel/hostname", O_RDONLY)) == -1)
    {
        perror("fail to hostname");
        strcpy("none", oinfo->hostname);
    }
    else
    {
        bytes = read(fd, buf, sizeof(buf));
        buf[bytes] = '\0';
        strcpy(oinfo->hostname, buf);
    }
    close(fd);


    if ((fd = open("/etc/issue", O_RDONLY)) == -1)
    {
        perror("fail to os");
        strcpy("none", oinfo->os);
    }
    else
    {
        bytes = read(fd, buf, sizeof(buf));
        buf[bytes - 1] = '\0';
        strcpy(oinfo->version, buf);
        pchar = buf;
        tp = oinfo->os;
        while (*pchar != ' ')
            *(tp++) = *(pchar++);
        tp = '\0';
    }
    close(fd);

    if ((fd = open("/proc/version", O_RDONLY)) == -1)
    {
        perror("fail to kernel");
        strcpy("none", oinfo->kernel);
    }
    else
    {
        bytes = read(fd, buf, 50);
        buf[50] = '\0';
        pchar = buf + 14;
        tp = oinfo->kernel;
        while (*pchar != ' ')
            *(tp++) = *(pchar++);
        tp = '\0';
    }
    close(fd);

    strcpy(oinfo->cpu, cpu_info.model_name);

    GetMemoInfo();
    sprintf(oinfo->memory, "%.2fG", memo_info.MemTotal /1024.0 /1024.0);

}

void ShowInfo(GtkWidget *vbox, OUTLINE_INFO oinfo)
{
    char text[50];
    ShowLabel(vbox, " ");

    sprintf(text, "计算机名： %s", oinfo.hostname);
    ShowLabel(vbox, text);

    sprintf(text, "系统名：%s", oinfo.os);
    ShowLabel(vbox, text);

    sprintf(text, "系统版本号：%s", oinfo.version);
    ShowLabel(vbox, text);

    sprintf(text, "内核版本号：%s", oinfo.kernel);
    ShowLabel(vbox, text);

    sprintf(text, "CPU：%s", oinfo.cpu);
    ShowLabel(vbox, text);

    sprintf(text, "安装内存：%s", oinfo.memory);
    ShowLabel(vbox, text);

    time_t t;
    time(&t);
    struct tm *p = gmtime(&t);
    long int num;
    num = GetUptime();
    int hour1 = num/3600, min1 = num%3600/60, sec1 = num%60;
    int hour2 = 8 + p->tm_hour, min2 = p->tm_min, sec2 = p->tm_sec;
    int hour, min, sec;

	if(sec2 < sec1)
	{
	    sec2 += 60;
	    if(min2 == 0)
	    {
		min2 = 59;
		hour2--;
	    }
	    else min2--;
	}
	sec = sec2 - sec1;
	if(min2 < min1)
	{
	    min2 += 60;
	    hour2--;
	}
	min = min2 - min1;
	hour = hour2 - hour1;

    sprintf(text, "系统开始时间：%dh %dm %ds", hour, min, sec);
    ShowLabel(vbox, text);

    ShowLabel(vbox, " ");
}




