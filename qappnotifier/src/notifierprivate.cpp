#include "notifierprivate.h"
#include "notifydefs.h"
#include "notifywidget.h"

#include "qappnotifier/notifier.h"

#include <QDebug>
#include <QDialog>
#include <QLabel>
#include <QPoint>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>
#include <QDesktopWidget>

using namespace notify_style;

NotifierPrivate::NotifierPrivate(Notifier *q_ptr, QWidget *rootWidget)
  : q_ptr(q_ptr)
  , m_filterEvent(new NotifyPosEventFilter(q_ptr))
{
    Q_ASSERT(rootWidget);

    QObject::connect(rootWidget, &QObject::destroyed, q_ptr, &QObject::deleteLater);

    applyRootWidget(rootWidget);

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

void
NotifierPrivate::applyRootWidget(QWidget *w)
{
    resetEventFilter();

    if (w) {
        m_rootWidget = w;
    }

    updateEventFilter();
}

Notify::Align
NotifierPrivate::getAlign() const
{
    return m_align;
}

void
NotifierPrivate::setAlign(const Notify::Align &align)
{
    m_align = align;
}


NotifyWidget *
NotifierPrivate::createNotifyWidget(const QString &title, const QString &text,
                                    Notify::MessageType type, int msec)
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
        updateNotifiersPositions();
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

    QObject::disconnect(m_connection);

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

    m_connection = QObject::connect(m_filterEvent, &NotifyPosEventFilter::updated,
                                    q, [this](){updateNotifiersPositions();});
}

void
NotifierPrivate::p_notify(const QString &title, const QString &text, Notify::MessageType type,
                          int msec)
{
    Q_Q(Notifier);

    auto notifyWidget = createNotifyWidget(title, text, type, msec);
    notifyWidget->showAnimated();
    updateNotifiersPositions();
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
NotifierPrivate::updateNotifiersPositions()
{
    Q_Q(Notifier);

    int x = 0;
    int y = 0;

    auto wrect = m_rootWidget ? m_rootWidget->rect()
                              : wholeDisplayGeometry();

    if (m_align == Notify::Left) {
        x = NOTIFY_ROOT_HOFFSET;
        y = wrect.height() - m_notifyWidget->height() - NOTIFY_ROOT_VOFFSET;
    } else {
        x = wrect.width() - m_notifyWidget->width() - NOTIFY_ROOT_HOFFSET;
        y = wrect.height() - m_notifyWidget->height() - NOTIFY_ROOT_VOFFSET;
    }

    m_notifyWidget->setGeometry(x, y, 0, 0);
}


void
NotifierPrivate::enableCloseOnMouseClick(bool enable)
{
    m_transparentForMouse = !enable;
    m_notifyWidget->setAttribute(Qt::WA_TransparentForMouseEvents,
                                 m_transparentForMouse);
}

bool
NotifierPrivate::isEnabledCloseOnMouseClick() const
{
    return m_transparentForMouse;
}

void
NotifierPrivate::clear()
{
    for (auto w = m_notifyList.begin(); w != m_notifyList.end(); w++) {
        (*w)->closeAnimated();
    }
}
