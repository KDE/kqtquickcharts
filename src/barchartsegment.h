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

#ifndef BARCHARTSEGMENT_H
#define BARCHARTSEGMENT_H

#include <QQuickItem>

class BarChartCore;

class BarChartSegment : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(BarChartCore* barChartCore READ barChartCore WRITE setBarChartCore NOTIFY barChartCoreChanged)
    Q_PROPERTY(int dimension READ dimension WRITE setDimension NOTIFY dimensionChanged)
    Q_PROPERTY(int row READ row WRITE setRow NOTIFY rowChanged)
    Q_PROPERTY(qreal barHeight READ barHeight NOTIFY barHeightChanged)
    Q_PROPERTY(QString text READ text NOTIFY textChanged)
public:
    explicit BarChartSegment(QQuickItem* parent = nullptr);
    BarChartCore* barChartCore() const;
    void setBarChartCore(BarChartCore* barChartCore);
    int dimension() const;
    void setDimension(int dimension);
    int row() const;
    void setRow(int row);
    qreal barHeight() const;
    QString text() const;
Q_SIGNALS:
    void barChartCoreChanged();
    void dimensionChanged();
    void rowChanged();
    void barHeightChanged();
    void textChanged();
private Q_SLOTS:
    void triggerUpdate();
private:
    bool valid() const;
    BarChartCore* m_barChartCore;
    int m_dimension;
    int m_row;
};

#endif // BARCHARTSEGMENT_H
