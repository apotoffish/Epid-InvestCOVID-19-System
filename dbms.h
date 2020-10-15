#ifndef DBMS_H
#define DBMS_H

#pragma once

#include <QSqlDatabase>
#include <QSqlTableModel>
#include "defs.h"

bool initdb();

struct finfo searchDB(struct finfo, int &flag);

bool inPasses(QString dept,QString dest,int type,QString trafficDate);

int insertDB(struct finfo);

bool loginDB(QString id, QString key);

QSqlTableModel* showDB(QString target);

bool addDB(struct finfo, int target);

bool addTrafficDB(QStringList list);

bool delTrafficDB(QStringList list);

bool delNewRiskDB(QString trafficDate);

bool delRiskDB(QString id);

bool addtoRiskDB(QString trafficDate);

#endif // DBMS_H
