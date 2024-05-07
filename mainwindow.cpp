#include "mainwindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSlider>
#include <QTime>
#include <QTimer>
//#include <QSoundEffect>

#include <iostream>
#include <iomanip>

#include "GenericButton.h"
#include "HoverButton.h"
#include "AppButton.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    pause = true;
    bpm = 200;
    spb = round(1.0/(bpm/60.0) * 1000.0) / 1000.0;
    mspb = int(spb * 1000);

    button_pause = new AppButton("play.png", QSize(100, 100), QSize(100, 100), "#fe0000", "#262729", this);
    connect(button_pause, &QPushButton::clicked, this, &MainWindow::pause_or_play);

    bpm_spb_label = new QLabel(QString("<span style='font-size:26px'>%1</span><span style='font-size:15px;font-weight:600;color:#bdc3c7;'>BPM </span><span> — </span><span style='font-size:26px'>%2</span><span style='font-size:15px;font-weight:600;color:#bdc3c7;'>SPB</span>").arg(bpm).arg(spb));

    bar = new QProgressBar();
    bar->setTextVisible(false);
    bar->setMaximum(mspb);

    button_decrease = new GenericButton();
    button_decrease->setIcon(QIcon("minus.png"));
    button_decrease->setIconSize(QSize(40, 40));
    connect(button_decrease, &QPushButton::clicked, this, &MainWindow::decrease_slider);

    button_increase = new GenericButton();
    button_increase->setIcon(QIcon("plus.png"));
    button_increase->setIconSize(QSize(40, 40));
    connect(button_increase, &QPushButton::clicked, this, &MainWindow::increase_slider);

    slider = new QSlider(Qt::Horizontal);
    slider->setMinimum(40);
    slider->setMaximum(218);
    connect(slider, &QSlider::valueChanged, this, &MainWindow::changed);
    slider->setValue(218);

    QHBoxLayout *button_layout = new QHBoxLayout;
    button_layout->addWidget(button_decrease);
    button_layout->addWidget(slider);
    button_layout->addWidget(button_increase);

    QVBoxLayout *main_layout = new QVBoxLayout;
    main_layout->addWidget(button_pause, 0, Qt::AlignHCenter);
    main_layout->addLayout(button_layout, 0);
    main_layout->addWidget(bpm_spb_label, 0, Qt::AlignHCenter);
    main_layout->addWidget(bar, 0);

    QWidget *central_widget = new QWidget;
    central_widget->setLayout(main_layout);
    setCentralWidget(central_widget);

    count = QTime(0, 0, 0, 0);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::addtime);

    bar_timer = new QTimer(this);
    connect(bar_timer, &QTimer::timeout, this, &MainWindow::addbarwidth);

    // Initialisation du son
    //tick_sound = new QSoundEffect();
    //tick_sound->setSource(QUrl::fromLocalFile("tick.wav"));
    //tick_sound->setLoopCount(1);
    //tick_sound->setVolume(0.1);

    setStyleSheet("QWidget { background:#262729; } QLabel { font-family:Courier; color:white; font-size:30px; font-weight:bold; } QPushButton {} QProgressBar { border-radius: 3px; padding:5px; text-align:right; font-size:30px; color:white; font-weight:bold; } QProgressBar { text-align:right; color:#8c7ae6; background:white; font-weight:bold; padding:0px; } QProgressBar::chunk { background-color: #8c7ae6; }");

    // Affichage de la fenêtre principale
    setGeometry(800, 250, 200, 350);
    setFixedSize(250, 350);
    setWindowTitle("Métronome");
    setWindowIcon(QIcon("playIcon.png"));

    show();
}

MainWindow::~MainWindow()
{
    delete button_pause;
    delete bpm_spb_label;
    delete bar;
    delete button_decrease;
    delete button_increase;
    delete slider;
    delete timer;
    //delete tick_sound;
}

void MainWindow::pause_or_play()
{
    pause = !pause;
    if (pause)
    {
        bar_timer->stop();
        timer->stop();
        bar->setValue(0);
        count = QTime(0, 0, 0, 0);
        button_pause->setIcon(QIcon("play.png"));
    }
    else
    {
        button_pause->setIcon(QIcon("pause.png"));
        launch_progress_bar();
        timer->start(mspb);
    }
}

void MainWindow::decrease_slider()
{
    slider->setValue(slider->value() - 1);
}

void MainWindow::increase_slider()
{
    slider->setValue(slider->value() + 1);
}

void MainWindow::changed(int value)
{
    if (!pause)
    {
        pause_or_play();
    }

    bpm = value;
    spb = round(1.0/(bpm/60.0) * 1000.0) / 1000.0;
    mspb = int(spb * 1000);

    bpm_spb_label->setText(QString("<span style='font-size:26px'>%1</span><span style='font-size:15px;font-weight:600;color:#bdc3c7;'>BPM </span><span> — </span><span style='font-size:26px'>%2</span><span style='font-size:15px;font-weight:600;color:#bdc3c7;'>SPB</span>").arg(bpm).arg(spb));
    bar->setMaximum(mspb);

    QHash<QPair<int, int>, QPair<QString, QString>> misc = {
                                                            {QPair<int, int>(40, 65), QPair<QString, QString>("#d200c8", "rgba(210,0,200, 0.3)")},
                                                            {QPair<int, int>(65, 90), QPair<QString, QString>("#0368ff", "rgba(3,104,255, 0.3)")},
                                                            {QPair<int, int>(90, 115), QPair<QString, QString>("#7600e8", "rgba(118,0,232, 0.3)")},
                                                            {QPair<int, int>(115, 140), QPair<QString, QString>("#00bd39", "rgba(0,189,57, 0.3)")},
                                                            {QPair<int, int>(140, 165), QPair<QString, QString>("#fffc01", "rgba(255,252,1, 0.3)")},
                                                            {QPair<int, int>(165, 190), QPair<QString, QString>("#fe6a00", "rgba(254,106,0, 0.3)")},
                                                            {QPair<int, int>(190, 218), QPair<QString, QString>("#fe0000", "rgba(254,0,0, 0.3)")}};

    for (auto it = misc.begin(); it != misc.end(); ++it)
    {
        if (bpm >= it.key().first && bpm <= it.key().second)
        {
            button_pause->setBackgroundColor(it.value().first);
            QVariantAnimation& transition = const_cast<QVariantAnimation&>(button_pause->getTransition());
            transition.setEndValue(QColor(it.value().first));
            //button_pause->getTransition().setEndValue(QColor(it.value().first));
            //button_pause->setStyleSheet(QString("background-color:%1;").arg(it.value().first));
            bar->setStyleSheet(QString("QProgressBar{background-color:%1;color:white;} QProgressBar::chunk{background-color:%2;}").arg(it.value().second).arg(it.value().first));
            slider->setStyleSheet("QSlider {height:20px;}QSlider::groove:horizontal { border: 1px solid #999999; height: 8px; background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #de3030, stop:1 #58a65e); } QSlider::handle:horizontal { background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #b4b4b4, stop:1 #8f8f8f); border: 1px solid #5c5c5c; width: 30px; margin: -5px 0; border-radius: 15px; }");
            break;
        }
    }
}

void MainWindow::addtime()
{
    count = count.addSecs(1);
    launch_progress_bar();
    //tick_sound->play();
}

void MainWindow::launch_progress_bar()
{
    progress_bar_value = 0;
    bar->setValue(progress_bar_value);
    bar_timer->start(mspb/100);
}

void MainWindow::addbarwidth()
{
    progress_bar_value += mspb/100;
    bar->setValue(progress_bar_value);

    if (progress_bar_value >= mspb) {
        bar_timer->stop();
    }
}
