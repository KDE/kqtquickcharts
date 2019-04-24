/*
 *  Copyright 2015  Jesper Hellesø Hansen <jesperhh@gmail.com>
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
#include "xychartpainter.h"

#include <QAbstractTableModel>
#include <QPainter>

#include "xychartcore.h"
#include "dimension.h"
#include "xychartbackgroundpainter.h"

XYChartPainter::XYChartPainter(QQuickItem* parent) :
    QQuickPaintedItem(parent),
    m_xyChartCore(nullptr),
    m_backgroundPainter(nullptr),
    m_dimension(-1)
{
    setFlag(QQuickItem::ItemHasContents, true);
}

XYChartCore* XYChartPainter::xyChartCore() const
{
    return m_xyChartCore;
}

void XYChartPainter::setXYChartCore(XYChartCore* lineChartCore)
{
    if (lineChartCore != m_xyChartCore)
    {
        if (m_xyChartCore)
        {
            m_xyChartCore->disconnect(this);
        }

        m_xyChartCore = lineChartCore;

        if (m_xyChartCore)
        {
            connect(m_xyChartCore, &ChartCore::updated, this, &XYChartPainter::triggerUpdate);
        }

        update();
        emit xyChartCoreChanged();
    }
}

XYChartBackgroundPainter* XYChartPainter::backgroundPainter() const
{
    return m_backgroundPainter;
}

void XYChartPainter::setBackgroundPainter(XYChartBackgroundPainter* backgroundPainter)
{
    if (backgroundPainter != m_backgroundPainter)
    {
        m_backgroundPainter = backgroundPainter;
        triggerUpdate();
        emit backgroundPainterChanged();
    }
}

int XYChartPainter::dimension() const
{
    return m_dimension;
}

void XYChartPainter::setDimension(int dimension)
{
    if (dimension != m_dimension)
    {
        m_dimension = dimension;
        triggerUpdate();
        emit dimensionChanged();
    }
}

void XYChartPainter::paint(QPainter* painter)
{
    if (!m_xyChartCore || !m_backgroundPainter || m_dimension == -1)
        return;

    painter->setRenderHints(QPainter::Antialiasing, true);

    Dimension* dimension = m_xyChartCore->dimensionsList().at(m_dimension);

    QPolygonF line = m_backgroundPainter->linePolygons().at(m_dimension);

    switch (dimension->lineStyle())
    {
    case Dimension::LineStyleSolid:
        painter->setPen(QPen(QBrush(dimension->color()), m_xyChartCore->lineWidth()));
        painter->drawPolyline(line);
        break;
    case Dimension::LineStyleDash:
        painter->setPen(QPen(QBrush(dimension->color()), m_xyChartCore->lineWidth(), Qt::DashLine));
        painter->drawPolyline(line);
        break;
    case Dimension::LineStyleNone:
        // do nothing
        break;
    }
}

void XYChartPainter::triggerUpdate()
{
    if (!m_xyChartCore || !m_backgroundPainter || m_dimension == -1)
        return;

    update();
}
