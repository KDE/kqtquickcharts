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

#ifndef BARGRAPHCORE_H
#define BARGRAPHCORE_H

#include "chartcore.h"

class BarChartCore : public ChartCore
{
    Q_OBJECT
    Q_PROPERTY(qreal barWidth READ barWidth NOTIFY barWidthChanged)
public:
    explicit BarChartCore(QQuickItem* parent = 0);
    qreal barWidth() const;
    void paint(QPainter* painter);
Q_SIGNALS:
    void barWidthChanged();
};

#endif // BARGRAPHCORE_H
