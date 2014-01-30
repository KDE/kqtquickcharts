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

#ifndef GRAPHCORE_H
#define GRAPHCORE_H

#include <QDeclarativeItem>

#include "dimension.h"

class QAbstractTableModel;

class ChartCore : public QDeclarativeItem
{
    Q_OBJECT
    Q_PROPERTY(QAbstractTableModel* model READ model WRITE setModel NOTIFY modelChanged)
    Q_PROPERTY(QDeclarativeListProperty<Dimension> dimensions READ dimensions CONSTANT)
    Q_PROPERTY(qreal pitch READ pitch WRITE setPitch NOTIFY pitchChanged)
    Q_PROPERTY(int textRole READ textRole WRITE setTextRole NOTIFY textRoleChanged)
public:
    explicit ChartCore(QDeclarativeItem *parent = 0);
    QAbstractTableModel* model() const;
    void setModel(QAbstractTableModel* model);
    QDeclarativeListProperty<Dimension> dimensions();
    QList<Dimension*> dimensionsList() const;
    qreal pitch() const;
    void setPitch(qreal pitch);
    int textRole() const;
    void setTextRole(int textRole);
signals:
    void modelChanged();
    void chartStyleChanged();
    void pitchChanged();
    void textRoleChanged();
    void updated();
protected slots:
    void triggerUpdate();
protected:
    void paintAxisAndLines(QPainter* painter, qreal offset);
private:
    static void appendDimension(QDeclarativeListProperty<Dimension>* list, Dimension* dimension);
    static int countDimensions(QDeclarativeListProperty<Dimension>* list);
    static Dimension* dimensionAt(QDeclarativeListProperty<Dimension>* list, int index);
    static void clearDimensions(QDeclarativeListProperty<Dimension>* list);
    QAbstractTableModel* m_model;
    QList<Dimension*> m_dimensions;
    qreal m_pitch;
    int m_textRole;
};

#endif // GRAPHCORE_H
