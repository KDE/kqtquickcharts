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

#ifndef RECORD_H
#define RECORD_H

#include <QObject>

#include <QVariantList>

class Record : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList values READ values WRITE setValues NOTIFY valuesChanged)
public:
    explicit Record(QObject* parent = 0);
    QVariantList values() const;
    void setValues(const QVariantList& values);
    Q_INVOKABLE qreal value(int column) const;
    Q_INVOKABLE void setValue(int column, qreal value);
signals:
    void valuesChanged(Record* record);
private:
    QVariantList m_values;
};

#endif // RECORD_H
