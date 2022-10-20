/*
 *  Copyright 2015  Jesper Hellesø Hansen <jesperhh@gmail.com>
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

#include "xychartcore.h"
#include <QPainter>
#include <QAbstractTableModel>
#include <QLocale>
#include <assert.h>
#include <cmath>

const qreal divisors[] = { 1, 2, 5};
const int ndivisors = sizeof(divisors) / sizeof(divisors[0]);

XYChartCore::XYChartCore(QQuickItem* parent) :
    ChartCore(parent),
    m_pointRadius(5.0),
    m_lineWidth(2.0),
    m_xAxis(nullptr),
    m_yAxis(nullptr),
    m_labelFont(),
    m_labelFontMetrics(m_labelFont),
    m_minorTickSize(2),
    m_majorTickSize(4),
    m_margin(m_majorTickSize + 4),
    m_gridLines(false),
    m_axisLabelCountGoal(6)
{
    m_labelFont.setPointSize(18);
    m_labelFontMetrics = QFontMetrics(m_labelFont);
    connect(this, &QQuickItem::widthChanged, this, &XYChartCore::triggerUpdate);
    connect(this, &QQuickItem::heightChanged, this, &XYChartCore::triggerUpdate);
    connect(this, &XYChartCore::fontChanged, this, &XYChartCore::triggerUpdate);
    connect(this, &XYChartCore::textColorChanged, this, &XYChartCore::triggerUpdate);
    connect(this, &XYChartCore::pointRadiusChanged, this, &XYChartCore::triggerUpdate);
    connect(this, &XYChartCore::lineWidthChanged, this, &XYChartCore::triggerUpdate);
    connect(this, &XYChartCore::xAxisChanged, this, &XYChartCore::triggerUpdate);
    connect(this, &XYChartCore::yAxisChanged, this, &XYChartCore::triggerUpdate);
    connect(this, &XYChartCore::gridLinesChanged, this, &XYChartCore::triggerUpdate);
    connect(this, &XYChartCore::axisLabelCountGoalChanged, this, &XYChartCore::triggerUpdate);
    connect(this, &ChartCore::updated, this, &XYChartCore::updateAxis);
}

qreal XYChartCore::pointRadius() const
{
    return m_pointRadius;
}

void XYChartCore::setPointRadius(qreal pointRadius)
{
    if (pointRadius != m_pointRadius)
    {
        m_pointRadius = pointRadius;
        emit pointRadiusChanged();
    }
}

qreal XYChartCore::lineWidth() const
{
    return m_lineWidth;
}

void XYChartCore::setLineWidth(qreal lineWidth)
{
    if (lineWidth != m_lineWidth)
    {
        m_lineWidth = lineWidth;
        emit lineWidthChanged();
    }
}

void XYChartCore::paint(QPainter* painter)
{
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setFont(m_labelFont);
    QPen pen(m_textColor);
    pen.setWidthF(m_lineWidth);
    painter->setPen(pen);

    if (m_gridLines)
        paintGrid(painter);

    paintAxis(painter);
    paintTicks(painter);
    paintAxisLabels(painter);
    paintDimensionLabels(painter);
}

void XYChartCore::paintAxis(QPainter* painter)
{
    const qreal minKey = xAxis()->minimumValue();
    const qreal maxKey = xAxis()->maximumValue();
    const qreal minValue = yAxis()->minimumValue();
    const qreal maxValue = yAxis()->maximumValue();

    const QPointF origo = translatePoint(QPointF(0.0, 0.0));
    const QPointF p1 = translatePoint(QPointF(minKey, 0.0));
    const QPointF p2 = translatePoint(QPointF(maxKey, 0.0));
    const QPointF p3 = translatePoint(QPointF(0.0, minValue));
    const QPointF p4 = translatePoint(QPointF(0.0, maxValue));

    if (origo != p1)
        painter->drawLine(origo, p1);

    if (origo != p2)
        painter->drawLine(origo, p2);

    if (origo != p3)
        painter->drawLine(origo, p3);

    if (origo != p4)
        painter->drawLine(origo, p4);
}

void XYChartCore::paintGrid(QPainter* painter)
{
    foreach(qreal label, m_xAxisLabels)
    {
        const qreal x = translatePoint(QPointF(label, 0.0)).x();
        painter->drawLine(x, m_lowerLeftCorner.y(), x, m_lowerLeftCorner.y() - m_graphHeight);
    }

    foreach(qreal label, m_yAxisLabels)
    {
        const qreal y = translatePoint(QPointF(0.0, label)).y();
        painter->drawLine(m_lowerLeftCorner.x(), y, m_lowerLeftCorner.x() + m_graphWidth, y);
    }
}

void XYChartCore::paintTicks(QPainter* painter)
{
    int tick = 2, tock = 4;

    qreal label;
    QPointF point;
    for (int i = 0; i < m_xAxisLabels.size(); i++)
    {
        label = m_xAxisLabels[i];
        point = translatePoint(QPointF(label, 0.0));
        painter->drawLine(point.x(), point.y() - tock, point.x(), point.y() + tock);

        if (i < m_xAxisLabels.size() - 1)
        {
            label = (m_xAxisLabels[i] + m_xAxisLabels[i + 1]) / 2.0;
            point = translatePoint(QPointF(label, 0.0));
            painter->drawLine(point.x(), point.y() - tick, point.x(), point.y() + tick);
        }
    }

    for (int i = 0; i < m_yAxisLabels.size(); i++)
    {
        label = m_yAxisLabels[i];
        point = translatePoint(QPointF(0.0, label));
        painter->drawLine(point.x() - tock, point.y(), point.x() + tock, point.y());

        if (i < m_yAxisLabels.size() - 1)
        {
            label = (m_yAxisLabels[i] + m_yAxisLabels[i + 1]) / 2.0;
            point = translatePoint(QPointF(0.0, label));
            painter->drawLine(point.x() - tick, point.y(), point.x() + tick, point.y());
        }
    }
}

void XYChartCore::paintAxisLabels(QPainter* painter)
{
    int labelHeight = painter->fontMetrics().tightBoundingRect(QStringLiteral("0123456789")).height();
    foreach(qreal label, m_xAxisLabels)
    {
        QString strLabel = formatLabel(label, xAxis());
        int labelWidth = painter->fontMetrics().boundingRect(strLabel).width();
        const QPointF point = translatePoint(QPointF(label, 0.0));
        painter->drawText(point.x() - labelWidth / 2, point.y() + labelHeight + m_margin, strLabel);
    }

    foreach(qreal label, m_yAxisLabels)
    {
        QString strLabel = formatLabel(label, yAxis());
        int labelWidth = painter->fontMetrics().boundingRect(strLabel).width();
        const QPointF point = translatePoint(QPointF(0.0, label));
        painter->drawText(point.x() - labelWidth - m_margin, point.y() + (labelHeight / 2), strLabel);
    }
}

void XYChartCore::paintDimensionLabels(QPainter* painter)
{
    QList<QPair<qreal, QString>> labels;
    const int row = model()->rowCount() - 1;
    if (row == -1)
        return;

    const qreal maxKey = model()->data(model()->index(row, xAxis()->dataColumn())).toReal();
    const qreal x = translatePoint(QPointF(maxKey, 0.0)).x();
    foreach(Dimension* dimension, dimensionsList())
    {
        const QString label = dimension->label();
        if (label.isEmpty())
            continue;

        const int column = dimension->dataColumn();
        const qreal value = model()->data(model()->index(row, column)).toReal();

        // We do not label dimensions that miss values for the last point
        // Use point text for labels inside the chart
        if (qIsNaN(value))
            continue;

        const qreal y = translatePoint(QPointF(maxKey, value)).y();
        labels.append(QPair<qreal, QString>(y, label));
    }

    if (labels.empty())
        return;

    for (const auto& iter : labels)
    {
        int labelheight = m_labelFontMetrics.tightBoundingRect(iter.second).height();
        painter->drawText(x + m_margin, iter.first + (labelheight / 2.0), iter.second);
    }
}

void XYChartCore::updateAxis()
{
    if (!xAxis() || !yAxis())
        return;

    const qreal minKey = xAxis()->minimumValue();
    const qreal maxKey = xAxis()->maximumValue();
    m_xAxisLabels = generateAxisLabels(minKey, maxKey);

    const qreal minValue = yAxis()->minimumValue();
    const qreal maxValue = yAxis()->maximumValue();
    m_yAxisLabels = generateAxisLabels(minValue, maxValue);

    const int minValueStringLength = formatLabel(minValue, yAxis()).length();
    const int maxValueStringLength = formatLabel(maxValue, yAxis()).length();
    const int minKeyStringLength = formatLabel(minKey, xAxis()).length();
    const int maxKeyStringLength = formatLabel(maxKey, xAxis()).length();

    int maxYLabelWidth = m_labelFontMetrics.boundingRect(QStringLiteral("W")).width() * std::max(minValueStringLength, maxValueStringLength);
    int maxXLabelWidth = m_labelFontMetrics.boundingRect(QStringLiteral("W")).width() * std::max(minKeyStringLength, maxKeyStringLength);

    m_lowerLeftCorner.setX(maxYLabelWidth + m_margin);
    m_lowerLeftCorner.setY(height() - m_labelFontMetrics.height() - m_margin);
    m_graphWidth = width() - m_lowerLeftCorner.x() - (maxXLabelWidth / 2);
    m_graphHeight = m_lowerLeftCorner.y() - (m_labelFontMetrics.height() / 2);
}

QString XYChartCore::formatLabel(const qreal label, const Dimension* dimension) const
{
    QLocale locale;
    return locale.toString(label, 'f', dimension->precision());
}

QPointF XYChartCore::translatePoint(QPointF point)
{
    const qreal minKey = xAxis()->minimumValue();
    const qreal maxKey = xAxis()->maximumValue();
    const qreal minVal = yAxis()->minimumValue();
    const qreal maxVal = yAxis()->maximumValue();

    const qreal x = m_lowerLeftCorner.x() + (m_graphWidth  * (point.x() - minKey) / (maxKey - minKey));
    const qreal y = m_lowerLeftCorner.y() - (m_graphHeight * (point.y() - minVal) / (maxVal - minVal));
    return QPointF(x, y);
}


QList<qreal> XYChartCore::generateAxisLabels(const qreal minValue, const qreal maxValue)
{
    // Distance between labels with preferred number of labels
    qreal div = fabs(maxValue - minValue) / m_axisLabelCountGoal;
    // Find power of 10 to scale preferred increments to
    qreal scale = std::pow(10, floor(std::log10(div)));

    // Find closest increment that has at maximum div distance between labels
    qreal increment = divisors[0] * scale;
    for (int i = 0; i < ndivisors; i++)
    {
        if ((divisors[i] * scale) > div)
            break;

        increment = divisors[i] * scale;
    }

    increment *= (maxValue - minValue) < 0.0 ? -1.0 : 1.0;

    qreal label = minValue;
    QList<qreal> result;
    while (label <= maxValue)
    {
        result << label;
        label += increment;
    }

    return result;
}

Dimension* XYChartCore::xAxis() const
{
    return m_xAxis;
}

void XYChartCore::setXAxis(Dimension* xAxis)
{
    if (m_xAxis != xAxis)
    {
        m_xAxis = xAxis;
        xAxisChanged();
    }
}

QColor XYChartCore::textColor() const
{
    return m_textColor;
}

void XYChartCore::setTextColor(QColor color)
{
    if (m_textColor != color)
    {
        m_textColor = color;
        emit textColorChanged();
    }
}

QFont XYChartCore::font() const
{
    return m_labelFont;
}

void XYChartCore::setFont(const QFont &font)
{
    if (font != m_labelFont)
    {
        m_labelFont = font;
        emit fontChanged();
    }
}

bool XYChartCore::gridLines() const
{
    return m_gridLines;
}

void XYChartCore::setGridLines(bool gridLines)
{
    if (m_gridLines != gridLines)
    {
        m_gridLines = gridLines;
        emit gridLinesChanged();
    }
}

Dimension* XYChartCore::yAxis() const
{
    return m_yAxis;
}

void XYChartCore::setYAxis(Dimension* yAxis)
{
    if (m_yAxis != yAxis)
    {
        m_yAxis = yAxis;
        yAxisChanged();
    }
}

unsigned int XYChartCore::axisLabelCountGoal() const
{
    return m_axisLabelCountGoal;
}

void XYChartCore::setAxisLabelCountGoal(unsigned int axisLabelCountGoal)
{
    if (m_axisLabelCountGoal != axisLabelCountGoal)
    {
        m_axisLabelCountGoal = axisLabelCountGoal;
        axisLabelCountGoalChanged();
    }
}
