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

#include "xychartbackgroundpainter.h"

#include <QAbstractTableModel>
#include <QPainter>

#include "xychartcore.h"
#include "dimension.h"

XYChartBackgroundPainter::XYChartBackgroundPainter(QQuickItem* parent) :
    QQuickPaintedItem(parent),
    m_xyChartCore(nullptr)
{
    setFlag(QQuickItem::ItemHasContents, true);

    connect(this, &QQuickItem::widthChanged, this, &XYChartBackgroundPainter::triggerUpdate);
    connect(this, &QQuickItem::heightChanged, this, &XYChartBackgroundPainter::triggerUpdate);
}

XYChartCore* XYChartBackgroundPainter::xyChartCore() const
{
    return m_xyChartCore;
}

void XYChartBackgroundPainter::setXYChartCore(XYChartCore* xyChartCore)
{
    if (xyChartCore != m_xyChartCore)
    {
        if (m_xyChartCore)
        {
            m_xyChartCore->disconnect(this);
        }

        m_xyChartCore = xyChartCore;

        if (m_xyChartCore)
        {
            connect(m_xyChartCore, &ChartCore::updated, this, &XYChartBackgroundPainter::triggerUpdate);
        }

        update();
        emit xyChartCoreChanged();
    }
}

const QList<QPolygonF>& XYChartBackgroundPainter::linePolygons() const
{
    return m_linePolygons;
}

void XYChartBackgroundPainter::paint(QPainter* painter)
{
    Q_UNUSED(painter);
}

void XYChartBackgroundPainter::triggerUpdate()
{
    if (!m_xyChartCore->model())
        return;

    updateLinePolygons();
    update();
}

void XYChartBackgroundPainter::updateLinePolygons()
{
    m_linePolygons.clear();

    Dimension* xAxis = m_xyChartCore->xAxis();
    QList<Dimension*> dimensions = m_xyChartCore->dimensionsList();
    QAbstractTableModel* model = m_xyChartCore->model();

    const int xAxisColumn = xAxis->dataColumn();

    foreach(Dimension* dimension, dimensions)
    {
        const int column = dimension->dataColumn();
        QPolygonF line;
        for (int row = 0; row < model->rowCount(); row++)
        {
            const qreal key = model->data(model->index(row, xAxisColumn)).toReal();
            const qreal value = model->data(model->index(row, column)).toReal();
            // Skip "NULL" values
            if (qIsNaN(value))
                continue;

            line << m_xyChartCore->translatePoint(QPointF(key, value));
        }

        m_linePolygons << line;
    }

    emit linePolygonsUpdated();
}

#include "moc_xychartbackgroundpainter.cpp"