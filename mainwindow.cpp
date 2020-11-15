#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QKeyEvent>
#include<QPixmap>
#include<QLabel>
#include<iostream>

using namespace std;
//9=wall,1=player,2=box
static int a[8][9]={
              {0,0,0,9,9,9,9,9,9}
             ,{0,0,0,9,1,0,0,5,9}
             ,{0,0,0,9,0,2,3,0,9}
             ,{9,9,9,9,7,0,4,0,9}
             ,{9,0,0,0,0,0,0,6,9}
             ,{9,9,9,9,9,9,9,9,9}};
static int r=1,c=4,r1=4,r2=4,r3=4,c1=1,c2=2,c3=3,num=0,coin_num=0,temp=0;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    best->setVisible(false);
    QUIT=new QPushButton("QUIT",this);
    QUIT->setGeometry(200,200,150,50);
    QUIT->show();
    LEVEL2=new QPushButton("START LEVEL2",this);
    LEVEL2->setGeometry(200,150,150,50);
    LEVEL2->show();
    LEVEL1=new QPushButton("START LEVEL1");
    LEVEL1->setParent(this);
    LEVEL1->setGeometry(200,100,150,50);
    LEVEL1->show();
    QPalette palette;
    palette.setColor(QPalette::Background,QColor(100,255,255));
    ui->steps->setNum(0);
    ui->restart2->setVisible(false);
    QPixmap sign(":/img/image/sign");
    ui->sign1->setPixmap(sign);
    ui->sign2->setPixmap(sign);
    ui->sign3->setPixmap(sign);
    ui->sign3->setScaledContents(true);
    ui->sign1->setScaledContents(true);
    ui->sign2->setScaledContents(true);
    ui->sign1->setGeometry(50,200,50,50);
    ui->sign2->setGeometry(100,200,50,50);   
    ui->sign3->setGeometry(150,200,50,50);  
    static QPixmap wall(":/img/image/wall.png");
    for (int i = 0; i < 35; ++i){
       labels << new QLabel(this);}
    for (int i = 0; i < 35; ++i){
        labels.at(i)->setPixmap(wall);
         labels.at(i)->setScaledContents(true);
        if(i<6){
       labels.at(i)->setGeometry(150+i*50,0,50,50);
        }
        else if(i>=6&&i<11){
            labels.at(i)->setGeometry(400,50+50*(i-6),50,50);
        }
        else if(i>=11&&i<19){
            labels.at(i)->setGeometry(350-50*(i-11),250,50,50);
        }
        else if(i>=19&&i<21){
            labels.at(i)->setGeometry(0,250-50*(i-18),50,50);

        }
        else if(i>=21&&i<24){
            labels.at(i)->setGeometry(50*(i-20),150,50,50);
        }
        else if(i>=24&&i<26){
            labels.at(i)->setGeometry(150,150-50*(i-23),50,50);
        }
        else{
            labels.at(i)->setVisible(false);
        }
    }
    QPixmap pix(":/img/image/workers");
    QPixmap box(":/img/image/box");
    QPixmap box2(":/img/image/box");
    QPixmap box3(":/img/image/box");
    QPixmap coin(":/img/image/coin.jpg");
    ui->coin1->setPixmap(coin);
    ui->coin2->setPixmap(coin);
    ui->coin3->setPixmap(coin);
    ui->coin1->setGeometry(350,50,50,50);
    ui->coin1->setScaledContents(true);
    ui->coin2->setGeometry(350,200,50,50);
    ui->coin2->setScaledContents(true);
    ui->coin3->setGeometry(200,150,50,50);
    ui->coin3->setScaledContents(true);
    ui->box2->setPixmap(box);
    ui->box2->setGeometry(300,100,50,50);
    ui->box2->raise();
    ui->box2->setScaledContents(true);
    ui->box3->setPixmap(box);
    ui->box3->setGeometry(300,150,50,50);
    ui->box3->raise();
    ui->box3->setScaledContents(true);
    ui->box->setPixmap(box);
    ui->box->setGeometry(250,100,50,50);
    ui->box->raise();
    ui->box->setScaledContents(true);
    ui->label->setPixmap(pix);
    ui->label->setGeometry(200,50,50,50);
    ui->label->raise();
    ui->label->setScaledContents(true);
    menu->setAutoFillBackground(true);
    menu->setPalette(palette);
    menu->setGeometry(0,0,600,500);
    menu->raise();
    menu->setVisible(true);
    LEVEL1->raise();
    LEVEL2->raise();
    QUIT->raise();
    connect(this,SIGNAL(move_box3_right()),this,SLOT(move_box3_Right()));
    connect(this,SIGNAL(move_box3_left()),this,SLOT(move_box3_Left()));
    connect(this,SIGNAL(move_box3_up()),this,SLOT(move_box3_Up()));
    connect(this,SIGNAL(move_box3_down()),this,SLOT(move_box3_Down()));
    connect(this,SIGNAL(move_box2_right()),this,SLOT(move_box2_Right()));
    connect(this,SIGNAL(move_box2_left()),this,SLOT(move_box2_Left()));
    connect(this,SIGNAL(move_box2_up()),this,SLOT(move_box2_Up()));
    connect(this,SIGNAL(move_box2_down()),this,SLOT(move_box2_Down()));
    connect(this,SIGNAL(move_box_right()),this,SLOT(move_box_Right()));
    connect(this,SIGNAL(move_box_left()),this,SLOT(move_box_Left()));
    connect(this,SIGNAL(move_box_up()),this,SLOT(move_box_Up()));
    connect(this,SIGNAL(move_box_down()),this,SLOT(move_box_Down()));
    connect(this,SIGNAL(move()),this,SLOT(move_right()));
    connect(this,SIGNAL(move_left()),this,SLOT(move_Left()));
    connect(this,SIGNAL(move_up()),this,SLOT(move_Up()));
    connect(this,SIGNAL(move_down()),this,SLOT(move_Down()));
    connect(this,SIGNAL(win_condition()),this,SLOT(win_Condition()));
    connect(ui->next,SIGNAL(clicked()),this,SLOT(on_next_clicked()));
    connect(this,SIGNAL(steps()),this,SLOT(calculus_steps()));
    connect(LEVEL1,SIGNAL(clicked()),this,SLOT(Start_clicked()));
    connect(LEVEL2,SIGNAL(clicked()),this,SLOT(on_next_clicked()));
    connect(LEVEL2,SIGNAL(clicked()),this,SLOT(Start_clicked()));
    connect(QUIT,SIGNAL(clicked()),this,SLOT(quit_game()));
    connect(this,SIGNAL(coin()),this,SLOT(calculus_coin()));
    connect(this,SIGNAL(coin_box()),this,SLOT(calculaus_coin_box()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::keyPressEvent(QKeyEvent *e){
    if(e->key()==Qt::Key_D){
            if(a[r][c+1]==0){
            a[r][c]=0;
            a[r][c+1]=1;
            c++;
            emit move();
            emit steps();
            }
            else if(a[r][c+1]==5||a[r][c+1]==6||a[r][c+1]==7){
                emit coin();
            a[r][c]=0;
            a[r][c+1]=1;
            c++;
            emit move();
            emit steps();

            }
            else if(a[r][c+1]==2){
                if(a[r][c+2]==0){
                    a[r][c]=0;
                    a[r][c+1]=1;
                    a[r][c+2]=2;
                    c++;
                    emit move();
                    emit steps();
                    emit move_box_right();
                    if(a[r1][c1]!=0&&a[r2][c2]!=0&&a[r3][c3]!=0&&a[r1][c1]!=1&&a[r2][c2]!=1&&a[r3][c3]!=1){
                        emit win_condition();
                    }
                }
                else if(a[r][c+2]==5||a[r][c+2]==6||a[r][c+2]==7){
                    emit coin_box();
                    a[r][c]=0;
                    a[r][c+1]=1;
                    a[r][c+2]=2;
                    c++;
                    emit move();
                    emit steps();
                    emit move_box_right();
                }
            }
            else if(a[r][c+1]==3){
                if(a[r][c+2]==0){
                    a[r][c]=0;
                    a[r][c+1]=1;
                    a[r][c+2]=3;
                    c++;
                    emit move();
                    emit steps();
                    emit move_box2_right();
                    if(a[r1][c1]!=0&&a[r2][c2]!=0&&a[r3][c3]!=0&&a[r1][c1]!=1&&a[r2][c2]!=1&&a[r3][c3]!=1){
                        emit win_condition();
                    }
                }
                else if(a[r][c+2]==5||a[r][c+2]==6||a[r][c+2]==7){
                    emit coin_box();
                    a[r][c]=0;
                    a[r][c+1]=1;
                    a[r][c+2]=3;
                    c++;
                    emit move();
                    emit steps();
                    emit move_box2_right();
                }
            }
            else if(a[r][c+1]==4){
                if(a[r][c+2]==0){
                    a[r][c]=0;
                    a[r][c+1]=1;
                    a[r][c+2]=4;
                    c++;
                    emit move();
                    emit steps();
                    emit move_box3_right();
                    if(a[r1][c1]!=0&&a[r2][c2]!=0&&a[r3][c3]!=0&&a[r1][c1]!=1&&a[r2][c2]!=1&&a[r3][c3]!=1){
                        emit win_condition();
                    }
                }
                else if(a[r][c+2]==5||a[r][c+2]==6||a[r][c+2]==7){
                    emit coin_box();
                    a[r][c]=0;
                    a[r][c+1]=1;
                    a[r][c+2]=4;
                    c++;
                    emit move();
                    emit steps();
                    emit move_box3_right();
                }
            }
        }
    else if(e->key()==Qt::Key_A){

            if(a[r][c-1]==0){
            a[r][c]=0;
            a[r][c-1]=1;
            c--;
        emit move_left();
            emit steps();
            }
            else if(a[r][c-1]==5||a[r][c-1]==6||a[r][c-1]==7){
                 emit coin();
            a[r][c]=0;
            a[r][c-1]=1;
            c--;
            emit move_left();
            emit steps();

            }
            else if(a[r][c-1]==2){
                if(a[r][c-2]==0){
                    a[r][c]=0;
                    a[r][c-1]=1;
                    a[r][c-2]=2;
                    c--;
                    emit move_box_left();
                    emit steps();
                emit move_left();
                    if(a[r1][c1]!=0&&a[r2][c2]!=0&&a[r3][c3]!=0&&a[r1][c1]!=1&&a[r2][c2]!=1&&a[r3][c3]!=1){
                        emit win_condition();
                    }
                }
                else if(a[r][c-2]==5||a[r][c-2]==6||a[r][c-2]==7){
                    emit coin_box();
                    a[r][c]=0;
                    a[r][c-1]=1;
                    a[r][c-2]=2;
                    c--;
                    emit move_box_left();
                    emit move_left();
                    emit steps();
                }
            }
            else if(a[r][c-1]==3){
                if(a[r][c-2]==0){
                    a[r][c]=0;
                    a[r][c-1]=1;
                    a[r][c-2]=3;
                    c--;
                    emit move_box2_left();
                    emit steps();
                emit move_left();
                    if(a[r1][c1]!=0&&a[r2][c2]!=0&&a[r3][c3]!=0&&a[r1][c1]!=1&&a[r2][c2]!=1&&a[r3][c3]!=1){
                        emit win_condition();
                    }
                }
                else if(a[r][c-2]==5||a[r][c-2]==6||a[r][c-2]==7){
                    emit coin_box();
                    a[r][c]=0;
                    a[r][c-1]=1;
                    a[r][c-2]=3;
                    c--;
                    emit move_box2_left();
                    emit move_left();
                    emit steps();
                }
            }
            else if(a[r][c-1]==4){
                if(a[r][c-2]==0){
                    a[r][c]=0;
                    a[r][c-1]=1;
                    a[r][c-2]=4;
                    c--;
                    emit move_box3_left();
                    emit steps();
                emit move_left();
                    if(a[r1][c1]!=0&&a[r2][c2]!=0&&a[r3][c3]!=0&&a[r1][c1]!=1&&a[r2][c2]!=1&&a[r3][c3]!=1){
                        emit win_condition();                    }
                }
                else if(a[r][c-2]==5||a[r][c-2]==6||a[r][c-2]==7){
                    emit coin_box();
                    a[r][c]=0;
                    a[r][c-1]=1;
                    a[r][c-2]=4;
                    c--;
                    emit move_box3_left();
                    emit move_left();
                    emit steps();

                }
            }

}
    else if(e->key()==Qt::Key_W){

            if(a[r-1][c]==0){
            a[r][c]=0;
            a[r-1][c]=1;
            r--;
        emit move_up();
            emit steps();
            }
            else if(a[r-1][c]==5||a[r-1][c]==6||a[r-1][c]==7){
                 emit coin();
            a[r][c]=0;
            a[r-1][c]=1;
            r--;
            emit move_up();
            emit steps();

            }
            else if(a[r-1][c]==2){
                if(a[r-2][c]==0){
                    a[r][c]=0;
                    a[r-1][c]=1;
                    a[r-2][c]=2;
                    r--;
                    emit move_box_up();
                    emit steps();
                emit move_up();
                    if(a[r1][c1]!=0&&a[r2][c2]!=0&&a[r3][c3]!=0&&a[r1][c1]!=1&&a[r2][c2]!=1&&a[r3][c3]!=1){
                        emit win_condition();
                    }
                }
                else if(a[r-2][c]==5||a[r-2][c]==6||a[r-2][c]==7){
                    emit coin_box();
                    a[r][c]=0;
                    a[r-1][c]=1;
                    a[r-2][c]=2;
                    r--;
                    emit move_up();
                    emit steps();
                    emit move_box_up();
                }
            }
            else if(a[r-1][c]==3){
                if(a[r-2][c]==0){
                    a[r][c]=0;
                    a[r-1][c]=1;
                    a[r-2][c]=3;
                    r--;
                    emit move_box2_up();
                    emit steps();
                emit move_up();
                    if(a[r1][c1]!=0&&a[r2][c2]!=0&&a[r3][c3]!=0&&a[r1][c1]!=1&&a[r2][c2]!=1&&a[r3][c3]!=1){
                        emit win_condition();
                    }
                }
                else if(a[r-2][c]==5||a[r-2][c]==6||a[r-2][c]==7){
                    emit coin_box();
                    a[r][c]=0;
                    a[r-1][c]=1;
                    a[r-2][c]=3;
                    r--;
                    emit move_up();
                    emit steps();
                    emit move_box2_up();
                }
            }
            else if(a[r-1][c]==4){
                if(a[r-2][c]==0){
                    a[r][c]=0;
                    a[r-1][c]=1;
                    a[r-2][c]=4;
                    r--;
                    emit move_box3_up();
                    emit steps();
                emit move_up();
                    if(a[r1][c1]!=0&&a[r2][c2]!=0&&a[r3][c3]!=0&&a[r1][c1]!=1&&a[r2][c2]!=1&&a[r3][c3]!=1){
                        emit win_condition();
                    }
                }
                else if(a[r-2][c]==5||a[r-2][c]==6||a[r-2][c]==7){
                    emit coin_box();
                    a[r][c]=0;
                    a[r-1][c]=1;
                    a[r-2][c]=4;
                    r--;
                    emit move_up();
                    emit steps();
                    emit move_box3_up();
                }
            }
        }

    else if(e->key()==Qt::Key_S){
            if(a[r+1][c]==0){
            a[r][c]=0;
            a[r+1][c]=1;
            r++;
        emit move_down();
            emit steps();
            }
            else if(a[r+1][c]==5||a[r+1][c]==6||a[r+1][c]==7){
            emit coin();
            a[r][c]=0;
            a[r+1][c]=1;
            r++;
            emit move_down();
            emit steps();
            }
            else if(a[r+1][c]==2){
                if(a[r+2][c]==0){
                    a[r][c]=0;
                    a[r+1][c]=1;
                    a[r+2][c]=2;
                    r++;
                    emit move_box_down();
                    emit steps();
                emit move_down();
                   if(a[r1][c1]!=0&&a[r2][c2]!=0&&a[r3][c3]!=0&&a[r1][c1]!=1&&a[r2][c2]!=1&&a[r3][c3]!=1){
                        emit win_condition();
                    }
                }
                else if(a[r+2][c]==5||a[r+2][c]==6||a[r+2][c]==7){
                    emit coin_box();
                    a[r][c]=0;
                    a[r+1][c]=1;
                    a[r+2][c]=2;
                    r++;
                    emit move_box_down();
                    emit steps();
                emit move_down();
                }
            }
            else if(a[r+1][c]==3){
                if(a[r+2][c]==0){
                    a[r][c]=0;
                    a[r+1][c]=1;
                    a[r+2][c]=3;
                    r++;
                    emit move_box2_down();
                    emit steps();
                emit move_down();
                   if(a[r1][c1]!=0&&a[r2][c2]!=0&&a[r3][c3]!=0&&a[r1][c1]!=1&&a[r2][c2]!=1&&a[r3][c3]!=1){
                        emit win_condition();
                    }
                }
                else if(a[r+2][c]==5||a[r+2][c]==6||a[r+2][c]==7){
                    emit coin_box();
                    a[r][c]=0;
                    a[r+1][c]=1;
                    a[r+2][c]=3;
                    r++;
                    emit move_box2_down();
                    emit steps();
                emit move_down();
                }
            }
            else if(a[r+1][c]==4){
                if(a[r+2][c]==0){
                    a[r][c]=0;
                    a[r+1][c]=1;
                    a[r+2][c]=4;
                    r++;
                    emit move_box3_down();
                    emit steps();
                emit move_down();
                    if(a[r1][c1]!=0&&a[r2][c2]!=0&&a[r3][c3]!=0&&a[r1][c1]!=1&&a[r2][c2]!=1&&a[r3][c3]!=1){
                        emit win_condition();
                    }
                }
                else if(a[r+2][c]==5||a[r+2][c]==6||a[r+2][c]==7){
                    emit coin_box();
                    a[r][c]=0;
                    a[r+1][c]=1;
                    a[r+2][c]=4;
                    r++;
                    emit move_box3_down();
                    emit steps();
                emit move_down();
                }
            }
    }
}

void MainWindow::calculus_steps()
{
    num++;
    ui->steps->setNum(num);
}


void MainWindow::move_box_Right()
{
    ui->box->setGeometry(ui->box->x()+50,ui->box->y(),50,50);
}

void MainWindow::move_box_Left()
{
    ui->box->setGeometry(ui->box->x()-50,ui->box->y(),50,50);
}

void MainWindow::move_box_Up()
{
    ui->box->setGeometry(ui->box->x(),ui->box->y()-50,50,50);
}

void MainWindow::move_box_Down()
{
    ui->box->setGeometry(ui->box->x(),ui->box->y()+50,50,50);
}
void MainWindow::move_box2_Right()
{
    ui->box2->setGeometry(ui->box2->x()+50,ui->box2->y(),50,50);
}

void MainWindow::move_box2_Left()
{
    ui->box2->setGeometry(ui->box2->x()-50,ui->box2->y(),50,50);
}

void MainWindow::move_box2_Up()
{
    ui->box2->setGeometry(ui->box2->x(),ui->box2->y()-50,50,50);
}

void MainWindow::move_box2_Down()
{
    ui->box2->setGeometry(ui->box2->x(),ui->box2->y()+50,50,50);
}
void MainWindow::move_box3_Right()
{
    ui->box3->setGeometry(ui->box3->x()+50,ui->box3->y(),50,50);
}

void MainWindow::move_box3_Left()
{
    ui->box3->setGeometry(ui->box3->x()-50,ui->box3->y(),50,50);
}

void MainWindow::move_box3_Up()
{
    ui->box3->setGeometry(ui->box3->x(),ui->box3->y()-50,50,50);
}

void MainWindow::move_box3_Down()
{
    ui->box3->setGeometry(ui->box3->x(),ui->box3->y()+50,50,50);
}
void MainWindow::move_right()
{
    ui->label->setGeometry(ui->label->x()+50,ui->label->y(),50,50);
}

void MainWindow::move_Left()
{
    ui->label->setGeometry(ui->label->x()-50,ui->label->y(),50,50);
}

void MainWindow::move_Up()
{
    ui->label->setGeometry(ui->label->x(),ui->label->y()-50,50,50);
}

void MainWindow::move_Down()
{
    ui->label->setGeometry(ui->label->x(),ui->label->y()+50,50,50);
}

void MainWindow::win_Condition()
{
    coin_num=coin_num+20;
    ui->coin->setNum(coin_num);
    QPixmap win(":/img/image/WIN.jpg");
    WIN->setPixmap(win);
    WIN->setGeometry(0,0,450,400);
    WIN->raise();
    WIN->setScaledContents(true);
    WIN->setVisible(true);
    if(coin_num==100){
        best->setGeometry(130,0,200,160);
        QPixmap a(":/img/image/best.png");
        best->setPixmap(a);
        best->setScaledContents(true);
        best->setVisible(true);
        best->raise();
    }
    else if(coin_num<100&&coin_num>50){
        best->setGeometry(130,-50,200,200);
        QPixmap b(":/img/image/good.png");
        best->setPixmap(b);
        best->setScaledContents(true);
        best->setVisible(true);
        best->raise();
    }

}

void MainWindow::on_restart_clicked()
{
    coin_num=0;
    ui->coin->setNum(0);
    ui->coin1->setVisible(true);
    ui->coin2->setVisible(true);
    ui->coin3->setVisible(true);
    WIN->setVisible(false);
    ui->steps->setNum(0);
    num=0;
    r=1;c=4;
    ui->box->setGeometry(250,100,50,50);
    ui->box2->setGeometry(300,100,50,50);
    ui->box3->setGeometry(300,150,50,50);
    ui->label->setGeometry(200,50,50,50);
    a[1][4]=1;a[2][5]=2;a[2][6]=3;a[3][6]=4;
    for(int i=1;i<5;i++){
        a[i][7]=0;
    }
    for(int i=1;i<7;i++){
        a[4][i]=0;
    }
    a[1][7]=5;
    a[3][4]=7;
    a[4][7]=6;
    a[1][5]=a[1][6]=a[2][4]=a[3][5]=0;
}


void MainWindow::on_next_clicked()
{
    temp=coin_num;
    ui->coin->setNum(temp);
    ui->coin1->setVisible(true);
    ui->coin2->setVisible(true);
    ui->coin3->setVisible(true);
    ui->next->setVisible(false);
    ui->steps->setNum(0);
    ui->restart2->setVisible(true);
    ui->restart->setVisible(false);
    WIN->setVisible(false);
    r=2;c=2;r1=4;r2=5;r3=6;c1=1;c2=1;c3=1;
    for(int i=0;i<8;i++){
        for(int j=0;j<9;j++){
            a[i][j]=0;
        }
    }
    for(int i=1;i<6;i++){
        a[0][i]=9;
    }
    for(int i=1;i<8;i++){
        a[7][i]=9;
    }
    for(int i=3;i<8;i++){
      a[i][7]=9;
    }
    for(int i=1;i<4;i++){
        a[i][1]=9;
    }
    for(int i=4;i<7;i++){
        a[1][i]=9;
    }
    for(int i=3;i<8;i++){
        a[i][0]=9;
    }
    a[2][6]=a[3][6]=a[3][2]=a[4][2]=a[3][4]=a[4][4]=a[5][5]=9;
    a[2][2]=1;a[2][3]=2;a[5][2]=3;a[6][5]=4;
    for(int i=0;i<35;i++){
        if(i<6){
            labels.at(i)->setGeometry(50+50*i,0,50,50);
        }
        else if(i>=6&&i<11){
            labels.at(i)->setGeometry(0,150+50*(i-6),50,50);
        }
        else if(i>=11&&i<18){
            labels.at(i)->setGeometry(50+50*(i-11),350,50,50);
        }
        else if(i>=18&&i<22){
            labels.at(i)->setGeometry(350,150+50*(i-18),50,50);
        }
        else if(i>=22&&i<25){
            labels.at(i)->setGeometry(50,50+50*(i-22),50,50);
        }
        else if(i>=25&&i<28){
            labels.at(i)->setGeometry(200+50*(i-25),50,50,50);
        }
        labels.at(i)->setVisible(true);
    }
        labels.at(28)->setGeometry(300,100,50,50);
        labels.at(29)->setGeometry(300,150,50,50);
        labels.at(30)->setGeometry(100,150,50,50);
        labels.at(31)->setGeometry(100,200,50,50);
        labels.at(32)->setGeometry(200,150,50,50);
        labels.at(33)->setGeometry(200,200,50,50);
        labels.at(34)->setGeometry(250,250,50,50);
        ui->sign1->setGeometry(50,200,50,50);
        ui->sign2->setGeometry(50,250,50,50);
        ui->sign3->setGeometry(50,300,50,50);
        ui->box->setGeometry(150,100,50,50);
        ui->box2->setGeometry(100,250,50,50);
        ui->box3->setGeometry(250,300,50,50);
        ui->label->setGeometry(100,100,50,50);
        a[5][4]=5;a[2][5]=6;a[4][6]=7;
        ui->coin1->setGeometry(200,250,50,50);
        ui->coin2->setGeometry(250,100,50,50);
        ui->coin3->setGeometry(300,200,50,50);

}

void MainWindow::on_restart2_clicked()
{
    best->setVisible(false);
    WIN->setVisible(false);
    ui->steps->setNum(0);
    num=0;coin_num=temp;
    ui->coin->setNum(temp);
    r=2;c=2;r1=4;r2=5;r3=6;c1=1;c2=1;c3=1;
    for(int i=0;i<8;i++){
        for(int j=0;j<9;j++){
            a[i][j]=0;
        }
    }
    for(int i=1;i<6;i++){
        a[0][i]=9;
    }
    for(int i=1;i<8;i++){
        a[7][i]=9;
    }
    for(int i=3;i<8;i++){
      a[i][7]=9;
    }
    for(int i=1;i<4;i++){
        a[i][1]=9;
    }
    for(int i=4;i<7;i++){
        a[1][i]=9;
    }
    for(int i=3;i<8;i++){
        a[i][0]=9;
    }
    a[2][6]=a[3][6]=a[3][2]=a[4][2]=a[3][4]=a[4][4]=a[5][5]=9;
    a[2][2]=1;a[2][3]=2;a[5][2]=3;a[6][5]=4;a[5][4]=5;a[2][5]=6;a[4][6]=7;
    ui->box->setGeometry(150,100,50,50);
    ui->box2->setGeometry(100,250,50,50);
    ui->box3->setGeometry(250,300,50,50);
    ui->label->setGeometry(100,100,50,50);
    ui->coin1->setVisible(true);
    ui->coin2->setVisible(true);
    ui->coin3->setVisible(true);
}

void MainWindow::Start_clicked()
{
   QUIT->setVisible(false);
   LEVEL2->setVisible(false);
   LEVEL1->setVisible(false);
   menu->setVisible(false);
}

int MainWindow::quit_game()
{
    exit(1) ;
}
int MainWindow::on_quit_clicked()
{
    exit(1);
}

void MainWindow::calculus_coin()
{
    coin_num=coin_num+10;
    ui->coin->setNum(coin_num);
    if(a[r][c+1]==5||a[r][c-1]==5||a[r+1][c]==5||a[r-1][c]==5){
    ui->coin1->setVisible(false);
    }
    if(a[r][c+1]==6||a[r][c-1]==6||a[r+1][c]==6||a[r-1][c]==6){
    ui->coin2->setVisible(false);
    }
    if(a[r][c+1]==7||a[r][c-1]==7||a[r+1][c]==7||a[r-1][c]==7){
        ui->coin3->setVisible(false);}
}

void MainWindow::calculaus_coin_box()
{
    coin_num=coin_num+10;
    ui->coin->setNum(coin_num);
    if(a[r][c+2]==5||a[r][c-2]==5||a[r+2][c]==5||a[r-2][c]==5){
    ui->coin1->setVisible(false);
    }
    if(a[r][c+2]==6||a[r][c-2]==6||a[r+2][c]==6||a[r-2][c]==6){
    ui->coin2->setVisible(false);
    }
    if(a[r][c+2]==7||a[r][c-2]==7||a[r+2][c]==7||a[r-2][c]==7){
        ui->coin3->setVisible(false);}
}


