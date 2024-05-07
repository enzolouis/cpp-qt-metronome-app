#ifndef GENERICBUTTON_H
#define GENERICBUTTON_H

#include <QPushButton>

class GenericButton : public QPushButton {
    Q_OBJECT

public:
    GenericButton(QWidget *parent = nullptr);
};

#endif // GENERICBUTTON_H
