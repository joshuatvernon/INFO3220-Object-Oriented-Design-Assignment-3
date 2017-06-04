#ifndef MENU_H
#define MENU_H

#include <QLabel>
#include <QPushButton>
namespace game {
class Menu {
public:
    Menu(QWidget* parent, QString name, int& playeScore, QList<QPair<QString, int>> scores);
    ~Menu();
    void displayMenu(bool paused);
    void openScore();
    void toggleDisplaySpeeds();
    void toggleDisplayControls();
    void toggleDisplayLevels();

private:
    void makeButtons(QWidget* parent, QString name);
    void closeButtons();  // if any buttons are left open, close them
    int& gameScore;

    // Buttons
    QPushButton* score;
    QPushButton* speed;
    QPushButton* slow;
    QPushButton* normal;
    QPushButton* fast;
    QPushButton* chaos;
    QPushButton* controls;
    QPushButton* levels;
    QPushButton* menu;
    QPushButton* resume;

    // Labels
    QLabel* playerName;
    QLabel* playerScoreLabel;
    QLabel* topScoreNameLabel;
    QLabel* topScoreLabel;
    QLabel* controlsLabel;

    // Menu
    void paintMenu();

    // Methods
    void revealPlayerScore(bool open);
};
}
#endif  // SCOREBUTTON_H
