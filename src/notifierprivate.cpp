#include <QDebug>
#include <QDialog>
#include <QLabel>
#include <QPoint>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>

#include "../include/notifierprivate.h"
#include "../include/notifydefs.h"
#include "../include/notifywidget.h"

#include "../notifier.h"
#include <QDesktopWidget>

NotifierPrivate::NotifierPrivate(Notifier *q_ptr)
  : q_ptr(q_ptr)
{}

void NotifierPrivate::initialize(QWidget *w)
{
    Q_ASSERT(w);

    Q_Q(Notifier);
    m_filterEvent = new NotifyPosEventFilter(q);
    setRootWidget(w);
    initialNotifyWidget();
    QObject::connect(q, &Notifier::notify,
                     [this](const QString &title, const QString &text, Notify::NotifyType type,
                            int msec) { p_notify(title, text, type, msec); });

    QObject::connect(q, &Notifier::updatePosition, [this]() { updatePosition(); });
}

void
NotifierPrivate::setRootWidget(QWidget *w)
{
    resetEventFilter();

    if (w) {
        m_rootWidget = w;
    }

    updateEventFilter();
}

void
NotifierPrivate::initialNotifyWidget()
{
    m_notifyWidget = new QWidget(m_rootWidget);
    m_notifyWidget->setFixedWidth(NOTIFY_WIDTH);
    m_notifyLayout = new QVBoxLayout(m_notifyWidget);
    m_notifyLayout->setMargin(0);
    m_notifyLayout->setSpacing(NOTIFY_SPACING);
    m_notifyWidget->setAttribute(Qt::WA_TranslucentBackground);

    if (!m_rootWidget) {
        m_notifyWidget->setWindowFlags(Qt::FramelessWindowHint |
                                       Qt::Tool |
                                       Qt::WindowStaysOnTopHint);
        m_notifyWidget->setWindowModality(Qt::WindowModal);
    }
}

NotifyWidget *
NotifierPrivate::createNotifyWidget(const QString &title, const QString &text,
                                    Notify::NotifyType type, int msec)
{
    auto widget = new NotifyWidget(nullptr, msec);
    widget->setData(title, text);
    widget->setType(type);

    m_notifyList.append(widget);
    m_notifyLayout->addWidget(widget);

    int addH = (m_notifyLayout->count() - 1) * NOTIFY_SPACING;
    m_notifyWidget->setFixedHeight(m_notifyLayout->count() * NOTIFY_HEIGHT + addH);

    if (NOTIFY_MAX_VISIBLE && (m_notifyList.size() > NOTIFY_MAX_VISIBLE)) {
        m_notifyList.takeFirst()->close();
    }

    QObject::connect(widget, &QWidget::destroyed, m_notifyWidget, [&, this, widget]() {
        Q_Q(Notifier);

        m_notifyList.removeOne(widget);
        int addH = m_notifyList.size() ? (m_notifyList.size() - 1) * NOTIFY_SPACING : 0;
        m_notifyWidget->setFixedHeight(m_notifyList.size() * NOTIFY_HEIGHT + addH);
        q->updatePosition();
    });

    widget->setTransparentForMouseEvents(m_transparentForMouse);

    m_notifyWidget->show();
    m_notifyWidget->raise();

    return widget;
}

void
NotifierPrivate::resetEventFilter()
{
    Q_Q(Notifier);

    QObject::disconnect(m_filterEvent, &NotifyPosEventFilter::updated, q,
                        &Notifier::updatePosition);

    if (m_rootWidget) {
        m_rootWidget->removeEventFilter(m_filterEvent);
    }
}

void
NotifierPrivate::updateEventFilter()
{
    Q_Q(Notifier);

    if (m_rootWidget) {
        m_rootWidget->installEventFilter(m_filterEvent);
    }

    QObject::connect(m_filterEvent, &NotifyPosEventFilter::updated, q, &Notifier::updatePosition);
}

void
NotifierPrivate::p_notify(const QString &title, const QString &text, Notify::NotifyType type,
                          int msec)
{
    Q_Q(Notifier);

    auto notifyWidget = createNotifyWidget(title, text, type, msec);
    notifyWidget->showAnimated();
    q->updatePosition();
}

QRect
wholeDisplayGeometry()
{
    QDesktopWidget dw;
    int screenCount = dw.screenCount();

    QRect rect;
    for (int i = 0; i < screenCount; ++i) {
        QRect screenRect     = dw.screen(i)->geometry();
        rect = rect.united(screenRect); // union
    }

    return rect;
}

void
NotifierPrivate::updatePosition()
{
    Q_Q(Notifier);

    int x = 0;
    int y = 0;

    auto wrect = m_rootWidget ? m_rootWidget->rect()
                              : wholeDisplayGeometry();

    if (q->getAlign() == Notifier::Left) {
        x = NOTIFY_ROOT_HOFFSET;
        y = wrect.height() - m_notifyWidget->height() - NOTIFY_ROOT_VOFFSET;
    } else {
        x = wrect.width() - m_notifyWidget->width() - NOTIFY_ROOT_HOFFSET;
        y = wrect.height() - m_notifyWidget->height() - NOTIFY_ROOT_VOFFSET;
    }

    m_notifyWidget->setGeometry(x, y, 0, 0);
}
