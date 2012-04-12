#include "levelselector.h"

LevelSelector::LevelSelector(QRect geometry,QWidget *parent):QWidget(parent)
{

    this->grabMouse();    
    this->setMouseTracking(true);
    this->grabKeyboard();

    this->setGeometry(0,0,geometry.width(),geometry.height());
    this->geometry=geometry;

    this->computeHeight();
    this->findLevels();
}


LevelSelector::~LevelSelector()
{
    this->setMouseTracking(false);
    this->releaseKeyboard();
    this->releaseMouse();
}

void LevelSelector::findLevels()//Find .level file in the current direcotory
{
    QDir *dir;
    dir=new QDir();
    QStringList filters;
    filters <<"*.level";
    dir->setNameFilters(filters);
    levels=dir->entryList();
    levels.append("Exit")   ;
    int yOffset=(geometry.height()-levels.size()*(height+30)+30)/2;
    for(int j=0;j<levels.size();j++)
    {
        int y=yOffset+(height+30)*j;
        buttons.push_back(QRect(geometry.width()/4,y,geometry.width()/2,height));
    }
    delete dir;
}

void LevelSelector::paintButton(int ind, QPainter &p){

    QFont f;
    f.setFamily("Times");
    f.setPointSize(32);
    p.setFont(f);
    QColor bBg;//(255,255,255,30);
    bBg.setRgb(0,0,0,100);
    p.setBrush(bBg);
    p.setPen(Qt::darkGray);
    p.drawRoundedRect(buttons.at(ind),15,15);
    p.setPen(Qt::white);
    p.drawText(buttons.at(ind),Qt::AlignCenter,levels.at(ind));

}

void LevelSelector::computeHeight(){
    QFont f;
    f.setFamily("Times");
    f.setPointSize(32);
    height=QFontMetrics(f).height()+30;
}

void LevelSelector::mouseReleaseEvent(QMouseEvent *e){
    if (e->button()==Qt::LeftButton){        
        selected=-1;
        for (int i=0;i<buttons.length();i++){
            if (buttons[i].contains(e->pos())) selected=i;
        }        
        //qWarning(levels.at(selected).toAscii());
        if (selected==-1) return;
        if( selected==buttons.size()-1)
                emit this->closing();

        emit this->eventLevelSelected();
        //this->close();
    }

}

void LevelSelector::paintEvent(QPaintEvent *e){
    //Initialize painter
    QPainter p(this);
    //call the pain function
    paint(p);
    //close the painter
    if (p.end()) e->accept();
    else e->ignore();
}

void LevelSelector::paint(QPainter &p){
    QColor bg(0,0,0,200);
    p.setPen(Qt::transparent);
    p.setBrush(bg);
    p.drawRect(0,0,geometry.width(),geometry.height());
    p.setPen(Qt::white);
    p.setBrush(Qt::white);
    for (int i=0;i<levels.length();i++)
        paintButton(i,p);
}

void LevelSelector::closeAll()
{
    emit this->closing();
}

QString LevelSelector::getLevelSelected()
{
    if(selected!=levels.size())
        return levels.at(selected);
    else
        return "Exit";
}

void LevelSelector::keyReleaseEvent(QKeyEvent *e){
    if(e->key()==Qt::Key_Escape)
        emit this->closing();
}

