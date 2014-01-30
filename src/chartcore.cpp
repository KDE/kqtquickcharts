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

#include "chartcore.h"

#include <QAbstractTableModel>
#include <QPainter>

ChartCore::ChartCore(QDeclarativeItem *parent) :
    QDeclarativeItem(parent),
    m_model(0),
    m_pitch(50.0),
    m_textRole(-1)
{
    setFlag(QGraphicsItem::ItemHasNoContents, false);
}

QAbstractTableModel* ChartCore::model() const
{
    return m_model;
}

void ChartCore::setModel(QAbstractTableModel* model)
{
    if (model != m_model)
    {
        if (m_model)
        {
            m_model->disconnect(this);
        }

        m_model = model;

        if (m_model)
        {
            connect(m_model, SIGNAL(modelReset()), SLOT(triggerUpdate()));
            connect(m_model, SIGNAL(rowsInserted(QModelIndex,int,int)), SLOT(triggerUpdate()));
            connect(m_model, SIGNAL(rowsRemoved(QModelIndex,int,int)), SLOT(triggerUpdate()));
            connect(m_model, SIGNAL(rowsMoved(QModelIndex,int,int,QModelIndex,int)), SLOT(triggerUpdate()));
            connect(m_model, SIGNAL(layoutChanged()), SLOT(triggerUpdate()));
            connect(m_model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), SLOT(triggerUpdate()));
        }

        triggerUpdate();
        emit modelChanged();
    }
}

QDeclarativeListProperty<Dimension> ChartCore::dimensions() {
    return QDeclarativeListProperty<Dimension>(this, 0, &ChartCore::appendDimension, &ChartCore::countDimensions, &ChartCore::dimensionAt, &ChartCore::clearDimensions);
}

QList<Dimension*> ChartCore::dimensionsList() const
{
    return m_dimensions;
}

qreal ChartCore::pitch() const
{
    return m_pitch;
}

void ChartCore::setPitch(qreal pitch)
{
    if (pitch != m_pitch)
    {
        m_pitch = pitch;
        triggerUpdate();
        emit pitchChanged();
    }
}

int ChartCore::textRole() const
{
    return m_textRole;
}

void ChartCore::setTextRole(int textRole)
{
    if (textRole != m_textRole)
    {
        m_textRole = textRole;

        triggerUpdate();

        emit textRoleChanged();
    }
}

void ChartCore::triggerUpdate()
{
    emit updated();
    update();
}

void ChartCore::paintAxisAndLines(QPainter* painter, qreal offset)
{
    const int minY = qRound(offset);
    const int maxY = height() - offset;
    const int distance = (maxY - minY) / 4;
    const qreal x1 = 0.0;
    const qreal x2 = x1 + width();
    int y = minY;

    painter->setBrush(QBrush("#808080"));
    painter->setPen(Qt::NoPen);

    for (int i = 0; i < 4; i++, y += distance)
    {
        painter->drawRect(QRectF(QPointF(x1, y), QPointF(x2, y + 1)));
    }

    painter->setBrush(QBrush("#000000"));
    painter->drawRect(QRectF(QPointF(x1, maxY), QPointF(x2, maxY + 1)));
}

void ChartCore::appendDimension(QDeclarativeListProperty<Dimension>* list, Dimension *dimension) {
    ChartCore* chartCore = qobject_cast<ChartCore*>(list->object);
    if (chartCore) {
        dimension->setParent(chartCore);
        chartCore->m_dimensions.append(dimension);
        connect(dimension, SIGNAL(updated()), chartCore, SLOT(triggerUpdate()));
        chartCore->triggerUpdate();
    }
}

int ChartCore::countDimensions(QDeclarativeListProperty<Dimension>* list) {
    ChartCore* chartCore = qobject_cast<ChartCore*>(list->object);
    if (chartCore) {
        return chartCore->m_dimensions.count();
    }
    return -1;
}

Dimension* ChartCore::dimensionAt(QDeclarativeListProperty<Dimension>* list, int index) {
    ChartCore* chartCore = qobject_cast<ChartCore*>(list->object);
    if (chartCore) {
        return chartCore->m_dimensions.at(index);
    }
    return 0;
}

void ChartCore::clearDimensions(QDeclarativeListProperty<Dimension>* list) {
    ChartCore* chartCore = qobject_cast<ChartCore*>(list->object);
    if (chartCore) {
        foreach (Dimension* dimension, chartCore->m_dimensions)
        {
            dimension->disconnect(chartCore);
        }
        chartCore->m_dimensions.clear();
        chartCore->triggerUpdate();
    }
}
