/*
 * Copyright 2014  Sebastian Gottfried <sebastiangottfried@web.de>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "record.h"

#include <QSignalMapper>

#include "value.h"

Record::Record(QObject* parent) :
    QObject(parent),
    m_valueSignalMapper(new QSignalMapper(this))
{
    connect(m_valueSignalMapper, SIGNAL(mapped(int)), SLOT(onValueChanged(int)));
}

QDeclarativeListProperty<Value> Record::values()
{
    return QDeclarativeListProperty<Value>(this, 0, &Record::appendValue, &Record::countValues, &Record::valueAt, &Record::clearValues);
}

qreal Record::value(int column) const
{
    if (column >= m_values.count())
        return 0.0;
    return m_values.at(column)->value();
}

void Record::setValue(int column, qreal value)
{
    while(column >= m_values.count()) {
        Value* value = new Value(this);
        m_valueSignalMapper->setMapping(value, m_values.count());
        connect(value, SIGNAL(valueChanged()), m_valueSignalMapper, SLOT(map()));
        m_values.append(value);
    }
    m_values.at(column)->setValue(value);
}

void Record::onValueChanged(int column)
{
    emit this->valueChanged(this, column);
}

void Record::appendValue(QDeclarativeListProperty<Value>* list, Value* value)
{
    Record* record = qobject_cast<Record*>(list->object);
    if (record)
    {
        value->setParent(record);
        record->m_valueSignalMapper->setMapping(value, record->m_values.count());
        connect(value, SIGNAL(valueChanged()), record->m_valueSignalMapper, SLOT(map()));
        record->m_values.append(value);
    }
}

int Record::countValues(QDeclarativeListProperty<Value>* list)
{
    Record* record = qobject_cast<Record*>(list->object);
    if (record)
    {
        return record->m_values.count();
    }
    return -1;
}

Value* Record::valueAt(QDeclarativeListProperty<Value>* list, int index)
{
    Record* record = qobject_cast<Record*>(list->object);
    if (record)
    {
        return record->m_values.at(index);
    }
    return 0;
}

void Record::clearValues(QDeclarativeListProperty<Value>* list)
{
    Record* record = qobject_cast<Record*>(list->object);
    if (record)
    {
        record->m_values.clear();
    }
}
