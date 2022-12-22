#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFileDialog>
#include <QProcess>
#include <iostream>
#include <QApplication>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QMediaPlaylist>
#include <string>
#include <vector>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QtCore/QFileInfo>
#include <QtWidgets/QFileIconProvider>
#include <QDesktopServices>
#include <QImageReader>
#include <QMessageBox>
#include <QtCore/QDir>
#include <QtCore/QDirIterator>
#include "the_player.h"
#include "the_button.h"
#include <QKeyEvent>
#include <QMouseEvent>
#include <QMediaPlayer>
#include "playerframe.h"
#include "coloroptiondialog.h"
#include <QScreen>
#include "timestamps.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_open_clicked();
    void on_pause_clicked();
    void on_fullscreen_clicked();
    void on_mute_clicked();
    void on_backward_clicked();
    void on_forward_clicked();
    void on_speed_clicked();
    void playerStateChanged ();
    void volumeStateChanged();
    void on_next_clicked();
    void getbuttonindex(int index);
    void on_comboBox_activated(int index);
    void updateduration();
    void endduration();
    void GetFrame(QPixmap pix);

    void on_groupBox_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

Q_SIGNALS:
    void fnClearPixmap();

private:
    Ui::Widget *ui;
    std::vector<TheButtonInfo> videoList;
    std::vector<TheButton*> buttonList;
    ThePlayer *player;
//    QMediaPlayer *mediaPlayer;
    int playerindex;
    int playernumbers;
    int state = 1;
    Timestamps* timestamps_layout;
   

    void Init();
    void playList();
    void playOne();
    void playMovie();
    std::vector<TheButtonInfo> getInfoIn (std::string loc);
    void getVideo(const std::string dirName);
    
    ColorOptionDialog* dialog;
    QMediaPlayer player1;
    PlayerFrame *pFrame;
    QPixmap pixmap;
    int fileCounter = 0;
    QString filename;


};
#endif // WIDGET_H
