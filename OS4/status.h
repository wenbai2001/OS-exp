/***********************************************************************
 * @file status.h
     STATUS
 * @brief   header file
 *
 * @Copyright (C)  2018  YangJunhuai. all right reserved
***********************************************************************/
#ifndef __STATUS_h__
#define __STATUS_h__

#include "MainWindow.h"
#include "cpu.h"
#include "memory.h"

void ShowStatus(GtkWidget* vbox);
gint GetTime(gpointer label);
long int GetUptime(void);

#endif // __STATUS_h__