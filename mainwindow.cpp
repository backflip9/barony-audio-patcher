#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->fateDir->hide();
    ui->baronyDir->hide();
    ui->status->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Find Barony Folder"),"C:/Users",QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->fateDir->setText(dir);
    ui->fateDir->show();

}

void MainWindow::on_pushButton_2_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Find Barony Folder"),"C:/Program Files (x86)/Steam/steamapps/common/",QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->baronyDir->setText(dir);
    ui->baronyDir->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    if(ui->fateDir->text()=="empty"||ui->baronyDir->text()=="empty"){
        ui->status->setText("You haven't set your fate/barony directories");
        if(!ui->status->isVisible()){
            ui->status->show();
        }
        return;
    }
    if(ui->deathSoundCheck->isChecked()){
        qInfo("deathsound is checked");
        swapSound("/SOUNDS/VOICES/NARRATOR/die1.ogg","/sound/Death.ogg");
    }
    if(ui->trollCheck->isChecked()){
        qInfo("trollcheck is checked");
        swapSound("/SOUNDS/MONSTERS/YETI/idle1.wav","/sound/TrollSpot.ogg");
    }
    if(ui->barrelBreak->isChecked()){
        //qInfo("")
        swapSound("/SOUNDS/ITEMS/barrelbreak2.wav","sound/Breakwood.ogg");
    }
    if(ui->skeletonDeath->isChecked()){
        swapSound("/SOUNDS/MONSTERS/SKELETON/die1.wav","sound/SkeletonDie.ogg");
    }
    if(ui->levelUp->isChecked()){
        swapSound("/SOUNDS/VOICES/NARRATOR/levelup1.ogg","/sound/LevelUp.ogg");
    }
    if(ui->portalAmbient->isChecked()){
        swapSound("/SOUNDS/SPELLS/portalloop.wav","/sound/Portal.ogg");
    }
    if(ui->potionUse->isChecked()){
        swapSound("/SOUNDS/ITEMS/potionuse.wav","/sound/Drink1v1.ogg");
    }

}

void MainWindow::swapSound(QString fateExtension,QString baronyExtension){
    QString fateName=ui->fateDir->text() + fateExtension;
    QString baronyName=ui->baronyDir->text() + baronyExtension;
    QFile fateDie(fateName);
    QFile baronyDie(baronyName);
    qInfo("removing baronyDie");
    baronyDie.remove();
    //qInfo("renaming"+fateName.toStdString()+" to "+baronyName.toStdString());
    qInfo("renaming");
    fateDie.rename(baronyName);
    ui->status->setText("Moved "+fateName +" to "+baronyName);
    if(!ui->status->isVisible()){
        ui->status->show();
    }

}
