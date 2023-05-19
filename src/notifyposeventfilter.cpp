#include "notifyposeventfilter.h"

#include <QEvent>

NotifyPosEventFilter::NotifyPosEventFilter(QObject *parent)
  : QObject(parent)
{}

bool
NotifyPosEventFilter::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::Move || event->type() == QEvent::Resize) {
        emit updated();
    }

    return QObject::eventFilter(obj, event);
}
