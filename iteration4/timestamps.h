#ifndef TIMESTAMPS_H
#define TIMESTAMPS_H

#include <QGridLayout>
#include <QLineEdit>
#include <QDebug>
#include <QFile>
#include <QLabel>
#include "the_player.h"



class Timestamps : public QGridLayout {

Q_OBJECT

public:
    Timestamps();
    ~Timestamps();
    ThePlayer* player;
    QString* vid_location;
    QLineEdit* new_stamp_time;
    QLineEdit* new_stamp_comment;

    void set_player(ThePlayer* player_input);
    void set_vid_location(QString vid_loc_input);
    void set_stamp_adder(QLineEdit* new_stamp_comment,QLineEdit* new_stamp_time);
     void add_timestamp();

private:
    int nr_timestamps;

public slots:
   
    void load_from_file();
};

#endif // TIMESTAMPS_H
