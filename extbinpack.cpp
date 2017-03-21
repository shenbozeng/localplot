#include "extbinpack.h"

ExtBinPack::ExtBinPack(hpglListModel *model)
{
    cancelFlag = false;
    hpglModel = model;
}

ExtBinPack::~ExtBinPack()
{
    //
}

void ExtBinPack::process()
{
    QSettings settings;
    rbp::ShelfBinPack packer;
    QPersistentModelIndex index;
    QGraphicsItemGroup * itemGroup;

    hpglModel->sort();

    int initX, initY;
    QLineF widthLine = MainWindow::get_widthLine();
    initX = widthLine.p2().y() - widthLine.p1().y();
    initY = 0;

    for (int i = 0; i < hpglModel->rowCount(); ++i)
    {
        if (cancelFlag)
        {
            statusUpdate("Cancelling auto arrange.", Qt::darkRed);
            emit finished();
            return;
        }
        index = hpglModel->index(i);
        itemGroup = NULL;
        QMutex * mutex;
        hpglModel->dataGroup(index, mutex, itemGroup);
        if (!mutex->tryLock())
        {
            qDebug() << "Mutex already locked, giving up.";
            emit finished();
            return;
        }

        if (itemGroup == NULL)
        {
            qDebug() << "Error: itemgroup is null in scenescalecontainselected().";
            mutex->unlock();
            emit finished();
            return;
        }

        initY += qMax(itemGroup->boundingRect().width(), itemGroup->boundingRect().height());

        mutex->unlock();
    }

    packer.Init(initX, initY, true);

    for (int i = 0; i < hpglModel->rowCount(); ++i)
    {
        if (cancelFlag)
        {
            statusUpdate("Cancelling auto arrange.", Qt::darkRed);
            emit finished();
            return;
        }
        index = hpglModel->index(i);
        itemGroup = NULL;
        QMutex * mutex;
        hpglModel->dataGroup(index, mutex, itemGroup);
        if (!mutex->tryLock())
        {
            qDebug() << "Mutex already locked, giving up.";
            emit finished();
            return;
        }

        if (itemGroup == NULL)
        {
            qDebug() << "Error: itemgroup is null in scenescalecontainselected().";
            mutex->unlock();
            emit finished();
            return;
        }

        rbp::Rect thisrect = packer.Insert(itemGroup->boundingRect().width(), itemGroup->boundingRect().height(), rbp::ShelfBinPack::ShelfChoiceHeuristic::ShelfBestHeightFit);

        QRectF rect;
        rect.setX(thisrect.y);
        rect.setY(thisrect.x);
        rect.setWidth(thisrect.height);
        rect.setHeight(thisrect.width);
        emit packedRect(index, rect);

        mutex->unlock();
    }

    emit statusUpdate("Finished arranging files.");
    emit finished();
}

void ExtBinPack::cancel()
{
    cancelFlag = true;
}

void ExtBinPack::statusUpdate(QString _consoleStatus)
{
    emit statusUpdate(_consoleStatus, Qt::black);
}































