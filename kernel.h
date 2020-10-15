#ifndef KERNEL_H
#define KERNEL_H

#pragma once

#include "defs.h"

int riskCompute(struct finfo rfinfo,struct finfo sfinfo);

bool isInterval(struct finfo rfinfo,struct finfo sfinfo);

int riskLevel(int type,int r,int s,int &risk);
#endif // KERNEL_H
