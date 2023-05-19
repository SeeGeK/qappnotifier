#include "notifywidget.h"
#include "notifydefs.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QTimer>
#include <QEvent>
#include <QMouseEvent>

using namespace notify_style;

NotifyWidget::NotifyWidget(QWidget *parent, int msec) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    m_titleLabel = new QLabel;
    m_infoLabel  = new QLabel;

    layout->setSpacing(0);
    layout->setMargin(0);
    auto defLabels = [layout](QLabel *lbl) {
        auto f = lbl->font();
        f.setPointSize(NOTIFY_FONT_POINTSIZE);
        lbl->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        lbl->setAttribute(Qt::WA_TranslucentBackground);
        lbl->setFont(f);
        lbl->setWordWrap(true);
        layout->addWidget(lbl);
    };

    defLabels(m_titleLabel);
    defLabels(m_infoLabel);

    setFixedHeight(NOTIFY_HEIGHT);
    setStyleSheet(NOTIFY_INFOSTYLE);

    setAttribute(Qt::WA_DeleteOnClose);
    createAnimation(msec);
}

void NotifyWidget::createAnimation(int msec) {
    m_gdse = new QGraphicsOpacityEffect(this);
    setGraphicsEffect(m_gdse);

    m_animation = new QPropertyAnimation(m_gdse, "opacity");
    m_animation->setStartValue(0.0);
    m_animation->setEndValue(NOTIFY_MAX_OPACITY);
    m_animation->setDuration(NOTIFY_ANIMATION_DURATION);

    m_closeTimer = new QTimer;
    m_closeTimer->setInterval(msec);
    m_closeTimer->setSingleShot(true);

    QObject::connect(m_animation, &QPropertyAnimation::finished, [this](){
        if (m_animation->direction() == QAbstractAnimation::Forward) {
            m_animation->setDirection(QAbstractAnimation::Backward);
            m_closeTimer->start();
        } else {
            this->close();
        }
    });

    connect(m_closeTimer, &QTimer::timeout, m_animation, [this](){m_animation->start();});
    m_animation->setDirection(QAbstractAnimation::Forward);
}

void NotifyWidget::showAnimated() {
    m_animation->start();
    show();
}

void NotifyWidget::closeAnimated() {
    const int CLOSE_DURATION = NOTIFY_ANIMATION_DURATION;
    m_animation->setDuration(CLOSE_DURATION);
    m_animation->stop();
    m_animation->start();
}

NotifyWidget::~NotifyWidget() {
    m_animation->deleteLater();
    m_gdse->deleteLater();
}

void NotifyWidget::setData(const QString &title, const QString &text) {
    if (title.isEmpty()) {
        m_titleLabel->setFixedHeight(0);
        m_infoLabel->setFixedHeight(NOTIFY_HEIGHT);
    } else if (text.isEmpty()) {
        m_titleLabel->setFixedHeight(NOTIFY_HEIGHT);
        m_infoLabel->setFixedHeight(0);
    }
    else {
        m_titleLabel->setFixedHeight(NOTIFY_HEIGHT / 2);
        m_infoLabel->setFixedHeight(NOTIFY_HEIGHT / 2);
    }
    m_titleLabel->setText(title);
    m_infoLabel->setText(text);
}

void NotifyWidget::setType(Notify::MessageType type)
{
    m_type = type;

    switch (m_type) {
        case Notify::Info:      setStyleSheet(NOTIFY_INFOSTYLE); break;
        case Notify::Warning:   setStyleSheet(NOTIFY_WARNINGSTYLE); break;
        case Notify::Error:     setStyleSheet(NOTIFY_CRITICALSTYLE); break;
        case Notify::Critical:  setStyleSheet(NOTIFY_CRITICALSTYLE); break;
    }
}

void NotifyWidget::setTransparentForMouseEvents(bool tme)
{
    m_titleLabel->setAttribute(Qt::WA_TransparentForMouseEvents, tme);
    m_infoLabel->setAttribute(Qt::WA_TransparentForMouseEvents, tme);
    this->setAttribute(Qt::WA_TransparentForMouseEvents, tme);
}

bool NotifyWidget::event(QEvent *e)
{
    switch (e->type()) {
        case QEvent::Enter: {
            int remainingTime = m_closeTimer->remainingTime();
            m_closeTimer->stop();
            m_closeTimer->setInterval(remainingTime < 1000 ? 1000 : remainingTime);
            break;
        }

        case QEvent::Leave:{
            m_closeTimer->start();
            break;
        }

        default:
            break;
    }
    return QWidget::event(e);
}

void NotifyWidget::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton || e->button() == Qt::RightButton) {
        m_closeTimer->stop();
        closeAnimated();
    }
}
