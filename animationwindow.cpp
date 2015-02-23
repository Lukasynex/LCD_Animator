#include "animationwindow.h"
#include "ui_animationwindow.h"
#include "ledmatrix.h"
#include "frame.h"
AnimationWindow::AnimationWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnimationWindow)
{
    ui->setupUi(this);
    ui->frameEditorL->init(FRAME_ROWS,FRAME_COLS);
    ui->CustomCharacter->init(SINGLE_CHARACTER_ROWS,SINGLE_CHARACTER_COLS);
    ui->CustomCharacter->setMaximumWidth(SINGLE_CHARACTER_ROWS +2);
    ui->CustomCharacter->setMaximumHeight(SINGLE_CHARACTER_COLS +2);
    onPopulateCharacters();
}
void AnimationWindow::onPopulateCharacters(){
    QString str = "";
    for(int i = 32; i < 126; i++){
        str.append(char(i));
        ui->characters2choose->addItem(str);
        str = "";
    }
    ui->row_rangeL->setRange(0,1);
    ui->col_rangeL->setRange(0,15);
}

AnimationWindow::~AnimationWindow(){
    delete ui;
}

void AnimationWindow::on_pushCharacterL_clicked(){
    char current_char = ui->characters2choose->currentText().toStdString().c_str()[0];
//    int received_char = int(current_char);
    int selected_row = ui->row_rangeL->value();
    int selected_col = ui->col_rangeL->value();

    ui->frameEditorL->setCharacter(current_char, selected_row, selected_col);
}
