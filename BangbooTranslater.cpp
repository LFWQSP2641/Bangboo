#include "BangbooTranslater.h"

#include <QBitArray>
#include <QDebug>
#include <QRandomGenerator>

BangbooTranslater::BangbooTranslater(QObject *parent)
    : QThread{ parent }
{
}

void BangbooTranslater::run()
{
    if (mode == TranslateMode::NotSet)
    {
        qFatal() << QStringLiteral("mode is not set.");
        emit translateFinished({});
        return;
    }
    if (input.isEmpty())
    {
        emit translateFinished({});
        return;
    }
    if (mode == Encode)
    {
        const QString result(encode(input.toUtf8()));
        emit translateFinished(result);
    }
    else if (mode == Decode)
    {
        const QString result(decode(input));
        emit translateFinished(result);
    }
}

QString BangbooTranslater::encode(const QByteArray &input) const
{
    const QByteArray bytes(qCompress(input));
    QString result;
    for (int i = 0; i < bytes.size(); ++i)
        for (int b = 0; b < 8; ++b)
        {
            if (bytes.at(i) & (1 << b))
                result.append(QStringLiteral("嗯"));
            else
                result.append(QStringLiteral("呢"));
            if (QRandomGenerator::global()->bounded(2) == 0)
                continue;
            switch (QRandomGenerator::global()->bounded(4))
            {
            case 0:
                result.append(QStringLiteral("？"));
                break;
            case 1:
                result.append(QStringLiteral("！"));
                break;
            case 2:
                result.append(QStringLiteral("……"));
                break;
            case 3:
                result.append(QStringLiteral("，"));
                break;
            default:
                break;
            }
        }
    return result;
}

QByteArray BangbooTranslater::decode(const QString &input)
{
    QBitArray bits(8);
    int bitsIndex(0);
    QByteArray result;
    for (const auto &i : input)
    {
        bool bit;
        if (i == QStringLiteral("嗯"))
            bit = true;
        else if (i == QStringLiteral("呢"))
            bit = false;
        else
            continue;
        bits.setBit(bitsIndex, bit);
        ++bitsIndex;
        if (bitsIndex > 7)
        {
            char byte(0);
            for (int b = 0; b < 8; ++b)
            {
                byte = byte | (bits[b] << b);
            }
            result.append(byte);
            bitsIndex = 0;
        }
    }
    if (bitsIndex != 0 || result.isEmpty())
    {
        emit error(QStringLiteral("输入不正确"));
        return {};
    }
    const QByteArray tResult(qUncompress(result));
    return tResult.isEmpty() ? result : tResult;
}

BangbooTranslater::TranslateMode BangbooTranslater::getMode() const
{
    return mode;
}

void BangbooTranslater::setMode(BangbooTranslater::TranslateMode newMode)
{
    if (mode == newMode)
        return;
    mode = newMode;
    emit modeChanged();
}

QString BangbooTranslater::getInput() const
{
    return input;
}

void BangbooTranslater::setInput(const QString &newInput)
{
    if (input == newInput)
        return;
    input = newInput;
    emit inputChanged();
}
