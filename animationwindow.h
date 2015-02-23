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

    void on_exportButton_clicked();

    void on_clearButton_clicked();

    void on_saveCustomChar_button_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::AnimationWindow *ui;
    void onPopulateCharacters();
    /**
    * custom characters:
    */
    int characters[8][8];
};

#endif // ANIMATIONWINDOW_H
