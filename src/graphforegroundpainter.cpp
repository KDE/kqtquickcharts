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

#include "graphforegroundpainter.h"

#include <QPainter>

#include "graphcore.h"

GraphForegroundPainter::GraphForegroundPainter(QDeclarativeItem *parent) :
    QDeclarativeItem(parent),
    m_graphCore(0)
{
    setFlag(QGraphicsItem::ItemHasNoContents, false);
}

GraphCore* GraphForegroundPainter::graphCore() const
{
    return m_graphCore;
}

void GraphForegroundPainter::setGraphCore(GraphCore* graphCore)
{
    if (graphCore != m_graphCore)
    {
        if (m_graphCore)
        {
            m_graphCore->disconnect(this);
        }

        m_graphCore = graphCore;

        if (m_graphCore)
        {
            connect(m_graphCore, SIGNAL(updated()), SLOT(triggerUpdate()));
        }

        triggerUpdate();
        emit graphCoreChanged();
    }
}

QColor GraphForegroundPainter::backgroundColor() const
{
    return m_backgroundColor;
}

void GraphForegroundPainter::setBackgroundColor(const QColor& backgroundColor)
{
    if (backgroundColor != m_backgroundColor)
    {
        m_backgroundColor = backgroundColor;
        triggerUpdate();
        emit backgroundColorChanged();
    }
}

void GraphForegroundPainter::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    if (!m_graphCore)
        return;

    const qreal overlapWidth = m_graphCore->pitch() / 2;

    QColor startColor = m_backgroundColor;
    QColor stopColor = startColor;
    stopColor.setAlpha(0);

    QLinearGradient leftFadeOutGradiend(QPointF(0, 0), QPointF(overlapWidth, 0));
    leftFadeOutGradiend.setColorAt(0, startColor);
    leftFadeOutGradiend.setColorAt(1, stopColor);
    painter->fillRect(QRectF(QPointF(0, 0), QPointF(overlapWidth, height())), QBrush(leftFadeOutGradiend));

    QLinearGradient rightFadeOutGradiend(QPointF(width() - overlapWidth , 0), QPointF(width(), 0));
    rightFadeOutGradiend.setColorAt(0, stopColor);
    rightFadeOutGradiend.setColorAt(1, startColor);
    painter->fillRect(QRectF(QPointF(width() - overlapWidth , 0), QPointF(width(), height())), QBrush(rightFadeOutGradiend));

}

void GraphForegroundPainter::triggerUpdate()
{
    if (!m_graphCore)
        return;

    update();
}
