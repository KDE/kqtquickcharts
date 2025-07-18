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

#include "chartforegroundpainter.h"

#include <QPainter>

#include "chartcore.h"

ChartForegroundPainter::ChartForegroundPainter(QQuickItem *parent) :
    QQuickPaintedItem(parent),
    m_chartCore(nullptr)
{
    setFlag(QQuickItem::ItemHasContents, true);
}

ChartCore* ChartForegroundPainter::chartCore() const
{
    return m_chartCore;
}

void ChartForegroundPainter::setChartCore(ChartCore* chartCore)
{
    if (chartCore != m_chartCore)
    {
        if (m_chartCore)
        {
            m_chartCore->disconnect(this);
        }

        m_chartCore = chartCore;

        if (m_chartCore)
        {
            connect(m_chartCore, &ChartCore::updated, this, &ChartForegroundPainter::triggerUpdate);
        }

        triggerUpdate();
        Q_EMIT chartCoreChanged();
    }
}

QColor ChartForegroundPainter::backgroundColor() const
{
    return m_backgroundColor;
}

void ChartForegroundPainter::setBackgroundColor(const QColor& backgroundColor)
{
    if (backgroundColor != m_backgroundColor)
    {
        m_backgroundColor = backgroundColor;
        triggerUpdate();
        Q_EMIT backgroundColorChanged();
    }
}

void ChartForegroundPainter::paint(QPainter* painter)
{
    if (!m_chartCore)
        return;

    const qreal overlapWidth = m_chartCore->pitch() / 2;

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

void ChartForegroundPainter::triggerUpdate()
{
    if (!m_chartCore)
        return;

    update();
}

#include "moc_chartforegroundpainter.cpp"
