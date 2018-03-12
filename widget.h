#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QObject>
#include <QLineEdit>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
	Q_OBJECT

public:
	explicit Widget(QWidget *parent = 0);
	~Widget();

private slots:
	void buttonClicked();
	void buttonRemove();

	void on_pushButton_igual_clicked();

private:
	Ui::Widget *ui;

	void abortOperation();

	double ANS;
	QString buffIn;
	bool isInputEmpty;


	enum { NumDigitButtons = 10 };

};

#endif // WIDGET_H
