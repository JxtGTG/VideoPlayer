#include "widget.h"
#include "ui_widget.h"
#include <string>
#include <QFileDialog>
#include "playerframe.h"
#include "ui_coloroptiondialog.h"
#include "coloroptiondialog.h"
#include <QFileDialog>
#include "timestamps.h"

using std::to_string;
using std::string;


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget),player1(parent, QMediaPlayer::VideoSurface)
{
    ui->setupUi(this);
    playerindex = 0;
    playernumbers = 0;
    player = new ThePlayer;
    player->setVideoOutput(ui->videoWidget);
    dialog=new ColorOptionDialog();
    //Set video progress bar
    connect(player,&QMediaPlayer::durationChanged,ui->playerslider,&QSlider::setMaximum);
    connect(player,&QMediaPlayer::positionChanged,ui->playerslider,&QSlider::setValue);
    connect(ui->playerslider,&QSlider::sliderMoved,player,&QMediaPlayer::setPosition);

    //Set volume progress bar
    connect(player,&QMediaPlayer::volumeChanged,ui->volumeslider,&QSlider::setValue);
    connect(ui->volumeslider,&QSlider::sliderMoved,player,&QMediaPlayer::setVolume);
    connect (player,SIGNAL (stateChanged(QMediaPlayer::State)), this, SLOT (volumeStateChanged()));

    connect(dialog->ui->brightnessSlider,&QSlider::sliderMoved,ui->videoWidget,&VideoWidget::setBrightness);
    connect(dialog->ui->contrastSlider,&QSlider::sliderMoved,ui->videoWidget,&VideoWidget::setContrast);
    connect(dialog->ui->hueSlider,&QSlider::sliderMoved,ui->videoWidget,&VideoWidget::setHue);
    connect(dialog->ui->sturationSlider,&QSlider::sliderMoved,ui->videoWidget,&VideoWidget::setSaturation);

    //Detect video status and change button icon
    QTimer *mTimer = new QTimer(nullptr);
    mTimer->setInterval(100);
    mTimer->start();
    connect( mTimer, SIGNAL (timeout()), SLOT(volumeStateChanged()));
    connect (mTimer, SIGNAL (timeout()),SLOT (updateduration()));
    connect (mTimer, SIGNAL (timeout()),SLOT (endduration()));
    connect (player, SIGNAL (stateChanged(QMediaPlayer::State)), this, SLOT (playerStateChanged()));

    pFrame = new PlayerFrame();
    player1.setVideoOutput(pFrame);
    timestamps_layout = new Timestamps();
    timestamps_layout->set_player(player);
   
     player->connect(player, SIGNAL(updated_video()), timestamps_layout, SLOT(load_from_file()));
    QWidget* timestamps = new QWidget();
    timestamps->setLayout(timestamps_layout);
     ui->s2->setWidget(timestamps);
      timestamps_layout->set_stamp_adder(ui->stamp_comment,ui->stamp_time);


}

Widget::~Widget(){
    delete ui;
}



//slots

void Widget::on_pause_clicked(){
    if(playernumbers == 0){
        return;
    }
    
    switch (player->state())
    {
        case QMediaPlayer::State::PausedState:
            player->play(); // starting playing again...
            ui->pause->setIcon(QIcon(":/icon/pause.png"));
            break;
        default:
            player->pause();
            ui->pause->setIcon(QIcon(":/icon/start.png"));
            break;
    }
}

void Widget::on_pushButton_4_clicked()
{
    if(ui->playList->isVisible()){
        ui->playList->setVisible(false);
        ui->pushButton_4->setIcon(QIcon(":/icon/shrink.png"));
    }
    else{
        ui->playList->setVisible(true);
        ui->pushButton_4->setIcon(QIcon(":/icon/spread.png"));
    }
}


void Widget::on_pushButton_7_clicked()
{
    if(ui->stamp->isVisible()){
        ui->stamp->setVisible(false);
        ui->pushButton_7->setIcon(QIcon(":/icon/up.png"));
    }
    else{
        ui->stamp->setVisible(true);
        ui->pushButton_7->setIcon(QIcon(":/icon/down.png"));
    }
}

void Widget::on_fullscreen_clicked(){
    ui->videoWidget->setFullScreen(true);
}


void Widget::on_mute_clicked(){
    switch (player->volume())
    {
        case 0:
            player->setVolume(20);
            ui->mute->setIcon(QIcon(":/icon/volumeHigh.png"));
            break;
        default:
            player->setVolume(0);
            ui->mute->setIcon(QIcon(":/icon/volumeDisable.png"));
            break;
    }
}


void Widget::on_backward_clicked(){
	if(playernumbers == 0){
        return;
    }
    qint64 backward = player->position();
    backward = backward - 5000;
    player->setPosition(backward);
}


void Widget::on_forward_clicked(){
	if(playernumbers == 0){
        return;
    }
    qint64 forward = player->position();
    forward = forward + 5000;
    player->setPosition(forward);
}


void Widget::on_speed_clicked(){
	if(playernumbers == 0){
        return;
    }
    player->setPlaybackRate(2);
    QMessageBox::question(
        nullptr,
        QString("Tomeo"),
        QString("doSetRate: Audio device or filter does not support rate. "
                "Falling back to previous value."),
        QMessageBox::Yes);
}


void Widget::playerStateChanged (){
    switch (player->state()) {
        case QMediaPlayer::State::PausedState:
            ui->pause->setIcon(QIcon(":/icon/start.png"));
            break;
        default:
            ui->pause->setIcon(QIcon(":/icon/pause.png"));
            break;
    }
    switch (player->volume()) {
        case 0:
            ui->mute->setIcon(QIcon(":/icon/volumeDisable.png"));
            break;
        default:
            ui->mute->setIcon(QIcon(":/icon/volumeHigh.png"));
            break;
    }
}


void Widget::volumeStateChanged (){
    switch (player->volume()) {
        case 0:
            ui->mute->setIcon(QIcon(":/icon/volumeDisable.png"));
            break;
        default:
            ui->mute->setIcon(QIcon(":/icon/volumeHigh.png"));
            break;
    }
}

void Widget::on_next_clicked() {
    if(playernumbers == 0){
        return;
    }
    if(playerindex == playernumbers-1){
        playerindex =  0;
    }
    else {
         playerindex= playerindex+1;
    }
    TheButtonInfo* button = player->getButtons()->at(playerindex)->info;
    player->jumpTo(button);
}

// Control the rate of the video
void Widget::on_comboBox_activated(int rate)
{
    qreal nowrate = 0;
    switch (rate) {
        case 0:
        {
            nowrate = 1;
            break;
        }
    case 1:
        {
            nowrate = 2;
            break;
        }
    case 2:
        {
            nowrate = 4;
            break;
        }
    case 3:
        {
            nowrate = 0.5;
            break;
        }


    }
        player->setPlaybackRate(nowrate);
}



void Widget::getbuttonindex(int index){
    QString qString;
    qDebug()<<qString.number(index);
    playerindex=index;
}
//end slots

// void Widget::setVideoTitle(int index){
//     QString title = player->getButtons()->at(index)->info->videoname;
//     ui->videoname->setText(title);
//     playertitle=title;
//     qDebug()<<playertitle;

// }


//function
std::vector<TheButtonInfo> Widget::getInfoIn (std::string loc) {
    std::vector<TheButtonInfo> out =  std::vector<TheButtonInfo>();
    QDir dir(QString::fromStdString(loc) );
    QDirIterator it(dir);

    while (it.hasNext()) {

        QString f = it.next();

            if (f.contains("."))

#if defined(_WIN32)
            if (f.contains(".mp4")) { // windows
#else
            if (f.contains(".wmv") || f.contains("MOV"))  { // mac/linux
#endif

            QString thumb = f.left( f .length() - 4) +".png";
            if (QFile(thumb).exists()) { // if a png thumbnail exists
                QImageReader *imageReader = new QImageReader(thumb);
                    QImage sprite = imageReader->read(); // read the thumbnail
                    if (!sprite.isNull()) {
                        QIcon* ico = new QIcon(QPixmap::fromImage(sprite)); // voodoo to create an icon for the button
                        QUrl* url = new QUrl(QUrl::fromLocalFile( f )); // convert the file location to a generic url
                        out . push_back(TheButtonInfo( url , ico  ) );
                    }
                    else
                        qDebug() << "warning: skipping video because I couldn't process thumbnail " << thumb << endl;
            }
            else
                qDebug() << "warning: skipping video because I couldn't find thumbnail " << thumb << endl;
        }
    }
    qDebug()<<out.size();
    playernumbers = out.size();
    return out;
}

void Widget::getVideo(const std::string dirName) {
    // let's just check that Qt is operational first
    qDebug() << "Qt version: " << QT_VERSION_STR << endl;

    //开始上传视频文件
    // collect all the videos in the folder

    videoList = getInfoIn(dirName);

    if (videoList.size() == 0) {
        const int result = QMessageBox::question(
                    nullptr,
                    QString("Tomeo"),
                    QString("no videos found! download, unzip, and add command line argument to \"quoted\" file location. Download videos from Tom's OneDrive?"),
                    QMessageBox::Yes |
                    QMessageBox::No );

        switch( result ) {
        case QMessageBox::Yes:
          QDesktopServices::openUrl(QUrl("https://leeds365-my.sharepoint.com/:u:/g/personal/scstke_leeds_ac_uk/EcGntcL-K3JOiaZF4T_uaA4BHn6USbq2E55kF_BTfdpPag?e=n1qfuN"));
          break;
        default:
            break;
        }
        return;
    }

}

void Widget::updateduration(){
    qint64 seconds = player->position()/1000;


     string stringData;
     int minutes = 0, hours = 0;


    if (hours > 9){
        stringData = to_string(hours) + ":";
    }else{
        stringData = to_string(hours) + "0:";
    }

    if((minutes = seconds / 60) > 0){
        seconds -= minutes * 60;
        if((hours = minutes / 60) > 0){
            minutes -= hours * 60;
        }
    }
    if(minutes > 9){
         stringData += to_string(minutes) + ":";
    }else{
        stringData += "0" + to_string(minutes) + ":";
    }
    if(seconds > 9){
         stringData += to_string(seconds);
    }else{
        stringData += "0" + to_string(seconds);
    }
    stringData = stringData + " /";

    ui->time->setText(QString::fromStdString(stringData));
}


void Widget::endduration(){
    qint64 seconds = player->duration()/1000;


     string stringData;
     int minutes = 0, hours = 0;


    if (hours > 9){
        stringData = to_string(hours) + ":";
    }else{
        stringData = to_string(hours) + "0:";
    }

    if((minutes = seconds / 60) > 0){
        seconds -= minutes * 60;
        if((hours = minutes / 60) > 0){
            minutes -= hours * 60;
        }
    }
    if(minutes > 9){
         stringData += to_string(minutes) + ":";
    }else{
        stringData += "0" + to_string(minutes) + ":";
    }
    if(seconds > 9){
         stringData += to_string(seconds);
    }else{
        stringData += "0" + to_string(seconds);
    }

    ui->endTime->setText(QString::fromStdString(stringData));
}
//end function


void Widget::on_groupBox_clicked()
{

}


void Widget::GetFrame(QPixmap pix)
{
    player1.pause();
    pixmap = pix;
}



void Widget::on_pushButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(this,"Choose videofile..","","*.mp4;*.mp3");
    QFile f(path);
    QFileInfo fileInfo(f.fileName());
    QString filename = fileInfo.fileName();

    player->setMedia(QUrl::fromLocalFile(path));

    player1.setMedia(QUrl::fromLocalFile(path));

    connect(pFrame, SIGNAL(fnSurfaceStopped(QPixmap)),
            this, SLOT(GetFrame(QPixmap)),Qt::QueuedConnection);

    connect(this, SIGNAL(fnClearPixmap()),
            pFrame, SLOT(fnClearPixmap()),Qt::QueuedConnection);
    playernumbers=1;
    player->play();
    playOne();
    //==================
}

void Widget::playOne(){
    //single file in the list
    //delete all file in list
    QList<QPushButton*> btns =  ui->listWidget->findChildren<QPushButton*>();
    foreach(QPushButton* btn, btns){
        delete btn;
    }
    delete ui->listWidget->layout();
    buttonList.clear();
}

void Widget::playList() {
    // the QMediaPlayer which controls the playback
    QList<QPushButton*> btns =  ui->listWidget->findChildren<QPushButton*>();
    foreach(QPushButton* btn, btns){
        delete btn;
    }
    delete ui->listWidget->layout();
    QVBoxLayout *layout = new QVBoxLayout();
    ui->listWidget->setLayout(layout);
    buttonList.clear();
    // create the six buttons
    for ( int i = 0; i < playernumbers; i++ ) {
        TheButton *button = new TheButton(ui->listWidget);
        button->index = i;
        button->connect(button, SIGNAL(jumpTo(TheButtonInfo* )), player, SLOT (jumpTo(TheButtonInfo*))); // when clicked, tell the player to play.
        button->connect(button, SIGNAL(returnindex(int)), this, SLOT (getbuttonindex(int)));
        button->connect (button, SIGNAL(returnindex(int)), this, SLOT (setVideoTitle(int)));
        buttonList.push_back(button);
        button->setFlat(true);
        button->setFocusPolicy(Qt::NoFocus);
        layout->addWidget(button);
        button->init(&videoList.at(i));
    }
    player->setContent(&buttonList, &videoList);
}

void Widget::on_open_clicked(){
    QString array = QFileDialog::getExistingDirectory(this,"need to play file","C:/Users/loulo/Desktop/19 UI/videos");
    if(array.length() <= 0)
        return;
    std::string dirName = array.toStdString();
    getVideo(dirName);
    playList();
    playerindex = 0;
    player->setMedia(*(buttonList.at(0)->info)->url);
    player1.setMedia(*(buttonList.at(0)->info)->url);
    connect(pFrame, SIGNAL(fnSurfaceStopped(QPixmap)),
            this, SLOT(GetFrame(QPixmap)),Qt::QueuedConnection);

    connect(this, SIGNAL(fnClearPixmap()),
            pFrame, SLOT(fnClearPixmap()),Qt::QueuedConnection);
    player->play();
    // setVideoTitle(playerindex);

}

void Widget::on_pushButton_2_clicked()
{
     dialog->show();
}


void Widget::on_pushButton_3_clicked()
{
    if(state){
    QPalette bgpal = palette();
    bgpal.setColor (QPalette::Background, QColor (79, 79, 79));
    //bgpal.setColor (QPalette::Background, Qt::transparent);
    bgpal.setColor (QPalette::Foreground, QColor (255, 255, 255)); setPalette (bgpal);
    ui->bottomwidget->setStyleSheet("background-color: rgb(255,215,0)");
    ui->stamp->setStyleSheet("background-color: rgb(255,106,106)");
    state = 0;
    }
    else{
        QPalette bgpal = palette();
        bgpal.setColor (QPalette::Background, QColor (184, 212, 184));
        //bgpal.setColor (QPalette::Background, Qt::transparent);
        bgpal.setColor (QPalette::Foreground, QColor (255,255,255,255)); setPalette (bgpal);
        ui->bottomwidget->setStyleSheet("background-color: rgb(255,193,193)");
        ui->listWidget->setStyleSheet("background-color: rgb(0,139,139)");
        ui->stamp->setStyleSheet("background-color: rgb(135,206,250)");
        state = 1;
    }
}


//点击按钮截图保存
void Widget::on_pushButton_5_clicked()
{
    QDesktopWidget *desk = QApplication::desktop();
    QScreen * screen = QGuiApplication::primaryScreen();
    QPixmap p = screen->grabWindow(ui->videoWidget->winId());

    QString file = QFileDialog::getSaveFileName(this, "保存截图",".","图片(*.jpg)");
    p.save(file);
}


void Widget::on_pushButton_6_clicked()
{
     qDebug() << "6"  << endl;
    timestamps_layout->add_timestamp();
     qDebug() << "6"  << endl;
}




void Widget::on_user_clicked() {
    QMessageBox::question(
        nullptr,
        QString("Tomeo"),
        QString("In the future can be used by users to log in or register,"
                " can enhance the video player personalization. Not developed yet."),
        QMessageBox::Yes);
}


