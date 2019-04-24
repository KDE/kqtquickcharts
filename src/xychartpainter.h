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
#ifndef XYCHARTPAINTER_H
#define XYCHARTPAINTER_H

#include <QQuickPaintedItem>

class XYChartCore;
class XYChartBackgroundPainter;

class XYChartPainter : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(XYChartCore* xyChartCore READ xyChartCore WRITE setXYChartCore NOTIFY xyChartCoreChanged)
    Q_PROPERTY(XYChartBackgroundPainter* backgroundPainter READ backgroundPainter WRITE setBackgroundPainter NOTIFY backgroundPainterChanged)
    Q_PROPERTY(int dimension READ dimension WRITE setDimension NOTIFY dimensionChanged)
public:
    explicit XYChartPainter(QQuickItem* parent = nullptr);
    XYChartCore* xyChartCore() const;
    void setXYChartCore(XYChartCore* xyChartCore);
    XYChartBackgroundPainter* backgroundPainter() const;
    void setBackgroundPainter(XYChartBackgroundPainter* backgroundPainter);
    int dimension() const;
    void setDimension(int dimension);
    void paint(QPainter* painter) override;
Q_SIGNALS:
    void xyChartCoreChanged();
    void backgroundPainterChanged();
    void dimensionChanged();
private Q_SLOTS:
    void triggerUpdate();
private:
    XYChartCore* m_xyChartCore;
    XYChartBackgroundPainter* m_backgroundPainter;
    int m_dimension;
};

#endif // XYCHARTPAINTER_H
