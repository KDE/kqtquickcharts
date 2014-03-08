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


#include "value.h"
#include "record.h"

Value::Value(QObject* parent) :
    QObject(parent),
    m_value(0.0)
{
}

qreal Value::value() const
{
    return m_value;
}

void Value::setValue(qreal value)
{
    if (value != m_value)
    {
        m_value = value;
        emit valueChanged();
    }
}
