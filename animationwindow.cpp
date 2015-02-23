#include "animationwindow.h"
#include "ui_animationwindow.h"
#include "ledmatrix.h"
#include "frame.h"
#include <QFile>
#include <QTextStream>
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
    ui->customCharsRange->setRange(0,7);

    //custom chars first:
    ui->characters2choose->addItem("Your char #0");
    ui->characters2choose->addItem("Your char #1");
    ui->characters2choose->addItem("Your char #2");
    ui->characters2choose->addItem("Your char #3");
    ui->characters2choose->addItem("Your char #4");
    ui->characters2choose->addItem("Your char #5");
    ui->characters2choose->addItem("Your char #6");
    ui->characters2choose->addItem("Your char #7");

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
    int selected_row = ui->row_rangeL->value();
    int selected_col = ui->col_rangeL->value();
    if(ui->characters2choose->currentText().startsWith("Your")){
        for(int i = 0; i < 8; i++){
        if(ui->characters2choose->currentText().endsWith(QString::number(i).at(0)))
            ui->frameEditorL->setChar(selected_row,selected_col,characters[i]);
        }
    }
    else {
        char current_char = ui->characters2choose->currentText().toStdString().c_str()[0];
//    int received_char = int(current_char);

        ui->frameEditorL->setCharacter(current_char, selected_row, selected_col);
    }
}


void AnimationWindow::on_exportButton_clicked(){
    int fixedCol;
    int fixedRow;
    QFile plikWyj;
    QString str = "output.txt";
    plikWyj.setFileName(str);
    plikWyj.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream tekst(&plikWyj);


    tekst << "unsigned char dictionary[][8] = {\n\t";

    for(int h = 0; h < 32; h++){
            tekst << "{";
            for(int j = 0; j < 8; j++){
                fixedRow = (h<16) ? 0 : 1;
                fixedCol = (h < 16) ? 6*h : 6*(h-16);
                tekst << ui->frameEditorL->BoolRow2IntParser(j + fixedRow*9, fixedCol);
                tekst << ", ";
            }

            tekst << "},\n";
            tekst << endl << "\t";
        }
        tekst << "};\n";
        tekst << "HD44780 a;\n"
                 "a.Initalize();\n"
                 "a.Clear();\n"
                 "for(int j = 0; j < 8; j++)\n"
                 "a.BuildFont(j,dictionary[j]);\n"
                 "a.GoTo(0,0);\n"
                 "for(int j = 0; j < 8; j++)\n"
                 "\ta.DrawCustomFont(j);\n";
        plikWyj.close();

}

void AnimationWindow::on_clearButton_clicked(){
    ui->frameEditorL->clearDisplay();
}

void AnimationWindow::on_saveCustomChar_button_clicked(){
    int current_char = ui->customCharsRange->value();
    for(int j = 0; j < 8; j++)
        characters[current_char][j] = ui->CustomCharacter->BoolRow2IntParser(j,0);
}

void AnimationWindow::on_pushButton_2_clicked(){
    ui->CustomCharacter->clearDisplay();
}
