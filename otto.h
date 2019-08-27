#ifndef OTTO_H
#define OTTO_H

#include <QDialog>

class QPushButton;
class QPlainTextEdit;

class Otto : public QDialog
{
	Q_OBJECT

	public:
		Otto(QWidget *parent = 0);
	
	signals:
	private slots:
		void findBuildClicked();
	private:
		QPushButton *findBuildButton;
		QPushButton *closeButton;
		QPlainTextEdit *findBuildResult;
};

#endif
