#include "../notifier.h"
#include "../include/notifierprivate.h"
#include "../include/notifydefs.h"
#include "../include/notifywidget.h"

Notifier::Notifier(QWidget *rootWidget)
    : QObject(nullptr), m_d_ptr(new NotifierPrivate(this))
{
    Q_ASSERT(rootWidget);

    Q_D(Notifier);
    d->q_ptr = this;
    d->initialize(rootWidget);

    connect(rootWidget, &QObject::destroyed, this, &QObject::deleteLater);
}

Notifier::~Notifier()
{
    Q_D(Notifier);
    delete d;
}

void
Notifier::setTransparentForMouseEvents(bool tme)
{
    Q_D(Notifier);
    d->m_transparentForMouse = tme;
    d->m_notifyWidget->setAttribute(Qt::WA_TransparentForMouseEvents,
                                            d->m_transparentForMouse);
}

void
Notifier::clear()
{
    Q_D(Notifier);
    for (auto w : d->m_notifyList) {
        w->closeAnimated();
    }
}

Notifier::Align
Notifier::getAlign() const
{
    return m_align;
}

void
Notifier::setAlign(const Align &align)
{
    m_align = align;
}

static Notifier *_rnotifier = nullptr;

void
rNotify(const QString &title, const QString &text, Notify::NotifyType type, int msec)
{
    if (_rnotifier) {
        _rnotifier->notify(title, text, type, msec);
    }
}

void
setRNotifier(Notifier *n)
{
    if (n) {
        _rnotifier = n;
    }
}
