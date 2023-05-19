#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QApplication>
#include <QPushButton>

#include <qappnotifier/notifier.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWidget w;
    w.setFixedSize(500, 400);

    auto primLayout = new QHBoxLayout (&w);

    auto buttonLayout = new QVBoxLayout ();
    primLayout->addStretch(1);
    primLayout->addLayout(buttonLayout);

    class Button : public QPushButton
    {
    public:
        Button(QString const &text) : QPushButton(text) { setFixedSize(100, 45); }
    };

    auto button_info = new Button("info");
    auto button_warn = new Button("warning");
    auto button_erro = new Button("error");

    buttonLayout->addWidget(button_info);
    buttonLayout->addWidget(button_warn);
    buttonLayout->addWidget(button_erro);
    buttonLayout->addStretch(1);

    Notifier notifier(&w);

    QObject::connect(button_info, &QPushButton::released,
                     [&notifier]()
                     {
                         notifier.notify("Testing", "Information Notification", Notify::Info, 3000);
                     });

    QObject::connect(button_warn, &QPushButton::released,
                     [&notifier]()
                     {
                         notifier.notify("Testing", "Warning Notification", Notify::Warning,  3000);
                     });

    QObject::connect(button_erro, &QPushButton::released,
                     [&notifier]()
                     {
                         notifier.notify("Testing", "Error Notification", Notify::Error, 3000);
                     });

    w.show();
    return a.exec();
}
