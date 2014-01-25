/*
 *  Copyright 2014  Sebastian Gottfried <sebastiangottfried@web.de>
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) version 3, or any
 *  later version accepted by the membership of KDE e.V. (or its
 *  successor approved by the membership of KDE e.V.), which shall
 *  act as a proxy defined in Section 6 of version 3 of the license.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 */

#ifndef LINEGRAPHPOINT_H
#define LINEGRAPHPOINT_H

#include <QDeclarativeItem>

class LineGraphCore;
class LineGraphBackgroundPainter;

class LineGraphPoint : public QDeclarativeItem
{
    Q_OBJECT
    Q_PROPERTY(LineGraphCore* lineGraphCore READ lineGraphCore WRITE setLineGraphCore NOTIFY lineGraphCoreChanged)
    Q_PROPERTY(LineGraphBackgroundPainter* backgroundPainter READ backgroundPainter WRITE setBackgroundPainter NOTIFY backgroundPainterChanged)
    Q_PROPERTY(int dimension READ dimension WRITE setDimension NOTIFY dimensionChanged)
    Q_PROPERTY(int row READ row WRITE setRow NOTIFY rowChanged)
    Q_PROPERTY(QString text READ text NOTIFY textChanged)
public:
    explicit LineGraphPoint(QDeclarativeItem* parent = 0);
    LineGraphCore* lineGraphCore() const;
    void setLineGraphCore(LineGraphCore* lineGraphCore);
    LineGraphBackgroundPainter* backgroundPainter() const;
    void setBackgroundPainter(LineGraphBackgroundPainter* backgroundPainter);
    int dimension() const;
    void setDimension(int dimension);
    int row() const;
    void setRow(int row);
    QString text() const;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*);
signals:
    void lineGraphCoreChanged();
    void backgroundPainterChanged();
    void dimensionChanged();
    void rowChanged();
    void textChanged();
    void maxYChanged();
private slots:
    void triggerUpdate();
private:
    void updateGeometry();
    bool valid() const;
    LineGraphCore* m_lineGraphCore;
    LineGraphBackgroundPainter* m_backgroundPainter;
    int m_dimension;
    int m_row;
};

#endif // LINEGRAPHPOINT_H
