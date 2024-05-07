#include "GenericButton.h"

GenericButton::GenericButton(QWidget *parent) : QPushButton(parent) {
    setCursor(Qt::PointingHandCursor);
    setStyleSheet("border:none;border-radius:100px;");
}
