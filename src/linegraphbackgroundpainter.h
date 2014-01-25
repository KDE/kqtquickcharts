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

#ifndef LINEGRAPHBACKGROUNDPAINTER_H
#define LINEGRAPHBACKGROUNDPAINTER_H

#include <QDeclarativeItem>

class LineGraphCore;

class LineGraphBackgroundPainter : public QDeclarativeItem
{
    Q_OBJECT
    Q_PROPERTY(LineGraphCore* lineGraphCore READ lineGraphCore WRITE setLineGraphCore NOTIFY lineGraphCoreChanged)
public:
    explicit LineGraphBackgroundPainter(QDeclarativeItem* parent = 0);
    LineGraphCore* lineGraphCore() const;
    void setLineGraphCore(LineGraphCore* lineGraphCore);
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*);
    const QList<QPolygonF>& linePolygons() const;
signals:
    void lineGraphCoreChanged();
    void linePolygonsUpdated();
private slots:
    void triggerUpdate();
private:
    void updateWidth();
    void updateLinePolygons();
    LineGraphCore* m_lineGraphCore;
    QList<QPolygonF> m_linePolygons;
};

#endif // LINEGRAPHBACKGROUNDPAINTER_H
