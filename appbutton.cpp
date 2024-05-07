#include "AppButton.h"

AppButton::AppButton(const QString &icon_name, const QSize &icon_size, const QSize &fixed_size, const QString &bg, const QString &fg, QWidget *parent)
    : HoverButton("border: none; text-align: center; text-decoration: none; font-size: 16px; border: 2px solid #487EB0;border-radius:"+QString::number(fixed_size.width() / 2)+";", bg, fg, fg, bg, parent)
{
    setIcon(QIcon(icon_name));
    setIconSize(icon_size);
    setFixedSize(fixed_size);
}
