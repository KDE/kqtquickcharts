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

#include "record.h"

Record::Record(QObject* parent) :
    QObject(parent)
{
}

QVariantList Record::values() const
{
    return m_values;
}

void Record::setValues(const QVariantList& values)
{
    if (values != m_values)
    {
        m_values = values;
        emit valuesChanged(this);
    }
}

qreal Record::value(int column) const
{
    if (column >= m_values.count())
        return 0.0;
    return m_values.at(column).toReal();
}

void Record::setValue(int column, qreal value)
{
    while(column >= m_values.count()) {
        m_values.append(0.0);
    }
    m_values[column] = value;
    emit valuesChanged(this);
}
