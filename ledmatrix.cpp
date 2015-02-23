#include "ledmatrix.h"

LedMatrix::LedMatrix(QWidget *v_parent)
    :
    QTableWidget(v_parent),
    m_offColor(QColor(0,0,0)),
    m_onColor(QColor(255,0,0)),
    m_justPressed(false)
{
    connect(this, SIGNAL(cellEntered(int,int)), this, SLOT(reactEntered(int,int)));
    connect(this, SIGNAL(cellPressed(int,int)), this, SLOT(reactPressed(int,int)));
}

void LedMatrix::init(int rows, int cols){
//    int v_cellWidth = CELL_WIDTH;
//    int v_cellHeight = CELL_HEIGHT;
//    int v_width = CELL_WIDTH*FRAME_COLS + 2;
//    int v_height = CELL_HEIGHT*FRAME_ROWS + 2;

    createDiodes(rows,cols);
    setGridSize(CELL_WIDTH, CELL_HEIGHT);
    setFixedHeight(CELL_HEIGHT*FRAME_ROWS + 2);
    setFixedWidth(CELL_WIDTH*FRAME_COLS + 2);
}

void LedMatrix::setGridSize(int v_width, int v_height)
{
    for(int i = 0; i < rowCount(); i++)
        setRowHeight(i, v_height);
    for(int j = 0; j < columnCount(); j++)
        setColumnWidth(j, v_width);
}

void LedMatrix::createDiodes(int v_rows, int v_cols)
{
    setRowCount(v_rows);
    setColumnCount(v_cols);
    for(int i = 0; i < rowCount(); i++)
        for(int j = 0; j < columnCount(); j++)
        {
            setItem(i, j, new QTableWidgetItem());
            item(i, j)->setBackgroundColor(m_offColor);
            if(i==8 || j%6==5)
                item(i, j)->setBackgroundColor(Qt::gray);


        }
}

void LedMatrix::setDiodeState(int v_row, int v_col, bool v_state)
{
    if(v_row==8 || v_col%6==5)
        return;
    item(v_row, v_col)->setBackgroundColor(v_state ? m_onColor : m_offColor);
}

bool LedMatrix::getDiodeState(int v_row, int v_col)
{
    return item(v_row, v_col)->backgroundColor() == m_onColor;
}

void LedMatrix::toggleDiodeState(int v_row, int v_col)
{
    setDiodeState(v_row, v_col, !getDiodeState(v_row, v_col));
}

void LedMatrix::setSimFrame(const SimFrame &v_frame)
{
    for(int i = 0; i < rowCount(); i++)
        for(int j = 0; j < columnCount(); j++)
            setDiodeState(i, j, v_frame.getPixel(i,j));
}

void LedMatrix::getSimFrame(SimFrame &v_frame)
{
    for(int i = 0; i < rowCount(); i++)
        for(int j = 0; j < columnCount(); j++)
            v_frame.setPixel(i ,j , getDiodeState(i,j));
}

void LedMatrix::clearDisplay()
{
    for(int i = 0; i < rowCount(); i++)
        for(int j = 0; j < columnCount(); j++)
            setDiodeState(i, j, false);
}

void LedMatrix::reactPressed(int v_row, int v_col)
{
    m_justPressed = true;
    toggleDiodeState(v_row, v_col);
}

void LedMatrix::reactEntered(int v_row, int v_col)
{
    if(!m_justPressed)
        toggleDiodeState(v_row, v_col);
    m_justPressed = false;
}
QString LedMatrix::getFieldData(int index){
    int fixedrow = (index < 16) ? 0 : 1;
    int fixedindex = (index < 16) ? index : index-16;
    QString str = "";
    for(int k = 0; k < 8; k++){
        str.append(BoolRow2IntParser(fixedindex*6, k + 9*fixedrow));
        str.append(", ");
    }
    return str;
}
/**
 * @brief BoolRow2IntParser
 * @param column index
 * @param row index
 * @return
 */
int LedMatrix::BoolRow2IntParser(int i, int j){
    if(i==8 || j%6!=0)
        return -1;
    int number=0;

    if(getDiodeState(i,j))
        number+=16;
    if(getDiodeState(i,j+1))
        number+=8;
    if(getDiodeState(i,j+2))
        number+=4;
    if(getDiodeState(i,j+3))
        number+=2;
    if(getDiodeState(i,j+4))
        number+=1;
    return number;
}
void LedMatrix::clearField(int row, int col){
    int fixed_row = (row) ? 9 : 0;
    int fixed_col = col*6;

    for(int i = fixed_row; i < fixed_row + 8; i++)
        for(int j = fixed_col; j < fixed_col + 5; j++)
            setDiodeState(i, j, false);
}
void LedMatrix::setChar(int* chars){

}

void LedMatrix::setCharacter(char ch, int row, int col){
    clearField(row,col);
    int fixed_row = (row) ? 9 : 0;
    int fixed_col = col*6;

    switch(ch){
        case '@':
        setDiodeState(fixed_row +1,fixed_col+1,true);
        setDiodeState(fixed_row +1,fixed_col+2,true);
        setDiodeState(fixed_row +1,fixed_col+3,true);

        setDiodeState(fixed_row +2,fixed_col,true);
        setDiodeState(fixed_row +2,fixed_col+4,true);

        setDiodeState(fixed_row +3,fixed_col+4,true);

        setDiodeState(fixed_row +4,fixed_col+1,true);
        setDiodeState(fixed_row +4,fixed_col+2,true);
        setDiodeState(fixed_row +4,fixed_col+4,true);

        setDiodeState(fixed_row +5,fixed_col,true);
        setDiodeState(fixed_row +5,fixed_col+2,true);
        setDiodeState(fixed_row +5,fixed_col+4,true);

        setDiodeState(fixed_row +6,fixed_col,true);
        setDiodeState(fixed_row +6,fixed_col+2,true);
        setDiodeState(fixed_row +6,fixed_col+4,true);

        setDiodeState(fixed_row +7,fixed_col+1,true);
        setDiodeState(fixed_row +7,fixed_col+2,true);
        setDiodeState(fixed_row +7,fixed_col+3,true);

        break;
    }
}

