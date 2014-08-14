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

#ifndef CHARTMODEL_H
#define CHARTMODEL_H

#include <QAbstractTableModel>

#include <QQmlListProperty>

class Record;

class ChartModel : public QAbstractTableModel
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<Record> records READ records CONSTANT)
    Q_PROPERTY(int columns READ columns WRITE setColumns NOTIFY columnsChanged)
    Q_PROPERTY(int rows READ rows NOTIFY rowsChanged)
    Q_CLASSINFO("DefaultProperty", "records")
public:
    QQmlListProperty<Record> records();
    int columns() const;
    void setColumns(int columns);
    int rows() const;
    Q_INVOKABLE void appendRecord();
    Q_INVOKABLE void insertRecord(int row);
    Q_INVOKABLE void removeRecord(int row);
    Q_INVOKABLE qreal value(int row, int column) const;
    Q_INVOKABLE void setValue(int row, int column, qreal value);
    explicit ChartModel(QObject* parent = 0);
    int rowCount(const QModelIndex& parent) const;
    int columnCount(const QModelIndex& parent) const;
    QVariant data(const QModelIndex& index, int role) const;
Q_SIGNALS:
    void columnsChanged();
    void rowsChanged();
    void recordChanged(int row);
private Q_SLOTS:
    void onRecordChanged(Record* record);
private:
    void insertRecord(int row, Record* record);
    static void appendRecord(QQmlListProperty<Record>* list, Record* record);
    static int countRecords(QQmlListProperty<Record>* list);
    static Record* recordAt(QQmlListProperty<Record>* list, int index);
    static void clearRecords(QQmlListProperty<Record>* list);
    QList<Record*> m_records;
    int m_columns;
};

#endif // CHARTMODEL_H
