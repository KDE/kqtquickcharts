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
#include "linegraphpainter.h"

#include <QAbstractTableModel>
#include <QPainter>

#include "linegraphcore.h"
#include "dimension.h"
#include "linegraphbackgroundpainter.h"

#include <KDebug>

LineGraphPainter::LineGraphPainter(QDeclarativeItem* parent) :
    QDeclarativeItem(parent),
    m_lineGraphCore(0),
    m_backgroundPainter(0),
    m_dimension(-1)
{
    setFlag(QGraphicsItem::ItemHasNoContents, false);
}

LineGraphCore* LineGraphPainter::lineGraphCore() const
{
    return m_lineGraphCore;
}

void LineGraphPainter::setLineGraphCore(LineGraphCore* lineGraphCore)
{
    if (lineGraphCore != m_lineGraphCore)
    {
        if (m_lineGraphCore)
        {
            m_lineGraphCore->disconnect(this);
        }

        m_lineGraphCore = lineGraphCore;

        if (m_lineGraphCore)
        {
            connect(m_lineGraphCore, SIGNAL(updated()), SLOT(triggerUpdate()));
        }

        update();
        emit lineGraphCoreChanged();
    }
}

LineGraphBackgroundPainter* LineGraphPainter::backgroundPainter() const
{
    return m_backgroundPainter;
}

void LineGraphPainter::setBackgroundPainter(LineGraphBackgroundPainter* backgroundPainter)
{
    if (backgroundPainter != m_backgroundPainter)
    {
        m_backgroundPainter = backgroundPainter;
        triggerUpdate();
        emit backgroundPainterChanged();
    }
}

int LineGraphPainter::dimension() const
{
    return m_dimension;
}

void LineGraphPainter::setDimension(int dimension)
{
    if (dimension != m_dimension)
    {
        m_dimension = dimension;
        triggerUpdate();
        emit dimensionChanged();
    }
}

void LineGraphPainter::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    if (!m_lineGraphCore || !m_backgroundPainter || m_dimension == -1)
        return;

    painter->setRenderHints(QPainter::Antialiasing, true);

    Dimension* dimension = m_lineGraphCore->dimensionsList().at(m_dimension);

    QPolygonF line = m_backgroundPainter->linePolygons().at(m_dimension);

    painter->setPen(QPen(QBrush(dimension->color()), 3));
    painter->drawPolyline(line);
}

void LineGraphPainter::triggerUpdate()
{
    if (!m_lineGraphCore || !m_backgroundPainter || m_dimension == -1)
        return;

    updateWidth();
    update();
}

void LineGraphPainter::updateWidth()
{
    setWidth(backgroundPainter()->width());
}
