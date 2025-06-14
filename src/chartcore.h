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

#ifndef CHARTCORE_H
#define CHARTCORE_H

#include <QQuickPaintedItem>

#include "dimension.h"

class QAbstractTableModel;

class ChartCore : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QAbstractTableModel* model READ model WRITE setModel NOTIFY modelChanged)
    Q_PROPERTY(QQmlListProperty<Dimension> dimensions READ dimensions CONSTANT)
    Q_PROPERTY(qreal pitch READ pitch WRITE setPitch NOTIFY pitchChanged)
    Q_PROPERTY(int textRole READ textRole WRITE setTextRole NOTIFY textRoleChanged)
public:
    explicit ChartCore(QQuickItem *parent = nullptr);
    QAbstractTableModel* model() const;
    void setModel(QAbstractTableModel* model);
    QQmlListProperty<Dimension> dimensions();
    QList<Dimension*> dimensionsList() const;
    qreal pitch() const;
    void setPitch(qreal pitch);
    int textRole() const;
    void setTextRole(int textRole);
Q_SIGNALS:
    void modelChanged();
    void chartStyleChanged();
    void pitchChanged();
    void textRoleChanged();
    void updated();
protected Q_SLOTS:
    void triggerUpdate();
protected:
    void paint(QPainter* painter) override;
    void paintAxisAndLines(QPainter* painter, qreal offset);
private:
    static void appendDimension(QQmlListProperty<Dimension>* list, Dimension* dimension);
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    static int countDimensions(QQmlListProperty<Dimension>* list);
    static Dimension* dimensionAt(QQmlListProperty<Dimension>* list, int index);
#else
    static qsizetype countDimensions(QQmlListProperty<Dimension>* list);
    static Dimension* dimensionAt(QQmlListProperty<Dimension>* list, qsizetype index);
#endif
    static void clearDimensions(QQmlListProperty<Dimension>* list);
    QAbstractTableModel* m_model;
    QList<Dimension*> m_dimensions;
    qreal m_pitch;
    int m_textRole;
};

#endif // CHARTCORE_H
