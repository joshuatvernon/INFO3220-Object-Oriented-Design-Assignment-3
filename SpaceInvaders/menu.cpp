#include "menu.h"

#include <QPainter>

namespace game {

Menu::Menu(QWidget* parent, QString name, int& playerScore, QList<int> scores, QList<QString> players)
        : gameScore(playerScore) {
    highScores = scores;
    highScoringPlayers = players;

    // Handle edge case where different amounts of scores or players are given
    while (highScores.size() < highScoringPlayers.size()) {
        highScoringPlayers.pop_back();
    }
    while (highScores.size() > highScoringPlayers.size()) {
        highScores.pop_back();
    }

    // If there are less than 5 high scoring players add dummy values
    while (highScores.size() < 5) {
        highScores.append(0);
    }
    while (highScoringPlayers.size() < 5) {
        highScoringPlayers.append("None");
    }

    // BubbleSort both highScores and highScoringPlayers
    for (int i = 0; i < highScores.size(); i++) {
        for (int j = 0; j < highScores.size(); j++) {
            if (i == j) {
                continue;
            }
            if (highScores.at(i) > highScores.at(j)) {
                int tempScore = highScores.at(i);
                highScores.replace(i, highScores.at(j));
                highScores.replace(j, tempScore);

                QString tempPlayer = highScoringPlayers.at(i);
                highScoringPlayers.replace(i, highScoringPlayers.at(j));
                highScoringPlayers.replace(j, tempPlayer);
            }
        }
    }

    makeButtons(parent, name);
}

Menu::~Menu() {
    delete score;
    delete playerName;
    delete playerScoreLabel;
}

void Menu::makeButtons(QWidget* parent, QString name) {
    score = new QPushButton("Scores", parent);
    score->setGeometry(QRect(300, 0, 200, 30));
    score->setVisible(false);
    score->setStyleSheet("background-color: #FFD954");
    QObject::connect(score, SIGNAL(released()), parent, SLOT(showScore()));

    playerName = new QLabel(parent);
    playerName->setGeometry(300, 30, 100, 30);
    playerName->setText(" " + name);
    playerName->setVisible(false);
    playerName->setStyleSheet("background-color: #E3216F");

    playerScoreLabel = new QLabel(parent);
    playerScoreLabel->setGeometry(400, 30, 100, 30);
    playerScoreLabel->setText(" " + QString::number(gameScore));
    playerScoreLabel->setVisible(false);
    playerScoreLabel->setStyleSheet("background-color: #E3216F");

    speed = new QPushButton("Speed", parent);
    speed->setGeometry(QRect(500, 0, 100, 30));
    speed->setVisible(false);
    speed->setStyleSheet("background-color: #FFD954");
    QObject::connect(speed, SIGNAL(released()), parent, SLOT(toggleShowSpeed()));

    slow = new QPushButton("Slow", parent);
    slow->setGeometry(QRect(500, 30, 100, 30));
    slow->setVisible(false);
    slow->setStyleSheet("background-color: green");
    QObject::connect(slow, SIGNAL(released()), parent, SLOT(pressSlow()));

    normal = new QPushButton("Normal", parent);
    normal->setGeometry(QRect(500, 60, 100, 30));
    normal->setVisible(false);
    normal->setStyleSheet("background-color: yellow");
    QObject::connect(normal, SIGNAL(released()), parent, SLOT(pressNormal()));

    fast = new QPushButton("Fast", parent);
    fast->setGeometry(QRect(500, 90, 100, 30));
    fast->setVisible(false);
    fast->setStyleSheet("background-color: orange");
    QObject::connect(fast, SIGNAL(released()), parent, SLOT(pressFast()));

    chaos = new QPushButton("Chaos", parent);
    chaos->setGeometry(QRect(500, 120, 100, 30));
    chaos->setVisible(false);
    chaos->setStyleSheet("background-color: red");
    QObject::connect(chaos, SIGNAL(released()), parent, SLOT(pressChaos()));

    controls = new QPushButton("Controls", parent);
    controls->setGeometry(QRect(0, 0, 100, 30));
    controls->setVisible(false);
    controls->setStyleSheet("background-color: red");
    QObject::connect(controls, SIGNAL(released()), parent, SLOT(pressControls()));

    menu = new QPushButton("Menu", parent);
    menu->setGeometry(QRect(350,  0, 100, 30));
    menu->setVisible(true);
    menu->setStyleSheet("background-color: #FFD954");
    QObject::connect(menu, SIGNAL(released()), parent, SLOT(pauseStart()));

    resume = new QPushButton("Resume", parent);
    resume->setGeometry(QRect(200, 0, 100, 30));
    resume->setVisible(false);
    resume->setStyleSheet("background-color: #FFD954");
    QObject::connect(resume, SIGNAL(released()), parent, SLOT(pauseStart()));

    topScoreLabel1 = new QLabel(parent);
    topScoreLabel1->setGeometry(QRect(400, 60, 100, 30));
    topScoreLabel1->setText(" " + QString::number(highScores.at(0)));
    topScoreLabel1->setVisible(false);
    topScoreLabel1->setStyleSheet("background-color: white");

    topScoreLabel2 = new QLabel(parent);
    topScoreLabel2->setGeometry(QRect(400, 90, 100, 30));
    topScoreLabel2->setText(" " + QString::number(highScores.at(1)));
    topScoreLabel2->setVisible(false);
    topScoreLabel2->setStyleSheet("background-color: white");

    topScoreLabel3 = new QLabel(parent);
    topScoreLabel3->setGeometry(QRect(400, 120, 100, 30));
    topScoreLabel3->setText(" " + QString::number(highScores.at(2)));
    topScoreLabel3->setVisible(false);
    topScoreLabel3->setStyleSheet("background-color: white");

    topScoreLabel4 = new QLabel(parent);
    topScoreLabel4->setGeometry(QRect(400, 150, 100, 30));
    topScoreLabel4->setText(" " + QString::number(highScores.at(3)));
    topScoreLabel4->setVisible(false);
    topScoreLabel4->setStyleSheet("background-color: white");

    topScoreLabel5 = new QLabel(parent);
    topScoreLabel5->setGeometry(QRect(400, 180, 100, 30));
    topScoreLabel5->setText(" " + QString::number(highScores.at(4)));
    topScoreLabel5->setVisible(false);
    topScoreLabel5->setStyleSheet("background-color: white");

    topScoreNameLabel1 = new QLabel(parent);
    topScoreNameLabel1->setGeometry(QRect(300, 60, 100, 30));
    topScoreNameLabel1->setText(" " + highScoringPlayers.at(0));
    topScoreNameLabel1->setVisible(false);
    topScoreNameLabel1->setStyleSheet("background-color: white");

    topScoreNameLabel2 = new QLabel(parent);
    topScoreNameLabel2->setGeometry(QRect(300, 90, 100, 30));
    topScoreNameLabel2->setText(" " + highScoringPlayers.at(1));
    topScoreNameLabel2->setVisible(false);
    topScoreNameLabel2->setStyleSheet("background-color: white");

    topScoreNameLabel3 = new QLabel(parent);
    topScoreNameLabel3->setGeometry(QRect(300, 120, 100, 30));
    topScoreNameLabel3->setText(" " + highScoringPlayers.at(2));
    topScoreNameLabel3->setVisible(false);
    topScoreNameLabel3->setStyleSheet("background-color: white");

    topScoreNameLabel4 = new QLabel(parent);
    topScoreNameLabel4->setGeometry(QRect(300, 150, 100, 30));
    topScoreNameLabel4->setText(" " + highScoringPlayers.at(3));
    topScoreNameLabel4->setVisible(false);
    topScoreNameLabel4->setStyleSheet("background-color: white");

    topScoreNameLabel5 = new QLabel(parent);
    topScoreNameLabel5->setGeometry(QRect(300, 180, 100, 30));
    topScoreNameLabel5->setText(" " + highScoringPlayers.at(4));
    topScoreNameLabel5->setVisible(false);
    topScoreNameLabel5->setStyleSheet("background-color: white");

    controlsLabel = new QLabel(parent);
    controlsLabel->setGeometry(QRect(0, 0, 100, 30));
    controlsLabel->setVisible(false);
    controlsLabel->setStyleSheet("background-color: red");
}

// called when game is paused or unpaused
void Menu::displayMenu(bool paused) {
    if (!paused) {
        closeButtons();
    } else {
        score->setVisible(true);
        speed->setVisible(true);
        controls->setVisible(true);
        resume->setVisible(true);
        menu->setVisible(false);
    }
}

// helper, closes all the opened menus
void Menu::closeButtons() {
    menu->setVisible(true);
    resume->setVisible(false);
    score->setVisible(false);
    speed->setVisible(false);
    slow->setVisible(false);
    normal->setVisible(false);
    fast->setVisible(false);
    chaos->setVisible(false);
    controls->setVisible(false);
    revealPlayerScore(false);
}

// helper function for OpenScore
void Menu::revealPlayerScore(bool open) {
    // recalculate playerScoreLabel
    playerScoreLabel->setText(QString::number(gameScore));
    playerName->setVisible(open);
    playerScoreLabel->setVisible(open);
    // Top scores
    topScoreLabel1->setVisible(open);
    topScoreLabel2->setVisible(open);
    topScoreLabel3->setVisible(open);
    topScoreLabel4->setVisible(open);
    topScoreLabel5->setVisible(open);
    topScoreNameLabel1->setVisible(open);
    topScoreNameLabel2->setVisible(open);
    topScoreNameLabel3->setVisible(open);
    topScoreNameLabel4->setVisible(open);
    topScoreNameLabel5->setVisible(open);
}

void Menu::openScore() {
    if (playerName->isVisible()) {
        revealPlayerScore(false);
    } else {
        revealPlayerScore(true);
    }
}

void Menu::toggleDisplaySpeeds() {
    if (slow->isVisible()) {
        slow->setVisible(false);
        normal->setVisible(false);
        fast->setVisible(false);
        chaos->setVisible(false);
    } else {
        slow->setVisible(true);
        normal->setVisible(true);
        fast->setVisible(true);
        chaos->setVisible(true);
    }
}

void Menu::toggleDisplayControls() {
    if (controlsLabel->isVisible()) {
        controlsLabel->setVisible(false);
    } else {
        controlsLabel->setVisible(true);
    }
}

void Menu::updateTopScores() {

}

void Menu::toggleDisplayLevels() {
//    if (levelsLabels->isVisible()) {
//        levelsLabels->setVisible(false);
//    } else {
//        levelsLabels->setVisible(true);
//    }
}

}
