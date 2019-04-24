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

#include "xychartpoint.h"

#include <QAbstractTableModel>
#include <QPainter>

#include "xychartcore.h"
#include "dimension.h"
#include "xychartbackgroundpainter.h"

XYChartPoint::XYChartPoint(QQuickItem* parent) :
    QQuickPaintedItem(parent),
    m_xyChartCore(nullptr),
    m_backgroundPainter(nullptr),
    m_dimension(-1),
    m_row(-1)
{
    setFlag(QQuickItem::ItemHasContents, true);
}

XYChartCore* XYChartPoint::xyChartCore() const
{
    return m_xyChartCore;
}

void XYChartPoint::setXYChartCore(XYChartCore* xyChartCore)
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
            connect(m_xyChartCore, &ChartCore::updated, this, &XYChartPoint::triggerUpdate);
        }

        triggerUpdate();
        emit xyChartCoreChanged();
    }
}

XYChartBackgroundPainter* XYChartPoint::backgroundPainter() const
{
    return m_backgroundPainter;
}

void XYChartPoint::setBackgroundPainter(XYChartBackgroundPainter* backgroundPainter)
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
            connect(m_backgroundPainter, &XYChartBackgroundPainter::linePolygonsUpdated, this, &XYChartPoint::triggerUpdate);
        }

        triggerUpdate();
        emit backgroundPainterChanged();
    }
}

int XYChartPoint::dimension() const
{
    return m_dimension;
}

void XYChartPoint::setDimension(int dimension)
{
    if (dimension != m_dimension)
    {
        m_dimension = dimension;
        triggerUpdate();
        emit dimensionChanged();
    }
}

int XYChartPoint::row() const
{
    return m_row;
}

void XYChartPoint::setRow(int row)
{
    if (row != m_row)
    {
        m_row = row;
        triggerUpdate();
        emit rowChanged();
    }
}

QString XYChartPoint::text() const
{
    if (!m_xyChartCore)
        return QString();

    const int role = m_xyChartCore->textRole();

    if (role == -1)
        return QString();

    QAbstractTableModel* model = m_xyChartCore->model();
    Dimension* dimension = m_xyChartCore->dimensionsList().at(m_dimension);
    const int column = dimension->dataColumn();

    return model->data(model->index(m_row, column), role).toString();
}

void XYChartPoint::paint(QPainter* painter)
{
    if (!valid())
        return;

    const Dimension* dimension = m_xyChartCore->dimensionsList().at(m_dimension);
    const qreal radius = m_xyChartCore->pointRadius();
    painter->setRenderHints(QPainter::Antialiasing, true);


    switch (dimension->markerStyle())
    {
    case Dimension::MarkerStyleNone:
        // Do nothing
        break;
    case Dimension::MarkerStyleRound:
        painter->setBrush(QBrush(dimension->color()));
        painter->setPen(Qt::NoPen);
        painter->drawEllipse(QPointF(radius, radius), radius, radius);
        break;
    case Dimension::MarkerStyleCross:
        painter->setBrush(Qt::NoBrush);
        QPen pen(dimension->color());
        pen.setWidthF(m_xyChartCore->lineWidth());
        painter->setPen(pen);
        painter->drawLine(0.0, 0.0, radius * 2.0, radius * 2.0);
        painter->drawLine(0.0, radius * 2.0, radius * 2.0, 0.0);
        break;
    }
}

void XYChartPoint::triggerUpdate()
{
    if (!valid())
        return;
    updateGeometry();
    update();
}

void XYChartPoint::updateGeometry()
{
    const qreal radius = m_xyChartCore->pointRadius();
    setWidth(2 * radius);
    setHeight(2 * radius);
    QPointF center = m_backgroundPainter->linePolygons().at(m_dimension).at(m_row);

    setX(center.x() - radius);
    setY(center.y() - radius);
}

bool XYChartPoint::valid() const
{
    if (!m_xyChartCore || !m_backgroundPainter || m_row == -1 || m_dimension == -1)
        return false;
    if (m_xyChartCore->dimensionsList().at(m_dimension)->markerStyle() == Dimension::MarkerStyleNone)
        return false;
    if (m_dimension >= m_backgroundPainter->linePolygons().count())
        return false;
    if (m_row >= m_backgroundPainter->linePolygons().at(m_dimension).count())
        return false;
    return true;
}
