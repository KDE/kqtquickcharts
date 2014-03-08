/*
 * Copyright 2014  Sebastian Gottfried <sebastiangottfried@web.de>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CHARTMODEL_H
#define CHARTMODEL_H

#include <QAbstractTableModel>

#include <QDeclarativeListProperty>

class Record;

class ChartModel : public QAbstractTableModel
{
    Q_OBJECT
    Q_PROPERTY(QDeclarativeListProperty<Record> records READ records CONSTANT)
    Q_PROPERTY(int columns READ columns WRITE setColumns NOTIFY columnsChanged)
    Q_PROPERTY(int rows READ rows NOTIFY rowsChanged)
    Q_CLASSINFO("DefaultProperty", "records")
public:
    QDeclarativeListProperty<Record> records();
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
signals:
    void columnsChanged();
    void rowsChanged();
    void valueChanged(int row, int column);
private slots:
    void onRecordValueChanged(Record* record, int column);
private:
    void insertRecord(int row, Record* record);
    static void appendRecord(QDeclarativeListProperty<Record>* list, Record* record);
    static int countRecords(QDeclarativeListProperty<Record>* list);
    static Record* recordAt(QDeclarativeListProperty<Record>* list, int index);
    static void clearRecords(QDeclarativeListProperty<Record>* list);
    QList<Record*> m_records;
    int m_columns;
};

#endif // CHARTMODEL_H
