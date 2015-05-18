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

#include <QQmlEngine>
#include <QAbstractTableModel>

#include "barchartcore.h"
#include "barchartsegment.h"
#include "chartforegroundpainter.h"
#include "chartcore.h"
#include "chartmodel.h"
#include "dimension.h"
#include "linechartcore.h"
#include "linechartbackgroundpainter.h"
#include "linechartpainter.h"
#include "linechartpoint.h"
#include "xychartcore.h"
#include "xychartbackgroundpainter.h"
#include "xychartpainter.h"
#include "xychartpoint.h"
#include "record.h"

void ChartPlugin::registerTypes(const char *uri)
{
    Q_ASSERT(uri == QLatin1String("org.kde.charts"));

    qmlRegisterType<Dimension>(uri, 0, 1, "Dimension");
    qmlRegisterType<BarChartCore>(uri, 0, 1, "BarChartCore");
    qmlRegisterType<BarChartSegment>(uri, 0, 1, "BarChartSegment");
    qmlRegisterType<ChartCore>(uri, 0, 1, "ChartCore");
    qmlRegisterType<ChartForegroundPainter>(uri, 0, 1, "ChartForegroundPainter");
    qmlRegisterType<LineChartCore>(uri, 0, 1, "LineChartCore");
    qmlRegisterType<LineChartBackgroundPainter>(uri, 0, 1, "LineChartBackgroundPainter");
    qmlRegisterType<LineChartPainter>(uri, 0, 1, "LineChartPainter");
    qmlRegisterType<LineChartPoint>(uri, 0, 1, "LineChartPoint");
    qmlRegisterType<XYChartCore>(uri, 0, 1, "XYChartCore");
    qmlRegisterType<XYChartBackgroundPainter>(uri, 0, 1, "XYChartBackgroundPainter");
    qmlRegisterType<XYChartPainter>(uri, 0, 1, "XYChartPainter");
    qmlRegisterType<XYChartPoint>(uri, 0, 1, "XYChartPoint");
    qmlRegisterType<ChartModel>(uri, 0, 1, "ChartModel");
    qmlRegisterType<Record>(uri, 0, 1, "Record");

    qmlRegisterUncreatableType<QAbstractTableModel>(uri, 0, 1, "QAbstractTableModel", "abstract class");
}
