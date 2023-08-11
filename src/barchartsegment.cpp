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

#include "barchartsegment.h"

#include <QAbstractTableModel>

#include "dimension.h"
#include "barchartcore.h"

BarChartSegment::BarChartSegment(QQuickItem* parent) :
    QQuickItem(parent),
    m_barChartCore(nullptr),
    m_dimension(-1),
    m_row(-1)
{
    connect(this, &QQuickItem::heightChanged, this, &BarChartSegment::triggerUpdate);
}

BarChartCore* BarChartSegment::barChartCore() const
{
    return m_barChartCore;
}

void BarChartSegment::setBarChartCore(BarChartCore* barChartCore)
{
    if (barChartCore != m_barChartCore)
    {
        if (m_barChartCore)
        {
            m_barChartCore->disconnect(this);
        }

        m_barChartCore = barChartCore;

        if (m_barChartCore)
        {
            connect(m_barChartCore, &ChartCore::updated, this, &BarChartSegment::triggerUpdate);
        }

        triggerUpdate();
        emit barChartCoreChanged();
    }
}

int BarChartSegment::dimension() const
{
    return m_dimension;
}

void BarChartSegment::setDimension(int dimension)
{
    if (dimension != m_dimension)
    {
        m_dimension = dimension;
        triggerUpdate();
        emit dimensionChanged();
    }
}

int BarChartSegment::row() const
{
    return m_row;
}

void BarChartSegment::setRow(int row)
{
    if (row != m_row)
    {
        m_row = row;
        triggerUpdate();
        emit rowChanged();
    }
}

qreal BarChartSegment::barHeight() const
{
    if (!valid())
        return 0.0;

    QAbstractTableModel* model = m_barChartCore->model();
    Dimension* dimension = m_barChartCore->dimensionsList().at(m_dimension);
    const qreal minValue = dimension->minimumValue();
    const qreal maxValue = dimension->maximumValue();
    const int column = dimension->dataColumn();
    const qreal value = model->data(model->index(m_row, column)).toReal();

    return height() * (value - minValue) / (maxValue - minValue);
}

QString BarChartSegment::text() const
{
    if (!m_barChartCore)
        return QString();

    const int role = m_barChartCore->textRole();

    if (role == -1)
        return QString();

    QAbstractTableModel* model = m_barChartCore->model();
    Dimension* dimension = m_barChartCore->dimensionsList().at(m_dimension);
    const int column = dimension->dataColumn();

    return model->data(model->index(m_row, column), role).toString();
}

void BarChartSegment::triggerUpdate()
{
    if (!valid())
        return;
    update();
    emit barHeightChanged();
}

bool BarChartSegment::valid() const
{
    if (!m_barChartCore)
        return false;
    if (m_dimension == -1)
        return false;
    if (m_row == -1)
        return false;
    if (m_row >= m_barChartCore->model()->rowCount())
        return false;
    return true;
}

#include "moc_barchartsegment.cpp"