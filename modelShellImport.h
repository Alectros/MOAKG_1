#ifndef MODELSHELLIMPORT_H
#define MODELSHELLIMPORT_H

#include <QString>
#include <QFile>
#include <QTextStream>

#include "modelshell.h"

//Структура файла
//количество точек
//точки
//количество ребер
//ребра (нумерация с 1)
//Пример
//4
//0 0 0
//1 0 0
//0 1 1
//0 1 0
//3
//1 2
//2 3
//3 4

bool importModelShellFromFile(const QString &filename, ModelShell &model, QString &errors)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        errors = "File not open";
        return false;
    }
    QTextStream stream(&file);
    int sP, sE;
    stream >> sP;
    model.clear();
    for(int i = 0; i < sP; i++) {
        double x, y, z;
        stream >> x >> y >> z;
        model.addPoint(x / z, y / z);
    }
    stream >> sE;
    for(int i = 0; i < sP; i++) {
        double p1, p2;
        stream >> p1 >> p2;
        model.addEdge(p1 - 1, p2 - 1);
    }
    file.close();
    return true;
}


#endif // MODELSHELLIMPORT_H