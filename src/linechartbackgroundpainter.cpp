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

#include "linechartbackgroundpainter.h"

#include <QAbstractTableModel>
#include <QPainter>

#include "linechartcore.h"
#include "dimension.h"

LineChartBackgroundPainter::LineChartBackgroundPainter(QQuickItem* parent) :
    QQuickPaintedItem(parent),
    m_lineChartCore(nullptr)
{
    setFlag(QQuickItem::ItemHasContents, true);

    connect(this, &QQuickItem::heightChanged, this, &LineChartBackgroundPainter::triggerUpdate);
}

LineChartCore* LineChartBackgroundPainter::lineChartCore() const
{
    return m_lineChartCore;
}

void LineChartBackgroundPainter::setLineChartCore(LineChartCore* lineChartCore)
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
            connect(m_lineChartCore, &ChartCore::updated, this, &LineChartBackgroundPainter::triggerUpdate);
        }

        update();
        emit lineChartCoreChanged();
    }
}

const QList<QPolygonF>& LineChartBackgroundPainter::linePolygons() const
{
    return m_linePolygons;
}

void LineChartBackgroundPainter::paint(QPainter* painter)
{
    if (m_lineChartCore->model()->rowCount() == 0)
        return;

    QList<Dimension*> dimensions = m_lineChartCore->dimensionsList();
    const qreal radius = m_lineChartCore->pointRadius();
    const qreal maxY = height();

    for (int i = 0; i < dimensions.length(); i++)
    {

        QPolygonF line = m_linePolygons.at(i);

        line << QPointF(line.last().x(), maxY - radius);
        line << QPointF(line.first().x(), maxY - radius);

        QColor bgColor = dimensions.at(i)->color();
        bgColor.setAlphaF(0.4);
        painter->setBrush(bgColor);
        painter->setPen(Qt::NoPen);

        painter->drawPolygon(line);
    }
}

void LineChartBackgroundPainter::triggerUpdate()
{
    if (!m_lineChartCore->model())
        return;

    updateLinePolygons();
    updateWidth();
    update();
}

void LineChartBackgroundPainter::updateWidth()
{
    QAbstractTableModel* model = m_lineChartCore->model();

    if (!model)
    {
        setWidth(0);
        return;
    }

    setWidth(model->rowCount() * m_lineChartCore->pitch());
}

void LineChartBackgroundPainter::updateLinePolygons()
{
    m_linePolygons.clear();

    const QList<Dimension*> dimensions = m_lineChartCore->dimensionsList();
    QAbstractTableModel* model = m_lineChartCore->model();
    const qreal pitch = m_lineChartCore->pitch();
    const qreal radius = m_lineChartCore->pointRadius();

    for (Dimension* dimension : dimensions)
    {
        const int column = dimension->dataColumn();
        const qreal minValue = dimension->minimumValue();
        const qreal maxValue = dimension->maximumValue();
        const qreal maxY = height();

        QPolygonF line;

        for (int row = 0; row < model->rowCount(); row++)
        {
            const qreal value = model->data(model->index(row, column)).toReal();
            if (qIsNaN(value))
                continue;

            const qreal x = (qreal(row) + 0.5) * pitch;
            const qreal y =  maxY - ((maxY - 2 * radius) * (value - minValue) / (maxValue - minValue)) - radius;
            line << QPointF(x, y);
        }

        m_linePolygons << line;
    }

    emit linePolygonsUpdated();
}

#include "moc_linechartbackgroundpainter.cpp"

