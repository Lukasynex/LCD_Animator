#ifndef ANIMATIONWINDOW_H
#define ANIMATIONWINDOW_H

#include <QWidget>

namespace Ui {
class AnimationWindow;
}

class AnimationWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AnimationWindow(QWidget *parent = 0);
    ~AnimationWindow();

private slots:
    void on_pushCharacterL_clicked();

private:
    Ui::AnimationWindow *ui;
    void onPopulateCharacters();
};

#endif // ANIMATIONWINDOW_H
