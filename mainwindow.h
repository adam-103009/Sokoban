#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QLabel>
#include <QMainWindow>
#include<QPushButton>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
signals:
    void steps();
    void move_box_right();
    void move_box_left();
    void move_box_up();
    void move_box_down();
    void move_box2_right();
    void move_box2_left();
    void move_box2_up();
    void move_box2_down();
    void move_box3_right();
    void move_box3_left();
    void move_box3_up();
    void move_box3_down();
    void move();
    void move_left();
    void move_up();
    void move_down();
    void win_condition();
    void coin();
    void coin_box();
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void keyPressEvent(QKeyEvent *e);
private:
    QLabel *WIN=new QLabel(this);
    QList<QLabel *> labels;
    QLabel *menu=new QLabel(this);
    QPushButton *LEVEL1,*LEVEL2,*QUIT;
    QLabel *best=new QLabel(this);
private:
    Ui::MainWindow *ui;
private slots:
       void  calculus_steps();
       void  move_box_Right();
       void  move_box_Left();
       void  move_box_Up();
       void  move_box_Down();
       void  move_box2_Right();
       void  move_box2_Left();
       void  move_box2_Up();
       void  move_box2_Down();
       void  move_box3_Right();
       void  move_box3_Left();
       void  move_box3_Up();
       void  move_box3_Down();
       void  move_right();
       void  move_Left();
       void  move_Up();
       void  move_Down();
       void  win_Condition();
       void on_restart_clicked();
       void on_next_clicked();
       void on_restart2_clicked();
       void Start_clicked();
       int quit_game();
       int on_quit_clicked();
       void calculus_coin();
       void calculaus_coin_box();
};

#endif // MAINWINDOW_H
