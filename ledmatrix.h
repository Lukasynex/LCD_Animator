#ifndef LEDMATRIX_H
#define LEDMATRIX_H

#include <QTableWidget>
#include <QTableWidgetItem>
#include "simframe.h"
#define CELL_WIDTH  10
#define CELL_HEIGHT 10

class LedMatrix : public QTableWidget
{
    Q_OBJECT
private:
    QColor m_offColor;
    QColor m_onColor;
    bool m_justPressed;

private slots:
    void reactPressed(int v_row, int v_col);
    void reactEntered(int v_row, int v_col);

public slots:
    void clearDisplay(void);

private:
    void setGridSize(int v_width, int v_height);
    void createDiodes(int v_rows, int v_cols);
    void setDiodeState(int v_row, int v_col, bool v_state);
    void toggleDiodeState(int v_row, int v_col);

    //static ASCII representation;
    int interjection[8] = {0, 4, 4, 4, 0, 0, 4, 0};
    int quote[8] = {0, 10, 10, 0, 0, 0, 0, 0};
    int hash[8] = {0, 10, 10, 31, 10, 31, 10, 10 };
    int dollar[8] = {0, 4, 15, 20, 14, 5, 30, 4 };
    int procent[8] = {0, 24, 25, 2, 4, 8, 19, 3 };
    int apostrophe[8] =	{0, 12, 4, 8, 0, 0, 0, 0 };
    int parenthesis_left[8]	= {0, 2, 4, 8, 8, 8, 4, 2 };
    int parenthesis_right[8] =	{0, 8, 4, 2, 2, 2, 4, 8 };
    int asterisk[8] = {0, 0, 4, 21, 14, 21, 4, 0 };
    int ampersand[8] = {0, 12, 18, 20, 8, 21, 18, 13 };
    int plus[8] = {0, 0, 4, 4, 31, 4, 4, 0 };
    int comma[8] = {0, 0, 0, 0, 0, 12, 4, 8 };
    int minus[8] = {0, 0, 0, 0, 31, 0, 0, 0 };
    int dot[8] = {0, 0, 0, 0, 0, 0, 12, 12 };
    int slash[8] = {0, 0, 1, 2, 4, 8, 16, 0 };
    int zero[8] = {0, 14, 17, 19, 21, 25, 17, 14 };
    int one[8] = {0, 4, 12, 4, 4, 4, 4, 14 };

public:
    QString getFieldData(int);
    void setChar(int a,int b,int tab[]);
    LedMatrix(QWidget *v_parent);
    void init(int,int);
    bool diodeState(int v_row, int v_col);
    bool getDiodeState(int v_row, int v_col);
    void setSimFrame(const SimFrame &v_frame);
    void getSimFrame(SimFrame &v_frame);
    int BoolRow2IntParser(int i, int j);
    void setCharacter(char,int,int);
    void clearField(int row, int col);
};

#endif // LEDMATRIX_H
