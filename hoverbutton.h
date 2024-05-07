#ifndef HOVERBUTTON_H
#define HOVERBUTTON_H

#include <QEnterEvent>
#include <QEvent>


#include "GenericButton.h"
#include <QVariantAnimation>

class HoverButton : public GenericButton {
    Q_OBJECT

public:
    HoverButton(const QString &stylesheet, const QString &bg, const QString &fg, const QString &bg_end, const QString &fg_end, QWidget *parent = nullptr);
    void setBackgroundColor(const QString &bg);
    const QVariantAnimation& getTransition() const;

protected:
    virtual void enterEvent(QEnterEvent *event);
    virtual void leaveEvent(QEvent *event);

private slots:
    void onValueChanged(const QVariant &bg);

private:
    QVariantAnimation transition;
    QString m_stylesheet;
    QString m_bg;
    QString m_fg;
    QString m_bg_end;
    QString m_fg_end;

    void upgradeStyleSheet(const QString &bg, const QString &fg, const QString &border = "none");
};

#endif // HOVERBUTTON_H
