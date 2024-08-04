#ifndef QMLUTILS_H
#define QMLUTILS_H

#include <QObject>

class QMLUtils : public QObject
{
    Q_OBJECT

public:
    explicit QMLUtils(QObject *parent = nullptr);

    Q_INVOKABLE QString clipboardGetText();

public slots:
    void clipboardSetText(const QString &str);

signals:
};

#endif // QMLUTILS_H
