#include "menu.h"

namespace game {

Menu::Menu(QWidget* parent, QString name, int& playerScore, QList<QPair<QString, int>> scores)
        : gameScore(playerScore) {
    // Scores could be read in the future.
    makeButtons(parent, name);
}

Menu::~Menu() {
    delete score;
    delete playerName;
    delete playerScoreLabel;
}

void Menu::makeButtons(QWidget* parent, QString name) {
    score = new QPushButton("Score", parent);
    score->setGeometry(QRect(100, 0, 100, 30));
    score->setVisible(false);
    score->setStyleSheet("background-color: white");
    QObject::connect(score, SIGNAL(released()), parent, SLOT(showScore()));

    playerName = new QLabel(parent);
    playerName->setGeometry(0, 30, 100, 30);
    playerName->setText(name);
    playerName->setVisible(false);
    playerName->setStyleSheet("background-color: white");

    playerScoreLabel = new QLabel(parent);
    playerScoreLabel->setGeometry(100, 30, 100, 30);
    playerScoreLabel->setText(QString::number(gameScore));
    playerScoreLabel->setVisible(false);
    playerScoreLabel->setStyleSheet("background-color: gray");

    speed = new QPushButton("Speed", parent);
    speed->setGeometry(QRect(200, 0, 100, 30));
    speed->setVisible(false);
    speed->setStyleSheet("background-color: gray");
    QObject::connect(speed, SIGNAL(released()), parent, SLOT(toggleShowSpeed()));

    slow = new QPushButton("Slow", parent);
    slow->setGeometry(QRect(200, 30, 100, 30));
    slow->setVisible(false);
    slow->setStyleSheet("background-color: green");
    QObject::connect(slow, SIGNAL(released()), parent, SLOT(pressSlow()));

    normal = new QPushButton("Normal", parent);
    normal->setGeometry(QRect(200, 60, 100, 30));
    normal->setVisible(false);
    normal->setStyleSheet("background-color: yellow");
    QObject::connect(normal, SIGNAL(released()), parent, SLOT(pressNormal()));

    fast = new QPushButton("Fast", parent);
    fast->setGeometry(QRect(200, 90, 100, 30));
    fast->setVisible(false);
    fast->setStyleSheet("background-color: orange");
    QObject::connect(fast, SIGNAL(released()), parent, SLOT(pressFast()));

    chaos = new QPushButton("Chaos", parent);
    chaos->setGeometry(QRect(200, 120, 100, 30));
    chaos->setVisible(false);
    chaos->setStyleSheet("background-color: red");
    QObject::connect(chaos, SIGNAL(released()), parent, SLOT(pressChaos()));

    controls = new QPushButton("Controls", parent);
    controls->setGeometry(QRect(0, 0, 100, 30));
    controls->setVisible(false);
    controls->setStyleSheet("background-color: red");
    QObject::connect(controls, SIGNAL(released()), parent, SLOT(pressControls()));

    levels = new QPushButton("Levels", parent);
    levels->setGeometry(QRect(0, 0, 100, 30));
    levels->setVisible(false);
    levels->setStyleSheet("background-color: red");
    QObject::connect(levels, SIGNAL(released()), parent, SLOT(pressLevels()));

    menu = new QPushButton("Menu", parent);
    menu->setGeometry(QRect(0, 0, 100, 30));
    menu->setVisible(true);
    menu->setStyleSheet("background-color: red");
    QObject::connect(menu, SIGNAL(released()), parent, SLOT(pauseStart()));

    resume = new QPushButton("Resume", parent);
    resume->setGeometry(QRect(0, 0, 100, 30));
    resume->setVisible(false);
    resume->setStyleSheet("background-color: red");
    QObject::connect(resume, SIGNAL(released()), parent, SLOT(pauseStart()));

    topScoreLabel = new QLabel(parent);
    topScoreLabel->setGeometry(QRect(0, 0, 100, 30));
    topScoreLabel->setVisible(false);
    topScoreLabel->setStyleSheet("background-color: red");

    topScoreNameLabel = new QLabel(parent);
    topScoreNameLabel->setGeometry(QRect(0, 0, 0, 0));
    topScoreNameLabel->setVisible(false);
    topScoreNameLabel->setStyleSheet("background-color: white");

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
        levels->setVisible(true);
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
    levels->setVisible(false);
    revealPlayerScore(false);
}

// helper function for OpenScore
void Menu::revealPlayerScore(bool open) {
    // recalculate playerScoreLabel
    playerScoreLabel->setText(QString::number(gameScore));
    playerName->setVisible(open);
    playerScoreLabel->setVisible(open);
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

void Menu::toggleDisplayLevels() {
//    if (levelsLabels->isVisible()) {
//        levelsLabels->setVisible(false);
//    } else {
//        levelsLabels->setVisible(true);
//    }
}

}
