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

#include "graphplugin.h"

#include <qdeclarative.h>
#include <QAbstractTableModel>

#include "dimension.h"
#include "bargraphcore.h"
#include "bargraphsegment.h"
#include "linegraphcore.h"
#include "linegraphbackgroundpainter.h"
#include "linegraphpainter.h"
#include "linegraphpoint.h"
#include "graphforegroundpainter.h"

void GraphPlugin::registerTypes(const char *uri)
{
    Q_ASSERT(uri == QLatin1String("org.kde.graphs"));

    qmlRegisterType<Dimension>(uri, 0, 1, "Dimension");
    qmlRegisterType<GraphCore>(uri, 0, 1, "GraphCore");
    qmlRegisterType<BarGraphCore>(uri, 0, 1, "BarGraphCore");
    qmlRegisterType<BarGraphSegment>(uri, 0, 1, "BarGraphSegment");
    qmlRegisterType<LineGraphCore>(uri, 0, 1, "LineGraphCore");
    qmlRegisterType<LineGraphBackgroundPainter>(uri, 0, 1, "LineGraphBackgroundPainter");
    qmlRegisterType<LineGraphPainter>(uri, 0, 1, "LineGraphPainter");
    qmlRegisterType<LineGraphPoint>(uri, 0, 1, "LineGraphPoint");
    qmlRegisterType<GraphForegroundPainter>(uri, 0, 1, "GraphForegroundPainter");

    qmlRegisterUncreatableType<QAbstractTableModel>(uri, 0, 1, "QAbstractTableModel", "abstract class");
}

Q_EXPORT_PLUGIN2(graphplugin, GraphPlugin)
