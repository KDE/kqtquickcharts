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

#include "linegraphpoint.h"

#include <QAbstractTableModel>
#include <QPainter>

#include "linegraphcore.h"
#include "dimension.h"
#include "linegraphbackgroundpainter.h"

LineGraphPoint::LineGraphPoint(QDeclarativeItem* parent) :
    QDeclarativeItem(parent),
    m_lineGraphCore(0),
    m_backgroundPainter(0),
    m_dimension(-1),
    m_row(-1)
{
    setFlag(QGraphicsItem::ItemHasNoContents, false);
}

LineGraphCore* LineGraphPoint::lineGraphCore() const
{
    return m_lineGraphCore;
}

void LineGraphPoint::setLineGraphCore(LineGraphCore* lineGraphCore)
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

        triggerUpdate();
        emit lineGraphCoreChanged();
    }
}

LineGraphBackgroundPainter* LineGraphPoint::backgroundPainter() const
{
    return m_backgroundPainter;
}

void LineGraphPoint::setBackgroundPainter(LineGraphBackgroundPainter* backgroundPainter)
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
            connect(m_backgroundPainter, SIGNAL(linePolygonsUpdated()), SLOT(triggerUpdate()));
        }

        triggerUpdate();
        emit backgroundPainterChanged();
    }
}

int LineGraphPoint::dimension() const
{
    return m_dimension;
}

void LineGraphPoint::setDimension(int dimension)
{
    if (dimension != m_dimension)
    {
        m_dimension = dimension;
        triggerUpdate();
        emit dimensionChanged();
    }
}

int LineGraphPoint::row() const
{
    return m_row;
}

void LineGraphPoint::setRow(int row)
{
    if (row != m_row)
    {
        m_row = row;
        triggerUpdate();
        emit rowChanged();
    }
}

QString LineGraphPoint::text() const
{
    const int role = m_lineGraphCore->textRole();

    if (role == -1)
        return QString();

    QAbstractTableModel* model = m_lineGraphCore->model();
    Dimension* dimension = m_lineGraphCore->dimensionsList().at(m_dimension);
    const int column = dimension->dataColumn();

    return model->data(model->index(m_row, column), role).toString();
}

void LineGraphPoint::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    if (!valid())
        return;

    Dimension* dimension = m_lineGraphCore->dimensionsList().at(m_dimension);

    painter->setRenderHints(QPainter::Antialiasing, true);
    painter->setBrush(QBrush(dimension->color()));
    painter->setPen(Qt::NoPen);
    const qreal radius = m_lineGraphCore->pointRadius();
    painter->drawEllipse(QPointF(radius, radius), radius, radius);
}

void LineGraphPoint::triggerUpdate()
{
    if (!valid())
        return;
    updateGeometry();
    update();
}

void LineGraphPoint::updateGeometry()
{
    const qreal radius = m_lineGraphCore->pointRadius();
    setWidth(2 * radius);
    setHeight(2 * radius);
    QPointF center = m_backgroundPainter->linePolygons().at(m_dimension).at(m_row);

    setPos(center - QPointF(radius, radius));
}

bool LineGraphPoint::valid() const
{
    if (!m_lineGraphCore || !m_backgroundPainter || m_row == -1 || m_dimension == -1)
        return false;
    if (m_dimension >= m_backgroundPainter->linePolygons().count())
        return false;
    if (m_row >= m_backgroundPainter->linePolygons().at(m_dimension).count())
        return false;
    return true;
}
