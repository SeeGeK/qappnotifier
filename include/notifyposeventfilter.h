#ifndef NOTIFYPOSEVENTFILTER_H
#define NOTIFYPOSEVENTFILTER_H

#include <QObject>

class NotifyPosEventFilter : public QObject
{
    Q_OBJECT
public:
    explicit NotifyPosEventFilter(QObject *parent = nullptr);
signals:
    void updated();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
};
#endif // NOTIFYPOSEVENTFILTER_H
