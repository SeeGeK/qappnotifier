#include <QEvent>

#include "../include/notifyposeventfilter.h"

NotifyPosEventFilter::NotifyPosEventFilter(QObject *parent)
  : QObject(parent)
{}

bool
NotifyPosEventFilter::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::Move || event->type() == QEvent::Resize) {
        updated();
    }

    return QObject::eventFilter(obj, event);
}
