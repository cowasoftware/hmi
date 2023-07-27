#pragma once

#include <QAbstractListModel>
#include <QJsonArray>
#include <QJsonObject>
#include <QList>

class JsonListModel : public QAbstractListModel
{
public:
    JsonListModel(const QList<QString> &roles, QObject *parent = nullptr)
        : QAbstractListModel(parent)
    {
        for (auto i = 0; i < roles.size(); i++)
        {
            _roles[int(Qt::UserRole + 1 + i)] = roles[i].toUtf8();
        }
    }

    int rowCount(const QModelIndex &parent) const override
    {
        Q_UNUSED(parent);
        return _data.size();
    }

    QHash<int, QByteArray> roleNames() const override
    {
        return _roles;
    }

    QVariant data(const QModelIndex &index, int role) const override
    {
        int idx = index.row();

        if (idx > -1 && idx < _data.size())
        {
            if (_data[idx].isObject())
            {
                QJsonObject value = _data[idx].toObject();
                return value[_roles[role]].toVariant();
            }
        }

        return {};
    }

    void set(const QJsonArray &data)
    {
        beginResetModel();
        _data = data;
        endResetModel();
    }

    void insert(int index, QJsonArray const &data)
    {
        if (data.size() != 0)
        {
            beginInsertRows(QModelIndex(), index, index + data.size() - 1);

            for (int i = index; i < data.size(); i++)
            {
                _data.insert(i, data[i]);
            }
            endInsertRows();
        }
    }

    void append(const QJsonArray &data)
    {
        if (data.size() == 0)
        {
            return;
        }

        beginInsertRows(QModelIndex(), _data.size(), _data.size() + data.size() - 1);
        for (int i = 0; i < data.size(); i++)
        {
            _data.append(data[i]);
        }
        endInsertRows();
    }

    void remove(int index, int count)
    {
        int minCount = count > _data.size() ? _data.size() : count;
        beginRemoveRows(QModelIndex(), index, index + count - 1);
        for (int i = 0; i < minCount; i++)
        {
            _data.removeAt(index);
        }
        endRemoveRows();
    }
    void clear()
    {
        if (_data.size() != 0)
        {
            remove(0, _data.size());
        }
    }

private:
    QJsonArray _data;
    QHash<int, QByteArray> _roles;
};
