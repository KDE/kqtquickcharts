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

#include "linechartpoint.h"

#include <QAbstractTableModel>
#include <QPainter>

#include "linechartcore.h"
#include "dimension.h"
#include "linechartbackgroundpainter.h"

LineChartPoint::LineChartPoint(QQuickItem* parent) :
    QQuickPaintedItem(parent),
    m_lineChartCore(nullptr),
    m_backgroundPainter(nullptr),
    m_dimension(-1),
    m_row(-1)
{
    setFlag(QQuickItem::ItemHasContents, true);
}

LineChartCore* LineChartPoint::lineChartCore() const
{
    return m_lineChartCore;
}

void LineChartPoint::setLineChartCore(LineChartCore* lineChartCore)
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
            connect(m_lineChartCore, &ChartCore::updated, this, &LineChartPoint::triggerUpdate);
        }

        triggerUpdate();
        emit lineChartCoreChanged();
    }
}

LineChartBackgroundPainter* LineChartPoint::backgroundPainter() const
{
    return m_backgroundPainter;
}

void LineChartPoint::setBackgroundPainter(LineChartBackgroundPainter* backgroundPainter)
{
    if (backgroundPainter != m_backgroundPainter)
    {
        if (m_backgroundPainter)
        {
            m_backgroundPainter->disconnect(this);
        }

        m_backgroundPainter = backgroundPainter;

        if (m_backgroundPainter)
        {
            connect(m_backgroundPainter, &LineChartBackgroundPainter::linePolygonsUpdated, this, &LineChartPoint::triggerUpdate);
        }

        triggerUpdate();
        emit backgroundPainterChanged();
    }
}

int LineChartPoint::dimension() const
{
    return m_dimension;
}

void LineChartPoint::setDimension(int dimension)
{
    if (dimension != m_dimension)
    {
        m_dimension = dimension;
        triggerUpdate();
        emit dimensionChanged();
    }
}

int LineChartPoint::row() const
{
    return m_row;
}

void LineChartPoint::setRow(int row)
{
    if (row != m_row)
    {
        m_row = row;
        triggerUpdate();
        emit rowChanged();
    }
}

QString LineChartPoint::text() const
{
    if (!m_lineChartCore)
        return QString();

    const int role = m_lineChartCore->textRole();

    if (role == -1)
        return QString();

    QAbstractTableModel* model = m_lineChartCore->model();
    Dimension* dimension = m_lineChartCore->dimensionsList().at(m_dimension);
    const int column = dimension->dataColumn();

    return model->data(model->index(m_row, column), role).toString();
}

void LineChartPoint::paint(QPainter* painter)
{
    if (!valid())
        return;

    Dimension* dimension = m_lineChartCore->dimensionsList().at(m_dimension);

    painter->setRenderHints(QPainter::Antialiasing, true);
    painter->setBrush(QBrush(dimension->color()));
    painter->setPen(Qt::NoPen);
    const qreal radius = m_lineChartCore->pointRadius();
    painter->drawEllipse(QPointF(radius, radius), radius, radius);
}

void LineChartPoint::triggerUpdate()
{
    if (!valid())
        return;
    updateGeometry();
    update();
}

void LineChartPoint::updateGeometry()
{
    const qreal radius = m_lineChartCore->pointRadius();
    setWidth(2 * radius);
    setHeight(2 * radius);
    QPointF center = m_backgroundPainter->linePolygons().at(m_dimension).at(m_row);

    setX(center.x() - radius);
    setY(center.y() - radius);
}

bool LineChartPoint::valid() const
{
    if (!m_lineChartCore || !m_backgroundPainter || m_row == -1 || m_dimension == -1)
        return false;
    if (m_dimension >= m_backgroundPainter->linePolygons().count())
        return false;
    if (m_row >= m_backgroundPainter->linePolygons().at(m_dimension).count())
        return false;
    return true;
}
