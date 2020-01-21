#pragma comment(lib, "version.lib")
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QClipboard>
#include <QDir>
#include <QDirIterator>
#include <QFileInfo>
#include <QRegExp>
#include <QFile>

#include <iostream>
#include <string>
#include <Windows.h>
#include <winver.h>
#include <fileapi.h>
#include <stdlib.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_close, SIGNAL(clicked()), this, SLOT(close()));
    ui->lineEdit_fileshareLatestPath->setText("\\\\fileshare\\Build\\autobuilds\\Motive\\Latest\\");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_findBuild_clicked()
{
    LPCSTR versionFilePath = "C:\\Program Files\\OptiTrack\\Motive\\Motive.exe";
    DWORD verHandle = 0;
    UINT size = 0;
    LPBYTE lpBuffer = NULL;
    DWORD verSize = GetFileVersionInfoSizeA(versionFilePath, &verHandle);

    if (verSize != NULL)
    {
        LPSTR verData = new char[verSize];

        if (GetFileVersionInfoA(versionFilePath, verHandle, verSize, verData))
        {

            if (VerQueryValueA(verData, "\\StringFileInfo\\040904E4\\ProductVersion", (VOID FAR* FAR*)&lpBuffer, &size))
            {

                if (size)
                {
                    std::string productVersion = std::string(reinterpret_cast<char const *>(lpBuffer), size);
                    version = productVersion.substr(0, 5);
                    changeList = productVersion.substr(7, 5);
                    ui->lineEdit_findBuildResult->setText("CL " + QString::fromStdString(changeList) + " " + QString::fromStdString(version));

                }

            }

        }

    }

}

void MainWindow::on_pushButton_copyBuild_clicked()
{
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText("CL " + QString::fromStdString(changeList) + " " + QString::fromStdString(version));
}

void MainWindow::on_pushButton_deleteSelected_clicked()
{
    LPCSTR userProfilePath = "C:\\ProgramData\\OptiTrack\\MotiveProfile.motive";
    LPCSTR sysCalPath = "C:\\ProgramData\\OptiTrack\\Motive\\System Calibration.cal";
    LPCSTR deviceProfilePath = "C:\\ProgramData\\OptiTrack\\Motive\\DeviceProfiles\\DefaultDeviceProfile.xml";

    if (ui->checkBox_userProfile->isChecked())
    {
        DeleteFileA(userProfilePath);
    }

    if (ui->checkBox_systemCalibration->isChecked())
    {
        DeleteFileA(sysCalPath);
    }

    if (ui->checkBox_deviceProfile->isChecked())
    {
        DeleteFileA(deviceProfilePath);
    }

}

// 3.0
// TODO add filewatcher
void MainWindow::on_pushButton_getLatestJenkinsBuild_clicked()
{
    QDirIterator it(ui->lineEdit_fileshareLatestPath->text(), QDirIterator::NoIteratorFlags);
    QString file_temp;
    QString qt_slash_format = ui->lineEdit_fileshareLatestPath->text().replace(QString("\\"), QString("/"));
    QRegExp rx("main");

    // search the fileshare for the main build's absolute path and file name
    while (it.hasNext())
    {
        file_temp =  it.next();

        // find the main build
        if (rx.indexIn(file_temp) != -1)
        {
            file_absolute = file_temp;
            file_relative = file_temp.replace(qt_slash_format, QString(""));
        }

    }

    // create or open ~/Desktop/otto
    desktop_path = QDir(QDir().homePath()).filePath("Desktop/otto/");
    QDir().mkdir(desktop_path);

    qDebug() << file_absolute;
    qDebug() << desktop_path;

    if (!QFile::copy(file_absolute, desktop_path + file_relative))
    {
        qDebug() << "copy error -_-";
    }

}

void MainWindow::on_pushButton_installLatestJenkinsBuild_clicked()
{
    std::system((desktop_path + file_relative).toStdString().c_str());
}
