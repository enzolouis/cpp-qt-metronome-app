#include <QEnterEvent>
#include <QEvent>
#include "HoverButton.h"

#include <iostream>

HoverButton::HoverButton(const QString &stylesheet, const QString &bg, const QString &fg, const QString &bg_end, const QString &fg_end, QWidget *parent)
    : GenericButton(parent),
    m_stylesheet(stylesheet),
    m_bg(bg),
    m_fg(fg),
    m_bg_end(bg_end),
    m_fg_end(fg_end)
{
    connect(&transition, &QVariantAnimation::valueChanged, this, &HoverButton::onValueChanged);
    transition.setStartValue(QColor(bg_end));
    transition.setEndValue(QColor(bg));
    transition.setDuration(200);
    upgradeStyleSheet(bg, fg);
}

void HoverButton::onValueChanged(const QVariant &bg) {
    QString fg = (transition.direction() == QAbstractAnimation::Forward) ? m_fg : m_fg_end;
    upgradeStyleSheet(bg.value<QColor>().name(), fg);
}

void HoverButton::upgradeStyleSheet(const QString &bg, const QString &fg, const QString &border) {
    setStyleSheet("*{" + m_stylesheet + "background-color:" + bg + ";color:" + fg + ";border:" + border + ";}");
}

void HoverButton::setBackgroundColor(const QString &bg) {
    m_bg = bg;
}

const QVariantAnimation& HoverButton::getTransition() const {
    return transition;
}

void HoverButton::enterEvent(QEnterEvent *event) {
    transition.setDirection(QAbstractAnimation::Backward);
    transition.start();
    GenericButton::enterEvent(event);
}

void HoverButton::leaveEvent(QEvent *event) {
    transition.setDirection(QAbstractAnimation::Forward);
    transition.start();
    GenericButton::leaveEvent(event);
}
