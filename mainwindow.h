#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_findBuild_clicked();

    void on_pushButton_copyBuild_clicked();

    void on_pushButton_deleteSelected_clicked();

    void on_pushButton_getLatestJenkinsBuild_clicked();

    void on_pushButton_installLatestJenkinsBuild_clicked();

    void on_pushButton_deleteOldBuilds_clicked();

private:
    Ui::MainWindow *ui;

    std::string version;
    std::string changeList;
    QString file_absolute; 	// full path to the fileshare latest main build
    QString file_relative; 	// name of the latest main build
    QString desktop_path; 	// otto desktop folder

};
#endif // MAINWINDOW_H
