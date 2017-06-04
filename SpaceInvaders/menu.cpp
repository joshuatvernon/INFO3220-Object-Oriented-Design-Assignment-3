#include "menu.h"

#include <QPainter>
#include <QDebug>

namespace game {

Menu::Menu(QWidget* parent, QString name, int& playerScore, QList<int> scores, QList<QString> players, bool& arrow)
        : gameScore(playerScore), arrowManual(arrow) {
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

    playerNameText = name;

    makeButtons(parent);
}

Menu::~Menu() {
    delete score;
    delete speed;
    delete slow;
    delete normal;
    delete fast;
    delete chaos;
    delete controls;
    delete controlsLabel;
    delete controlsArrow;
    delete controlsWASD;
    delete menu;
    delete resume;
    delete topScoreLabel1;
    delete topScoreLabel2;
    delete topScoreLabel3;
    delete topScoreLabel4;
    delete topScoreLabel5;
    delete topScoreNameLabel1;
    delete topScoreNameLabel2;
    delete topScoreNameLabel3;
    delete topScoreNameLabel4;
    delete topScoreNameLabel5;
}

void Menu::makeButtons(QWidget* parent) {
    score = new QPushButton("Scores", parent);
    score->setGeometry(QRect(300, 0, 200, 30));
    score->setVisible(false);
    score->setStyleSheet("background-color: #FFD954");
    QObject::connect(score, SIGNAL(released()), parent, SLOT(showScore()));

    speed = new QPushButton("Speed", parent);
    speed->setGeometry(QRect(500, 0, 100, 30));
    speed->setVisible(false);
    speed->setStyleSheet("background-color: #FFD954");
    QObject::connect(speed, SIGNAL(released()), parent, SLOT(toggleShowSpeed()));

    slow = new QPushButton("Slow", parent);
    slow->setGeometry(QRect(500, 30, 100, 40));
    slow->setVisible(false);
    slow->setStyleSheet("background-color: green");
    QObject::connect(slow, SIGNAL(released()), parent, SLOT(pressSlow()));

    normal = new QPushButton("Normal", parent);
    normal->setGeometry(QRect(500, 70, 100, 40));
    normal->setVisible(false);
    normal->setStyleSheet("background-color: yellow");
    QObject::connect(normal, SIGNAL(released()), parent, SLOT(pressNormal()));

    fast = new QPushButton("Fast", parent);
    fast->setGeometry(QRect(500, 110, 100, 40));
    fast->setVisible(false);
    fast->setStyleSheet("background-color: orange");
    QObject::connect(fast, SIGNAL(released()), parent, SLOT(pressFast()));

    chaos = new QPushButton("Chaos", parent);
    chaos->setGeometry(QRect(500, 150, 100, 40));
    chaos->setVisible(false);
    chaos->setStyleSheet("background-color: red");
    QObject::connect(chaos, SIGNAL(released()), parent, SLOT(pressChaos()));

    controls = new QPushButton("Controls", parent);
    controls->setGeometry(QRect(700, 0, 100, 30));
    controls->setVisible(false);
    controls->setStyleSheet("background-color: #FFD954");
    QObject::connect(controls, SIGNAL(released()), parent, SLOT(pressControls()));

    controlsLabel = new QLabel(parent);
    controlsLabel->setGeometry(QRect(330, 190, 140, 230));
    controlsLabel->setVisible(false);
    controlsLabel->setStyleSheet("background-color: #3F3131");

    controlsArrow = new QPushButton("Arrows", parent);
    controlsArrow->setGeometry(QRect(350, 270, 100, 30));
    controlsArrow->setVisible(false);
    controlsArrow->setStyleSheet("background-color: #FFD954");
    QObject::connect(controlsArrow, SIGNAL(released()), parent, SLOT(setArrowControls()));

    controlsWASD = new QPushButton("WASD", parent);
    controlsWASD->setGeometry(QRect(350, 370, 100, 30));
    controlsWASD->setVisible(false);
    controlsWASD->setStyleSheet("background-color: #FFD954");
    QObject::connect(controlsWASD, SIGNAL(released()), parent, SLOT(setWASDControls()));

    leftArrowKey = new QPushButton("<", parent);
    leftArrowKey->setGeometry(QRect(359, 240, 22, 22));
    leftArrowKey->setVisible(false);

    rightArrowKey = new QPushButton(">", parent);
    rightArrowKey->setGeometry(QRect(419, 240, 22, 22));
    rightArrowKey->setVisible(false);

    upArrowKey = new QPushButton("^", parent);
    upArrowKey->setGeometry(QRect(389, 210, 22, 22));
    upArrowKey->setVisible(false);

    downArrowKey = new QPushButton("v", parent);
    downArrowKey->setGeometry(QRect(389, 240, 22, 22));
    downArrowKey->setVisible(false);

    wKey = new QPushButton("W", parent);
    wKey->setGeometry(QRect(389, 310, 22, 22));
    wKey->setVisible(false);

    aKey = new QPushButton("A", parent);
    aKey->setGeometry(QRect(359, 340, 22, 22));
    aKey->setVisible(false);

    sKey = new QPushButton("S", parent);
    sKey->setGeometry(QRect(389, 340, 22, 22));
    sKey->setVisible(false);

    dKey = new QPushButton("D", parent);
    dKey->setGeometry(QRect(419, 340, 22, 22));
    dKey->setVisible(false);

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
    topScoreLabel1->setGeometry(QRect(400, 30, 100, 32));
    topScoreLabel1->setVisible(false);

    topScoreLabel2 = new QLabel(parent);
    topScoreLabel2->setGeometry(QRect(400, 62, 100, 32));
    topScoreLabel2->setVisible(false);

    topScoreLabel3 = new QLabel(parent);
    topScoreLabel3->setGeometry(QRect(400, 94, 100, 32));
    topScoreLabel3->setVisible(false);

    topScoreLabel4 = new QLabel(parent);
    topScoreLabel4->setGeometry(QRect(400, 126, 100, 32));
    topScoreLabel4->setVisible(false);

    topScoreLabel5 = new QLabel(parent);
    topScoreLabel5->setGeometry(QRect(400, 158, 100, 32));
    topScoreLabel5->setVisible(false);

    topScoreNameLabel1 = new QLabel(parent);
    topScoreNameLabel1->setGeometry(QRect(300, 30, 100, 32));
    topScoreNameLabel1->setVisible(false);

    topScoreNameLabel2 = new QLabel(parent);
    topScoreNameLabel2->setGeometry(QRect(300, 62, 100, 32));
    topScoreNameLabel2->setVisible(false);

    topScoreNameLabel3 = new QLabel(parent);
    topScoreNameLabel3->setGeometry(QRect(300, 94, 100, 32));
    topScoreNameLabel3->setVisible(false);

    topScoreNameLabel4 = new QLabel(parent);
    topScoreNameLabel4->setGeometry(QRect(300, 126, 100, 32));
    topScoreNameLabel4->setVisible(false);

    topScoreNameLabel5 = new QLabel(parent);
    topScoreNameLabel5->setGeometry(QRect(300, 158, 100, 32));
    topScoreNameLabel5->setVisible(false);

    updateTopScores();
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
    controlsLabel->setVisible(false);
    controlsArrow->setVisible(false);
    controlsWASD->setVisible(false);
    leftArrowKey->setVisible(false);
    rightArrowKey->setVisible(false);
    upArrowKey->setVisible(false);
    downArrowKey->setVisible(false);
    wKey->setVisible(false);
    aKey->setVisible(false);
    sKey->setVisible(false);
    dKey->setVisible(false);
    revealPlayerScore(false);
}

// helper function for OpenScore
void Menu::revealPlayerScore(bool open) {
    // recalculate playerScoreLabel
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
    if (topScoreLabel1->isVisible()) {
        revealPlayerScore(false);
    } else {
        updateTopScores();
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
        controlsArrow->setVisible(false);
        controlsWASD->setVisible(false);
        leftArrowKey->setVisible(false);
        rightArrowKey->setVisible(false);
        upArrowKey->setVisible(false);
        downArrowKey->setVisible(false);
        wKey->setVisible(false);
        aKey->setVisible(false);
        sKey->setVisible(false);
        dKey->setVisible(false);
    } else {
        controlsLabel->setVisible(true);
        controlsArrow->setVisible(true);
        controlsWASD->setVisible(true);
        updateControlKeyColour();
        leftArrowKey->setVisible(true);
        rightArrowKey->setVisible(true);
        upArrowKey->setVisible(true);
        downArrowKey->setVisible(true);
        wKey->setVisible(true);
        aKey->setVisible(true);
        sKey->setVisible(true);
        dKey->setVisible(true);
    }
}

void Menu::updateControlKeyColour() {
    if (arrowManual) {
        leftArrowKey->setStyleSheet("background-color: #43AFF8");
        rightArrowKey->setStyleSheet("background-color: #43AFF8");
        upArrowKey->setStyleSheet("background-color: #43AFF8");
        downArrowKey->setStyleSheet("background-color: #43AFF8");
        wKey->setStyleSheet("background-color: #E2E1E3");
        aKey->setStyleSheet("background-color: #E2E1E3");
        sKey->setStyleSheet("background-color: #E2E1E3");
        dKey->setStyleSheet("background-color: #E2E1E3");
    } else {
        leftArrowKey->setStyleSheet("background-color: #E2E1E3");
        rightArrowKey->setStyleSheet("background-color: #E2E1E3");
        upArrowKey->setStyleSheet("background-color: #E2E1E3");
        downArrowKey->setStyleSheet("background-color: #E2E1E3");
        wKey->setStyleSheet("background-color: #43AFF8");
        aKey->setStyleSheet("background-color: #43AFF8");
        sKey->setStyleSheet("background-color: #43AFF8");
        dKey->setStyleSheet("background-color: #43AFF8");
    }
}

void Menu::updateTopScores() {
    QList<int> overallScores = highScores;
    QList<QString> overallPlayers = highScoringPlayers;
    overallScores.append(gameScore);
    overallPlayers.append(playerNameText);

    // BubbleSort both highScores and highScoringPlayers
    for (int i = 0; i < overallScores.size(); i++) {
        for (int j = 0; j < overallScores.size(); j++) {
            if (i == j) {
                continue;
            }
            if (overallScores.at(i) >= overallScores.at(j)) {
                int tempScore = overallScores.at(i);
                overallScores.replace(i, overallScores.at(j));
                overallScores.replace(j, tempScore);

                QString tempPlayer = overallPlayers.at(i);
                overallPlayers.replace(i, overallPlayers.at(j));
                overallPlayers.replace(j, tempPlayer);
            }
        }
    }

    topScoreLabel1->setText(" " + QString::number(overallScores.at(0)));
    if (QString::compare(overallPlayers.at(0), playerNameText, Qt::CaseInsensitive) == 0) {
        topScoreLabel1->setStyleSheet("background-color: #E3216F");
    } else {
        topScoreLabel1->setStyleSheet("background-color: white");
    }
    topScoreLabel2->setText(" " + QString::number(overallScores.at(1)));
    if (QString::compare(overallPlayers.at(1), playerNameText, Qt::CaseInsensitive) == 0) {
        topScoreLabel2->setStyleSheet("background-color: #E3216F");
    } else {
        topScoreLabel2->setStyleSheet("background-color: white");
    }

    topScoreLabel3->setText(" " + QString::number(overallScores.at(2)));
    if (QString::compare(overallPlayers.at(2), playerNameText, Qt::CaseInsensitive) == 0) {
        topScoreLabel3->setStyleSheet("background-color: #E3216F");
    } else {
        topScoreLabel3->setStyleSheet("background-color: white");
    }

    topScoreLabel4->setText(" " + QString::number(overallScores.at(3)));
    if (QString::compare(overallPlayers.at(3), playerNameText, Qt::CaseInsensitive) == 0) {
        topScoreLabel4->setStyleSheet("background-color: #E3216F");
    } else {
        topScoreLabel4->setStyleSheet("background-color: white");
    }

    topScoreLabel5->setText(" " + QString::number(overallScores.at(4)));
    if (QString::compare(overallPlayers.at(4), playerNameText, Qt::CaseInsensitive) == 0) {
        topScoreLabel5->setStyleSheet("background-color: #E3216F");
    } else {
        topScoreLabel5->setStyleSheet("background-color: white");
    }

    topScoreNameLabel1->setText(" " + overallPlayers.at(0));
    if (QString::compare(overallPlayers.at(0), playerNameText, Qt::CaseInsensitive) == 0) {
        topScoreNameLabel1->setStyleSheet("background-color: #E3216F");
    } else {
        topScoreNameLabel1->setStyleSheet("background-color: white");
    }

    topScoreNameLabel2->setText(" " + overallPlayers.at(1));
    if (QString::compare(overallPlayers.at(1), playerNameText, Qt::CaseInsensitive) == 0) {
        topScoreNameLabel2->setStyleSheet("background-color: #E3216F");
    } else {

        topScoreNameLabel2->setStyleSheet("background-color: white");
    }

    topScoreNameLabel3->setText(" " + overallPlayers.at(2));
    if (QString::compare(overallPlayers.at(2), playerNameText, Qt::CaseInsensitive) == 0) {
        topScoreNameLabel3->setStyleSheet("background-color: #E3216F");
    } else {
        topScoreNameLabel3->setStyleSheet("background-color: white");
    }

    topScoreNameLabel4->setText(" " + overallPlayers.at(3));
    if (QString::compare(overallPlayers.at(3), playerNameText, Qt::CaseInsensitive) == 0) {
        topScoreNameLabel4->setStyleSheet("background-color: #E3216F");
    } else {
        topScoreNameLabel4->setStyleSheet("background-color: white");
    }

    topScoreNameLabel5->setText(" " + overallPlayers.at(4));
    if (QString::compare(overallPlayers.at(4), playerNameText, Qt::CaseInsensitive) == 0) {
        topScoreNameLabel5->setStyleSheet("background-color: #E3216F");
    } else {
        topScoreNameLabel5->setStyleSheet("background-color: white");
    }
}

QList<int> Menu::getHighScores() {
    QList<int> overallScores = highScores;
    overallScores.append(gameScore);

    // BubbleSort both highScores and highScoringPlayers
    for (int i = 0; i < overallScores.size(); i++) {
        for (int j = 0; j < overallScores.size(); j++) {
            if (i == j) {
                continue;
            }
            if (overallScores.at(i) >= overallScores.at(j)) {
                int tempScore = overallScores.at(i);
                overallScores.replace(i, overallScores.at(j));
                overallScores.replace(j, tempScore);
            }
        }
    }

    overallScores.pop_back();

    return overallScores;
}

QList<QString> Menu::getHighScoringPlayers() {
    QList<int> overallScores = highScores;
    QList<QString> overallPlayers = highScoringPlayers;
    overallScores.append(gameScore);
    overallPlayers.append(playerNameText);

    // BubbleSort both highScores and highScoringPlayers
    for (int i = 0; i < overallScores.size(); i++) {
        for (int j = 0; j < overallScores.size(); j++) {
            if (i == j) {
                continue;
            }
            if (overallScores.at(i) >= overallScores.at(j)) {
                int tempScore = overallScores.at(i);
                overallScores.replace(i, overallScores.at(j));
                overallScores.replace(j, tempScore);

                QString tempPlayer = overallPlayers.at(i);
                overallPlayers.replace(i, overallPlayers.at(j));
                overallPlayers.replace(j, tempPlayer);
            }
        }
    }

    overallPlayers.pop_back();

    for (int i = 0; i < 5; i++) {
        if (QString::compare(overallPlayers.at(i), playerNameText, Qt::CaseInsensitive) == 0) {
            QString formatPlayerName = overallPlayers.at(i);
            formatPlayerName.chop(4);
            overallPlayers.replace(i, formatPlayerName);
        }
    }

    return overallPlayers;
}

void Menu::toggleDisplayLevels() {
//    if (levelsLabels->isVisible()) {
//        levelsLabels->setVisible(false);
//    } else {
//        levelsLabels->setVisible(true);
//    }
}

}
