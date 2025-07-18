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

ChartCore::ChartCore(QQuickItem *parent) :
    QQuickPaintedItem(parent),
    m_model(nullptr),
    m_pitch(50.0),
    m_textRole(-1)
{
    setFlag(QQuickItem::ItemHasContents, true);
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
            connect(m_model, &QAbstractItemModel::modelReset, this, &ChartCore::triggerUpdate);
            connect(m_model, &QAbstractItemModel::rowsInserted, this, &ChartCore::triggerUpdate);
            connect(m_model, &QAbstractItemModel::rowsRemoved, this, &ChartCore::triggerUpdate);
            connect(m_model, &QAbstractItemModel::rowsMoved, this, &ChartCore::triggerUpdate);
            connect(m_model, &QAbstractItemModel::layoutChanged, this, &ChartCore::triggerUpdate);
            connect(m_model, &QAbstractItemModel::dataChanged, this, &ChartCore::triggerUpdate);
        }

        triggerUpdate();
        Q_EMIT modelChanged();
    }
}

QQmlListProperty<Dimension> ChartCore::dimensions() {
    return QQmlListProperty<Dimension>(this, nullptr, &ChartCore::appendDimension, &ChartCore::countDimensions, &ChartCore::dimensionAt, &ChartCore::clearDimensions);
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
        Q_EMIT pitchChanged();
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

        Q_EMIT textRoleChanged();
    }
}

void ChartCore::triggerUpdate()
{
    Q_EMIT updated();
    update();
}

void ChartCore::paint(QPainter*)
{
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

void ChartCore::appendDimension(QQmlListProperty<Dimension>* list, Dimension *dimension) {
    ChartCore* chartCore = qobject_cast<ChartCore*>(list->object);
    if (chartCore) {
        dimension->setParent(chartCore);
        chartCore->m_dimensions.append(dimension);
        connect(dimension, &Dimension::updated, chartCore, &ChartCore::triggerUpdate);
        chartCore->triggerUpdate();
    }
}

qsizetype ChartCore::countDimensions(QQmlListProperty<Dimension>* list) {
    ChartCore* chartCore = qobject_cast<ChartCore*>(list->object);
    if (chartCore) {
        return chartCore->m_dimensions.count();
    }
    return -1;
}

Dimension* ChartCore::dimensionAt(QQmlListProperty<Dimension>* list, qsizetype index) {
    ChartCore* chartCore = qobject_cast<ChartCore*>(list->object);
    if (chartCore) {
        return chartCore->m_dimensions.at(index);
    }
    return nullptr;
}

void ChartCore::clearDimensions(QQmlListProperty<Dimension>* list) {
    ChartCore* chartCore = qobject_cast<ChartCore*>(list->object);
    if (chartCore) {
        for (Dimension* dimension : std::as_const(chartCore->m_dimensions))
        {
            dimension->disconnect(chartCore);
        }
        chartCore->m_dimensions.clear();
        chartCore->triggerUpdate();
    }
}

#include "moc_chartcore.cpp"
