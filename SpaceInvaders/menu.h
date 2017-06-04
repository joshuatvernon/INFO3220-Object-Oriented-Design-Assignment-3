#ifndef MENU_H
#define MENU_H

#include <QLabel>
#include <QPushButton>
namespace game {
class Menu {
public:
    Menu(QWidget* parent, QString name, int& playeScore, QList<int> scores, QList<QString> players);
    ~Menu();
    void displayMenu(bool paused);
    void openScore();
    void toggleDisplaySpeeds();
    void toggleDisplayControls();
    void toggleDisplayLevels();
    void updateTopScores();

private:
    void makeButtons(QWidget* parent, QString name);
    void closeButtons();  // if any buttons are left open, close them
    int& gameScore;

    // High scores
     QList<int> highScores;
     QList<QString> highScoringPlayers;

    // Buttons
    QPushButton* score;
    QPushButton* speed;
    QPushButton* slow;
    QPushButton* normal;
    QPushButton* fast;
    QPushButton* chaos;
    QPushButton* controls;
    QPushButton* menu;
    QPushButton* resume;

    // Labels
    QLabel* playerName;
    QLabel* playerScoreLabel;

    QLabel* topScoreNameLabel1;
    QLabel* topScoreNameLabel2;
    QLabel* topScoreNameLabel3;
    QLabel* topScoreNameLabel4;
    QLabel* topScoreNameLabel5;
    QLabel* topScoreLabel1;
    QLabel* topScoreLabel2;
    QLabel* topScoreLabel3;
    QLabel* topScoreLabel4;
    QLabel* topScoreLabel5;

    QLabel* controlsLabel;

    // Menu
    void paintMenu();

    // Methods
    void revealPlayerScore(bool open);
};
}
#endif  // SCOREBUTTON_H
