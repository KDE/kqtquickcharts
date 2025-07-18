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

#include <QLocale>

Dimension::Dimension(QObject* parent) :
    QObject(parent),
    m_color(Qt::black),
    m_dataColumn(0),
    m_minimumValue(0),
    m_maximumValue(256),
    m_precision(0),
    m_unitFactor(1),
    m_markerStyle(MarkerStyleRound),
    m_lineStyle(LineStyleSolid)
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
        Q_EMIT updated();
        Q_EMIT colorChanged();
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
        Q_EMIT updated();
        Q_EMIT dataColumnChanged();
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
        Q_EMIT updated();
        Q_EMIT minimumValueChanged();
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
        Q_EMIT updated();
        Q_EMIT maximumValueChanged();
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
        Q_EMIT updated();
        Q_EMIT labelChanged();
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
        Q_EMIT updated();
        Q_EMIT precisionChanged();
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
        Q_EMIT updated();
        Q_EMIT unitChanged();
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
        Q_EMIT updated();
        Q_EMIT unitFactorChanged();
    }
}

QString Dimension::formatValue(qreal value)
{
    QLocale locale;
    return locale.toString(value * m_unitFactor, 'f', m_precision);
}

Dimension::MarkerStyle Dimension::markerStyle() const
{
    return m_markerStyle;
}

void Dimension::setMarkerStyle(MarkerStyle markerstyle)
{
    if (m_markerStyle != markerstyle)
    {
        m_markerStyle = markerstyle;
        Q_EMIT updated();
        Q_EMIT markerStyleChanged();
    }
}

Dimension::LineStyle Dimension::lineStyle() const
{
    return m_lineStyle;
}

void Dimension::setLineStyle(LineStyle lineStyle)
{
    if (m_lineStyle != lineStyle)
    {
        m_lineStyle = lineStyle;
        Q_EMIT updated();
        Q_EMIT lineStyleChanged();
    }
}

#include "moc_dimension.cpp"
