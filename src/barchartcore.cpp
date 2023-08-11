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

#include "barchartcore.h"

BarChartCore::BarChartCore(QQuickItem* parent) :
    ChartCore(parent)
{
    connect(this, &ChartCore::pitchChanged, this, &BarChartCore::barWidthChanged);
}

qreal BarChartCore::barWidth() const
{
    return qRound(pitch() / (dimensionsList().length() + 1));
}

void BarChartCore::paint(QPainter* painter)
{
    paintAxisAndLines(painter, 0.0);
}

#include "moc_barchartcore.cpp"