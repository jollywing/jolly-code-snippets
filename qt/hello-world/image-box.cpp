
#include "image-box.h"
#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>
#include <QPushButton>
#include <QProgressBar>

ImageBox::ImageBox(QWidget *parent)
{
    QVBoxLayout * layout = new QVBoxLayout(this);
    this->setLayout(layout);

    QVBoxLayout * topMain = new QVBoxLayout(this);
    layout->addLayout(topMain);
    QPixmap pixmap("emacs-qt.png");
    label = new QLabel(this);   // must set the label's parent with this, otherwise it won't display
    label->setPixmap(pixmap);
    // label->setText("Hello, QT!");
    // label->setGeometry(5, 10, 590, 500);
    topMain->addWidget(label);

    QHBoxLayout *bottomBar = new QHBoxLayout(this);
    layout->addLayout(bottomBar);

    QPushButton * playButton = new QPushButton("Play", this);
    QPushButton * fullscreenButton = new QPushButton("full screen", this);
    QProgressBar * progressBar = new QProgressBar(this);
    bottomBar->addWidget(playButton);
    bottomBar->addWidget(progressBar);
    bottomBar->addWidget(fullscreenButton);
}

ImageBox::~ImageBox()
{
    if(label){
        delete label;
        label = NULL;
    }
}
