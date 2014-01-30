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

#include "chartplugin.h"

#include <qdeclarative.h>
#include <QAbstractTableModel>

#include "dimension.h"
#include "barchartcore.h"
#include "barchartsegment.h"
#include "linechartcore.h"
#include "linechartbackgroundpainter.h"
#include "linechartpainter.h"
#include "linechartpoint.h"
#include "chartforegroundpainter.h"

void ChartPlugin::registerTypes(const char *uri)
{
    Q_ASSERT(uri == QLatin1String("org.kde.charts"));

    qmlRegisterType<Dimension>(uri, 0, 1, "Dimension");
    qmlRegisterType<ChartCore>(uri, 0, 1, "ChartCore");
    qmlRegisterType<BarChartCore>(uri, 0, 1, "BarChartCore");
    qmlRegisterType<BarChartSegment>(uri, 0, 1, "BarChartSegment");
    qmlRegisterType<LineChartCore>(uri, 0, 1, "LineChartCore");
    qmlRegisterType<LineChartBackgroundPainter>(uri, 0, 1, "LineChartBackgroundPainter");
    qmlRegisterType<LineChartPainter>(uri, 0, 1, "LineChartPainter");
    qmlRegisterType<LineChartPoint>(uri, 0, 1, "LineChartPoint");
    qmlRegisterType<ChartForegroundPainter>(uri, 0, 1, "ChartForegroundPainter");

    qmlRegisterUncreatableType<QAbstractTableModel>(uri, 0, 1, "QAbstractTableModel", "abstract class");
}

Q_EXPORT_PLUGIN2(chartplugin, ChartPlugin)
