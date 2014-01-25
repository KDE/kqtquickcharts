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

#include "bargraphsegment.h"

#include <QAbstractTableModel>

#include "dimension.h"
#include "bargraphcore.h"

#include <KDebug>

BarGraphSegment::BarGraphSegment(QDeclarativeItem* parent) :
    QDeclarativeItem(parent),
    m_barGraphCore(0),
    m_dimension(-1),
    m_row(-1)
{
    connect(this, SIGNAL(heightChanged()), SLOT(triggerUpdate()));
}

BarGraphCore* BarGraphSegment::barGraphCore() const
{
    return m_barGraphCore;
}

void BarGraphSegment::setBarGraphCore(BarGraphCore* barGraphCore)
{
    if (barGraphCore != m_barGraphCore)
    {
        if (m_barGraphCore)
        {
            m_barGraphCore->disconnect(this);
        }

        m_barGraphCore = barGraphCore;

        if (m_barGraphCore)
        {
            connect(m_barGraphCore, SIGNAL(updated()), SLOT(triggerUpdate()));
        }

        triggerUpdate();
        emit barGraphCoreChanged();
    }
}

int BarGraphSegment::dimension() const
{
    return m_dimension;
}

void BarGraphSegment::setDimension(int dimension)
{
    if (dimension != m_dimension)
    {
        m_dimension = dimension;
        triggerUpdate();
        emit dimensionChanged();
    }
}

int BarGraphSegment::row() const
{
    return m_row;
}

void BarGraphSegment::setRow(int row)
{
    if (row != m_row)
    {
        m_row = row;
        triggerUpdate();
        emit rowChanged();
    }
}

qreal BarGraphSegment::barHeight() const
{
    if (!valid())
        return 0.0;

    QAbstractTableModel* model = m_barGraphCore->model();
    Dimension* dimension = m_barGraphCore->dimensionsList().at(m_dimension);
    const qreal minValue = dimension->minimumValue();
    const qreal maxValue = dimension->maximumValue();
    const int column = dimension->dataColumn();
    const qreal value = model->data(model->index(m_row, column)).toReal();

    return height() * (value - minValue) / (maxValue - minValue);
}

QString BarGraphSegment::text() const
{
    const int role = m_barGraphCore->textRole();

    if (role == -1)
        return QString();

    QAbstractTableModel* model = m_barGraphCore->model();
    Dimension* dimension = m_barGraphCore->dimensionsList().at(m_dimension);
    const int column = dimension->dataColumn();

    return model->data(model->index(m_row, column), role).toString();
}

void BarGraphSegment::triggerUpdate()
{
    if (!valid())
        return;
    update();
    emit barHeightChanged();
}

bool BarGraphSegment::valid() const
{
    if (!m_barGraphCore)
        return false;
    if (m_dimension == -1)
        return false;
    if (m_row == -1)
        return false;
    if (m_row >= m_barGraphCore->model()->rowCount())
        return false;
    return true;
}
