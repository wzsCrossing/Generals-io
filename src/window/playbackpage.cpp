#include "playbackpage.h"
#include "ui_playbackpage.h"

PlaybackPage::PlaybackPage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PlaybackPage)
{
    ui->setupUi(this);
}

PlaybackPage::~PlaybackPage()
{
    delete ui;
}
