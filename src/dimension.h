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

#ifndef DIMENSION_H
#define DIMENSION_H

#include <QObject>

#include <QColor>

class Dimension : public QObject
{
Q_OBJECT
public:
    enum MarkerStyle
    {
        MarkerStyleNone,
        MarkerStyleRound,
        MarkerStyleCross
    };
    Q_ENUMS(MarkerStyle)
    enum LineStyle
    {
        LineStyleNone,
        LineStyleSolid,
        LineStyleDash
    };
    Q_ENUMS(LineStyle)

    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(int dataColumn READ dataColumn WRITE setDataColumn NOTIFY dataColumnChanged)
    Q_PROPERTY(qreal minimumValue READ minimumValue WRITE setMinimumValue NOTIFY minimumValueChanged)
    Q_PROPERTY(qreal maximumValue READ maximumValue WRITE setMaximumValue NOTIFY maximumValueChanged)
    Q_PROPERTY(QString label READ label WRITE setLabel NOTIFY labelChanged)
    Q_PROPERTY(int precision READ precision WRITE setPrecision NOTIFY precisionChanged)
    Q_PROPERTY(QString unit READ unit WRITE setUnit NOTIFY unitChanged)
    Q_PROPERTY(qreal unitFactor READ unitFactor WRITE setUnitFactor NOTIFY unitFactorChanged)
    Q_PROPERTY(MarkerStyle markerStyle READ markerStyle WRITE setMarkerStyle NOTIFY markerStyleChanged)
    Q_PROPERTY(LineStyle lineStyle READ lineStyle WRITE setLineStyle NOTIFY lineStyleChanged)

    explicit Dimension(QObject* parent = 0);
    QColor color() const;
    void setColor(const QColor& color);
    int dataColumn() const;
    void setDataColumn(int dataColumn);
    qreal minimumValue() const;
    void setMinimumValue(qreal minimumValue);
    qreal maximumValue() const;
    void setMaximumValue(qreal maximumValue);
    QString label() const;
    void setLabel(const QString& label);
    int precision() const;
    void setPrecision(int precision);
    QString unit() const;
    void setUnit(const QString& unit);
    qreal unitFactor() const;
    void setUnitFactor(qreal unitFactor);
    MarkerStyle markerStyle() const;
    void setMarkerStyle(MarkerStyle markerstyle);
    LineStyle lineStyle() const;
    void setLineStyle(LineStyle lineStyle);
    Q_INVOKABLE QString formatValue(qreal value);

Q_SIGNALS:
    void colorChanged();
    void dataColumnChanged();
    void minimumValueChanged();
    void maximumValueChanged();
    void labelChanged();
    void precisionChanged();
    void unitChanged();
    void unitFactorChanged();
    void updated();
    void markerStyleChanged();
    void lineStyleChanged();
private:
    QColor m_color;
    int m_dataColumn;
    qreal m_minimumValue;
    qreal m_maximumValue;
    QString m_label;
    int m_precision;
    QString m_unit;
    qreal m_unitFactor;
    MarkerStyle m_markerStyle;
    LineStyle m_lineStyle;
};

#endif // DIMENSION_H
