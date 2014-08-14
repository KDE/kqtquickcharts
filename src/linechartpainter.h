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
#ifndef LINEGRAPHPAINTER_H
#define LINEGRAPHPAINTER_H

#include <QQuickPaintedItem>

class LineChartCore;
class LineChartBackgroundPainter;

class LineChartPainter : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(LineChartCore* lineChartCore READ lineChartCore WRITE setLineChartCore NOTIFY lineChartCoreChanged)
    Q_PROPERTY(LineChartBackgroundPainter* backgroundPainter READ backgroundPainter WRITE setBackgroundPainter NOTIFY backgroundPainterChanged)
    Q_PROPERTY(int dimension READ dimension WRITE setDimension NOTIFY dimensionChanged)
public:
    explicit LineChartPainter(QQuickItem* parent = 0);
    LineChartCore* lineChartCore() const;
    void setLineChartCore(LineChartCore* lineChartCore);
    LineChartBackgroundPainter* backgroundPainter() const;
    void setBackgroundPainter(LineChartBackgroundPainter* backgroundPainter);
    int dimension() const;
    void setDimension(int dimension);
    void paint(QPainter* painter);
Q_SIGNALS:
    void lineChartCoreChanged();
    void backgroundPainterChanged();
    void dimensionChanged();
private Q_SLOTS:
    void triggerUpdate();
private:
    void updateWidth();
    LineChartCore* m_lineChartCore;
    LineChartBackgroundPainter* m_backgroundPainter;
    int m_dimension;
};

#endif // LINEGRAPHPAINTER_H
