

#include "the_player.h"


void ThePlayer::setContent(std::vector<TheButton*>* b, std::vector<TheButtonInfo>* i) {
    buttons = b;
    infos = i;
    
}


void ThePlayer::playStateChanged (QMediaPlayer::State ms) {
    switch (ms) {
        case QMediaPlayer::State::StoppedState:
            play(); // starting playing again...
            break;
    default:
        break;
    }
}


void ThePlayer::jumpTo (TheButtonInfo* button) {
    setMedia( * button -> url);
    QUrl x = *button->url;
    currently_playing=new QString(x.toString());

}
