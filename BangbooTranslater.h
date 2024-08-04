#ifndef BANGBOOTRANSLATER_H
#define BANGBOOTRANSLATER_H

#include <QThread>

class BangbooTranslater : public QThread
{
    Q_OBJECT

public:
    explicit BangbooTranslater(QObject *parent = nullptr);

    enum TranslateMode
    {
        NotSet = 0,
        Decode = -1,
        Encode = 1
    };
    Q_ENUM(TranslateMode)

    BangbooTranslater::TranslateMode getMode() const;
    void setMode(BangbooTranslater::TranslateMode newMode);

    QString getInput() const;
    void setInput(const QString &newInput);

protected:
    void run() override;

    BangbooTranslater::TranslateMode mode = NotSet;
    QString input;

    QString encode(const QByteArray &input) const;
    QByteArray decode(const QString &input);

signals:
    void modeChanged();

    void inputChanged();

    void translateFinished(const QString &result);

    void error(const QString &msg);

private:
    Q_PROPERTY(BangbooTranslater::TranslateMode mode READ getMode WRITE setMode NOTIFY modeChanged FINAL)
    Q_PROPERTY(QString input READ getInput WRITE setInput NOTIFY inputChanged FINAL)
};

#endif // BANGBOOTRANSLATER_H
