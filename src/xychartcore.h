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

#ifndef XYGRAPHCORE_H
#define XYGRAPHCORE_H

#include "chartcore.h"
#include <QFont>
#include <QFontMetrics>

class Dimension;

class XYChartCore : public ChartCore
{
    Q_OBJECT
    Q_PROPERTY(qreal pointRadius READ pointRadius WRITE setPointRadius NOTIFY pointRadiusChanged)
    Q_PROPERTY(qreal lineWidth READ lineWidth WRITE setLineWidth NOTIFY lineWidthChanged)
    Q_PROPERTY(Dimension* xAxis READ xAxis WRITE setXAxis NOTIFY xAxisChanged)
    Q_PROPERTY(Dimension* yAxis READ yAxis WRITE setYAxis NOTIFY yAxisChanged)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor NOTIFY textColorChanged)
    Q_PROPERTY(QFont font READ font WRITE setFont NOTIFY fontChanged)
    Q_PROPERTY(bool gridLines READ gridLines WRITE setGridLines NOTIFY gridLinesChanged)
    Q_PROPERTY(unsigned int axisLabelCountGoal READ axisLabelCountGoal WRITE setAxisLabelCountGoal NOTIFY axisLabelCountGoalChanged)
public:
    explicit XYChartCore(QQuickItem* parent = 0);
    qreal pointRadius() const;
    void setPointRadius(qreal pointRadius);
    qreal lineWidth() const;
    void setLineWidth(qreal lineWidth);
    Dimension* xAxis() const;
    void setXAxis(Dimension* xAxis);
    Dimension* yAxis() const;
    void setYAxis(Dimension* yAxis);
    QColor textColor() const;
    void setTextColor(QColor color);
    QFont font() const;
    void setFont(QFont font);
    bool gridLines() const;
    void setGridLines(bool gridLines);
    unsigned int axisLabelCountGoal() const;
    void setAxisLabelCountGoal(unsigned int axisLabelCountGoal);
    QList<qreal> generateAxisLabels(const qreal minValue, const qreal maxValue);
    void paint(QPainter* painter) override;
    QPointF translatePoint(QPointF point);

Q_SIGNALS:
    void pointRadiusChanged();
    void lineWidthChanged();
    void xAxisChanged();
    void yAxisChanged();
    void textColorChanged();
    void fontChanged();
    void gridLinesChanged();
    void axisLabelCountGoalChanged();

protected Q_SLOTS:
    void updateAxis();

protected:
    void paintAxis(QPainter* painter);
    void paintAxisLabels(QPainter* painter);
    void paintTicks(QPainter* painter);
    void paintGrid(QPainter* painter);
    void paintDimensionLabels(QPainter* painter);

private:
    QString formatLabel(const qreal label, const Dimension* dimension) const;

    QList<qreal> m_xAxisLabels;
    QList<qreal> m_yAxisLabels;
    qreal m_pointRadius;
    qreal m_lineWidth;
    QPointF m_lowerLeftCorner;
    Dimension* m_xAxis;
    Dimension* m_yAxis;
    QFont m_labelFont;
    QFontMetrics m_labelFontMetrics;
    QColor m_textColor;
    qreal m_graphHeight;
    qreal m_graphWidth;
    int m_minorTickSize;
    int m_majorTickSize;
    int m_margin;
    bool m_gridLines;
    unsigned int m_axisLabelCountGoal;
};

#endif // XYGRAPHCORE_H
