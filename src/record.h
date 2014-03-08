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

#ifndef RECORD_H
#define RECORD_H

#include <QObject>

#include <QDeclarativeListProperty>

class QSignalMapper;
class Value;

class Record : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QDeclarativeListProperty<Value> values READ values CONSTANT)
    Q_CLASSINFO("DefaultProperty", "values")
public:
    explicit Record(QObject* parent = 0);
    QDeclarativeListProperty<Value> values();
    Q_INVOKABLE qreal value(int column) const;
    Q_INVOKABLE void setValue(int column, qreal value);
signals:
    void valueChanged(Record* record, int column);
private slots:
    void onValueChanged(int column);
private:
    static void appendValue(QDeclarativeListProperty<Value>* list, Value* value);
    static int countValues(QDeclarativeListProperty<Value>* list);
    static Value* valueAt(QDeclarativeListProperty<Value>* list, int index);
    static void clearValues(QDeclarativeListProperty<Value>* list);
    QList<Value*> m_values;
    QSignalMapper* m_valueSignalMapper;
};

#endif // RECORD_H
