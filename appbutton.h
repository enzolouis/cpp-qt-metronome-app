#ifndef APPBUTTON_H
#define APPBUTTON_H

#include "HoverButton.h"
#include <QIcon>
#include <QSize>

class AppButton : public HoverButton {
    Q_OBJECT

public:
    AppButton(const QString &icon_name, const QSize &icon_size, const QSize &fixed_size, const QString &bg, const QString &fg, QWidget *parent = nullptr);
};

#endif // APPBUTTON_H
