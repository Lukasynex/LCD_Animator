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
    void setChar(int*);
public:
    QString getFieldData(int);

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
