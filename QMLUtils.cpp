#include "QMLUtils.h"

#include <QClipboard>
#include <QGuiApplication>

QMLUtils::QMLUtils(QObject *parent)
    : QObject{ parent }
{
}

QString QMLUtils::clipboardGetText()
{
    return QGuiApplication::clipboard()->text();
}

void QMLUtils::clipboardSetText(const QString &str)
{
    QGuiApplication::clipboard()->setText(str);
}
