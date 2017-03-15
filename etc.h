/**
 * ETC - header
 * Christopher Bero <bigbero@gmail.com>
 */
#ifndef ETC_H
#define ETC_H

#include <QtCore>
#include <QGraphicsItemGroup>
#include <QGraphicsPolygonItem>
#include <QVector>

QString timeStamp();
int get_nextInt(QString input, int * index);
double speedTranslate(int setting_speed);

#endif // ETC_H
