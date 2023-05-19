#include "qappnotifier/notifier.h"
#include "notifierprivate.h"
#include "notifydefs.h"
#include "notifywidget.h"

Notifier::Notifier(QWidget *rootWidget)
    : QObject(nullptr), d_ptr(new NotifierPrivate(this, rootWidget))
{
    Q_ASSERT(rootWidget);
}

Notifier::~Notifier()
{
    Q_D(Notifier);
    delete d;
}

void
Notifier::enableCloseOnMouseClick(bool tme)
{
    Q_D(Notifier);
    d->enableCloseOnMouseClick(tme);
}

bool
Notifier::isEnabledCloseOnMouseClick() const
{
    Q_D(const Notifier);
    return d->isEnabledCloseOnMouseClick();
}

void
Notifier::clear()
{
    Q_D(Notifier);
    d->clear();
}

Notify::Align
Notifier::getAlign() const
{
    Q_D(const Notifier);
    return d->getAlign();
}

void
Notifier::setAlign(const Notify::Align &align)
{
    Q_D(Notifier);
    d->setAlign(align);
}

void
Notifier::notify(const QString &title, const QString &text, Notify::MessageType type, int msec)
{
    Q_D(Notifier);
    d->p_notify(title, text, type, msec);
}

namespace Notify
{

static Notifier *_rnotifier = nullptr;

void
setNotifier(Notifier *n)
{
    if (n) {
        _rnotifier = n;
    }
}

void
notify(const QString &title, const QString &text, Notify::MessageType type, int msec)
{
    if (_rnotifier) {
        _rnotifier->notify(title, text, type, msec);
    }
}


}
