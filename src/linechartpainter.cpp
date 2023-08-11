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
#include "linechartpainter.h"

#include <QAbstractTableModel>
#include <QPainter>

#include "linechartcore.h"
#include "dimension.h"
#include "linechartbackgroundpainter.h"

LineChartPainter::LineChartPainter(QQuickItem* parent) :
    QQuickPaintedItem(parent),
    m_lineChartCore(nullptr),
    m_backgroundPainter(nullptr),
    m_dimension(-1)
{
    setFlag(QQuickItem::ItemHasContents, true);
}

LineChartCore* LineChartPainter::lineChartCore() const
{
    return m_lineChartCore;
}

void LineChartPainter::setLineChartCore(LineChartCore* lineChartCore)
{
    if (lineChartCore != m_lineChartCore)
    {
        if (m_lineChartCore)
        {
            m_lineChartCore->disconnect(this);
        }

        m_lineChartCore = lineChartCore;

        if (m_lineChartCore)
        {
            connect(m_lineChartCore, &ChartCore::updated, this, &LineChartPainter::triggerUpdate);
        }

        update();
        emit lineChartCoreChanged();
    }
}

LineChartBackgroundPainter* LineChartPainter::backgroundPainter() const
{
    return m_backgroundPainter;
}

void LineChartPainter::setBackgroundPainter(LineChartBackgroundPainter* backgroundPainter)
{
    if (backgroundPainter != m_backgroundPainter)
    {
        m_backgroundPainter = backgroundPainter;
        triggerUpdate();
        emit backgroundPainterChanged();
    }
}

int LineChartPainter::dimension() const
{
    return m_dimension;
}

void LineChartPainter::setDimension(int dimension)
{
    if (dimension != m_dimension)
    {
        m_dimension = dimension;
        triggerUpdate();
        emit dimensionChanged();
    }
}

void LineChartPainter::paint(QPainter* painter)
{
    if (!m_lineChartCore || !m_backgroundPainter || m_dimension == -1)
        return;

    painter->setRenderHints(QPainter::Antialiasing, true);

    Dimension* dimension = m_lineChartCore->dimensionsList().at(m_dimension);

    QPolygonF line = m_backgroundPainter->linePolygons().at(m_dimension);

    painter->setPen(QPen(QBrush(dimension->color()), 3));
    painter->drawPolyline(line);
}

void LineChartPainter::triggerUpdate()
{
    if (!m_lineChartCore || !m_backgroundPainter || m_dimension == -1)
        return;

    updateWidth();
    update();
}

void LineChartPainter::updateWidth()
{
    setWidth(backgroundPainter()->width());
}

#include "moc_linechartpainter.cpp"