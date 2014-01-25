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

#ifndef LINEGRAPHFOREGROUNDPAINTER_H
#define LINEGRAPHFOREGROUNDPAINTER_H

#include <QDeclarativeItem>

class GraphCore;

class GraphForegroundPainter : public QDeclarativeItem
{
    Q_OBJECT
    Q_PROPERTY(GraphCore* graphCore READ graphCore WRITE setGraphCore NOTIFY graphCoreChanged)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
public:
    explicit GraphForegroundPainter(QDeclarativeItem* parent = 0);
    GraphCore* graphCore() const;
    void setGraphCore(GraphCore* graphCore);
    QColor backgroundColor() const;
    void setBackgroundColor(const QColor& backgroundColor);
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*);
signals:
    void graphCoreChanged();
    void backgroundColorChanged();
private slots:
    void triggerUpdate();
private:
    GraphCore* m_graphCore;
    QColor m_backgroundColor;
};

#endif // LINEGRAPHFOREGROUNDPAINTER_H
