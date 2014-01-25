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

#include "dimension.h"

#include <KGlobal>
#include <KLocale>

Dimension::Dimension(QDeclarativeItem* parent) :
    QDeclarativeItem(parent),
    m_color(Qt::black),
    m_dataColumn(0),
    m_minimumValue(0),
    m_maximumValue(256),
    m_precision(0),
    m_unitFactor(1)
{
}

QColor Dimension::color() const
{
    return m_color;
}

void Dimension::setColor(const QColor &color)
{
    if (color != m_color)
    {
        m_color = color;
        emit updated();
        emit colorChanged();
    }
}

int Dimension::dataColumn() const
{
    return m_dataColumn;
}

void Dimension::setDataColumn(int dataColumn)
{
    if (dataColumn != m_dataColumn)
    {
        m_dataColumn = dataColumn;
        emit updated();
        emit dataColumnChanged();
    }
}

qreal Dimension::minimumValue() const
{
    return m_minimumValue;
}

void Dimension::setMinimumValue(qreal minimumValue)
{
    if (minimumValue != m_minimumValue)
    {
        m_minimumValue = minimumValue;
        emit updated();
        emit minimumValueChanged();
    }
}

qreal Dimension::maximumValue() const
{
    return m_maximumValue;
}

void Dimension::setMaximumValue(qreal maximumValue)
{
    if (maximumValue != m_maximumValue)
    {
        m_maximumValue = maximumValue;
        emit updated();
        emit maximumValueChanged();
    }
}

QString Dimension::label() const
{
    return m_label;
}

void Dimension::setLabel(const QString& label)
{
    if (label != m_label)
    {
        m_label = label;
        emit updated();
        emit labelChanged();
    }
}

int Dimension::precision() const
{
    return m_precision;
}

void Dimension::setPrecision(int precision)
{
    if (precision != m_precision)
    {
        m_precision = precision;
        emit updated();
        emit precisionChanged();
    }
}

QString Dimension::unit() const
{
    return m_unit;
}

void Dimension::setUnit(const QString& unit)
{
    if (unit != m_unit)
    {
        m_unit = unit;
        emit updated();
        emit unitChanged();
    }
}

qreal Dimension::unitFactor() const
{
    return m_unitFactor;
}

void Dimension::setUnitFactor(qreal unitFactor)
{
    if (unitFactor != m_unitFactor)
    {
        m_unitFactor = unitFactor;
        emit updated();
        emit unitFactorChanged();
    }
}

QString Dimension::formatValue(qreal value)
{
    return KGlobal::locale()->formatNumber(value * m_unitFactor, m_precision) + m_unit;
}
