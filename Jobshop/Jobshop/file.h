/**
 * file and io
 *
 * file.h
 * by Hzy
 * 2018-5-12
 */
#pragma once
#ifndef _FILE_H_
#define _FILE_H_

#include "base.h"

/* contemp input func */
void input(All_job * job);
void read_from_file(All_job * job);
/* contemp output func */
void output(int * elite, int machine, int job, int all_operation);
void output_to_file(int * elite, int machine, int job, int all_operation);
#endif // !_FILE_H_