/**
 * HPGL List Model - header
 * Christopher Bero <bigbero@gmail.com>
 */
#ifndef HPGLLISTMODEL_H
#define HPGLLISTMODEL_H

#include <QtCore>
#include <QAbstractListModel>
#include <QAbstractItemModel>
#include <QGraphicsItemGroup>
#include <QGraphicsRectItem>
#include <QMutex>
#include <QMutexLocker>
#include <math.h>

#define QMODELINDEX_KEY (1)
#define QPLOTSCENE_KEY (2)

// hpgl structs
struct file_uid {
    QString filename;
    QString path;
    int uid;
};

struct hpgl_file {
    file_uid name;
    QVector<QGraphicsPolygonItem *> hpgl_items;
    QGraphicsItemGroup * hpgl_items_group;
    QGraphicsRectItem * cutoutBox;
    QMutex mutex;
};
bool operator==(const file_uid& lhs, const file_uid& rhs);

namespace std {
class hpglListModel;
}

class hpglListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit hpglListModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool dataGroup(const QPersistentModelIndex index, QMutex *&retLocker,
                    QGraphicsItemGroup *&itemGroup);
    bool dataItemsGroup(const QPersistentModelIndex index, QMutex *&retLocker,
                        QGraphicsItemGroup *&itemGroup, QVector<QGraphicsPolygonItem *> *&items);
    bool dataItems(const QPersistentModelIndex index, QMutex *&retLocker, QVector<QGraphicsPolygonItem *> *&items);
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    bool setGroupFlag(const QModelIndex &index, QGraphicsItem::GraphicsItemFlag flag, bool flagValue);
    QModelIndex index(int row, int column = 0, const QModelIndex &parent = QModelIndex()) const;
    bool insertRow(int row, const QModelIndex &parent = QModelIndex());
    bool removeRow(int row, const QModelIndex &parent = QModelIndex());
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
    void addPolygon(QPersistentModelIndex index, QGraphicsPolygonItem * poly);
    void constrainItems(QPointF bottomLeft, QPointF topLeft);
    bool setFileUid(const QModelIndex &index, const file_uid filename);
    void sort();

private:
    QVector<hpgl_file *> hpglData;
};

#endif // HPGLLISTMODEL_H
