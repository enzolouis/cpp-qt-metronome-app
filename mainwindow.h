#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QSlider>
#include <QTime>
#include <QTimer>
#include <QProgressBar>

#include "GenericButton.h"
#include "HoverButton.h"
#include "AppButton.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void pause_or_play();
    void decrease_slider();
    void increase_slider();
    void addtime();
    void launch_progress_bar();
    void addbarwidth();

private:
    AppButton *button_pause;
    QLabel *bpm_spb_label;
    QProgressBar *bar;
    GenericButton *button_decrease;
    GenericButton *button_increase;
    QSlider *slider;

    int a;
    int progress_bar_value;
    bool pause;
    int bpm;
    double spb;
    int mspb;
    QTime count;
    QTimer *timer;
    //QSoundEffect *tick_sound;
    QTimer *bar_timer;

    void changed(int value);
};

#endif // MAINWINDOW_H
