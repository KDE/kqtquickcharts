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

#include "chartmodel.h"

#include "record.h"

ChartModel::ChartModel(QObject* parent) :
    QAbstractTableModel(parent),
    m_columns(0)
{
}

QDeclarativeListProperty<Record> ChartModel::records()
{
    return QDeclarativeListProperty<Record>(this, 0, &ChartModel::appendRecord, &ChartModel::countRecords, &ChartModel::recordAt, &ChartModel::clearRecords);
}

int ChartModel::columns() const
{
    return m_columns;
}

void ChartModel::setColumns(int columns)
{
    if (columns != m_columns)
    {
        m_columns = columns;
        reset();
        emit columnsChanged();
    }
}

int ChartModel::rows() const
{
    return m_records.count();
}

qreal ChartModel::value(int row, int column) const
{
    if (row >= m_records.count())
        return 0.0;
    return m_records.at(row)->value(column);
}

void ChartModel::appendRecord()
{
    insertRecord(rows(), new Record());
}

void ChartModel::insertRecord(int row)
{
    insertRecord(row, new Record());
}

void ChartModel::removeRecord(int row)
{
    beginRemoveRows(QModelIndex(), row, row);
    Record* record = m_records.at(row);
    record->disconnect(this);
    m_records.removeAt(row);
    record->deleteLater();
    endRemoveRows();
    emit rowsChanged();
}

void ChartModel::setValue(int row, int column, qreal value)
{
    while (row >= m_records.count())
    {
        appendRecord();
    }
    m_records.at(row)->setValue(column, value);
}

int ChartModel::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid())
        return 0;
    return m_records.count();
}

int ChartModel::columnCount(const QModelIndex& parent) const
{
    if (parent.isValid())
        return 0;
    return m_columns;
}

QVariant ChartModel::data(const QModelIndex& index, int role) const
{
    if (index.parent().isValid())
        return QVariant();
    if (role != Qt::DisplayRole)
        return QVariant();
    return QVariant(value(index.row(), index.column()));
}

void ChartModel::onRecordChanged(Record* record)
{
    const int row = m_records.indexOf(record);
    emit dataChanged(index(row, 0), index(row, columns() - 1));
    emit recordChanged();
}

void ChartModel::insertRecord(int row, Record *record)
{
    beginInsertRows(QModelIndex(), row, row);
    record->setParent(this);
    connect(record, SIGNAL(valuesChanged(Record*)), SLOT(onRecordChanged(Record*)));
    m_records.insert(row, record);
    endInsertRows();
    emit rowsChanged();
}

void ChartModel::appendRecord(QDeclarativeListProperty<Record>* list, Record* record)
{
    ChartModel* chartModel = qobject_cast<ChartModel*>(list->object);
    if (chartModel)
    {
        chartModel->insertRecord(chartModel->rows(), record);
    }
}

int ChartModel::countRecords(QDeclarativeListProperty<Record>* list)
{
    ChartModel* chartModel = qobject_cast<ChartModel*>(list->object);
    if (chartModel)
    {
        return chartModel->m_records.count();
    }
    return -1;
}

Record* ChartModel::recordAt(QDeclarativeListProperty<Record>* list, int index)
{
    ChartModel* chartModel = qobject_cast<ChartModel*>(list->object);
    if (chartModel)
    {
        return chartModel->m_records.at(index);
    }
    return 0;
}

void ChartModel::clearRecords(QDeclarativeListProperty<Record>* list)
{
    ChartModel* chartModel = qobject_cast<ChartModel*>(list->object);
    if (chartModel)
    {
        qDeleteAll(chartModel->m_records);
        chartModel->m_records.clear();
        emit chartModel->rowsChanged();
    }
}
