#include "widget.h"
#include "ui_widget.h"
#include <calc.h>
#include <maths.h>


Widget::Widget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::Widget),
	ANS(0.0),
	buffIn(""),
	isInputEmpty(true)
{
	ui->setupUi(this);
	ui->output_textEdit->setAlignment(Qt::AlignRight);

	// connects de botones de la calculadora a sus respectivas funciones de control
	connect(ui->pushButton_num0,SIGNAL(clicked()), this, SLOT(buttonClicked()));
	connect(ui->pushButton_num1,SIGNAL(clicked()), this, SLOT(buttonClicked()));
	connect(ui->pushButton_num2,SIGNAL(clicked()), this, SLOT(buttonClicked()));
	connect(ui->pushButton_num3,SIGNAL(clicked()), this, SLOT(buttonClicked()));
	connect(ui->pushButton_num4,SIGNAL(clicked()), this, SLOT(buttonClicked()));
	connect(ui->pushButton_num5,SIGNAL(clicked()), this, SLOT(buttonClicked()));
	connect(ui->pushButton_num6,SIGNAL(clicked()), this, SLOT(buttonClicked()));
	connect(ui->pushButton_num7,SIGNAL(clicked()), this, SLOT(buttonClicked()));
	connect(ui->pushButton_num8,SIGNAL(clicked()), this, SLOT(buttonClicked()));
	connect(ui->pushButton_num9,SIGNAL(clicked()), this, SLOT(buttonClicked()));
	connect(ui->pushButton_punto,SIGNAL(clicked()), this, SLOT(buttonClicked()));
	connect(ui->pushButton_mas,SIGNAL(clicked()), this, SLOT(buttonClicked()));
	connect(ui->pushButton_menos,SIGNAL(clicked()), this, SLOT(buttonClicked()));
	connect(ui->pushButton_multiplicar,SIGNAL(clicked()), this, SLOT(buttonClicked()));
	connect(ui->pushButton_dividir,SIGNAL(clicked()), this, SLOT(buttonClicked()));
	connect(ui->pushButton_parentesis_a,SIGNAL(clicked()), this, SLOT(buttonClicked()));
	connect(ui->pushButton_parentesis_c,SIGNAL(clicked()), this, SLOT(buttonClicked()));

	connect(ui->pushButton_AC,SIGNAL(clicked()), this, SLOT(buttonRemove()));
	connect(ui->pushButton_DEL,SIGNAL(clicked()), this, SLOT(buttonRemove()));
}

Widget::~Widget()
{
	delete ui;
}

void Widget::buttonClicked()
{
	QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());
	QString buttonValue = clickedButton->text();

	if(isInputEmpty)
	{
		// do stuff
		isInputEmpty = false;
	}

	if(!QString::compare(buttonValue,"X"))
		buttonValue.fill(QChar('*'));

	ui->input_lineEdit->setFocus();
	ui->input_lineEdit->insert(buttonValue);
	buffIn += buttonValue;
}

void Widget::buttonRemove()
{
	QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());

	if(!QString::compare(clickedButton->text(), "AC"))
	{
		ui->input_lineEdit->clear();
		buffIn.clear();
	}
	else if(!QString::compare(clickedButton->text(), "DEL"))
	{
		ui->input_lineEdit->backspace();
		int cursor = ui->input_lineEdit->cursorPosition();
		buffIn.remove(cursor,1); // o buffIn = buffIn.remove(... ??
	}
	ui->input_lineEdit->setFocus();
}

void Widget::on_pushButton_igual_clicked()
{
	ui->output_textEdit->insertPlainText( QString::number(ANS = resolverExpresion(buffIn.toLocal8Bit()))); //, 'f', 10) );
	// para el manejo de ANS voy a tener que modificar la libreria para que resolverExpresion tome como parametro un double, ANS
	// en la expresion, se le va a pasar la letra A, la cual va a reemplazar por el valor de ese parametro
	ui->output_textEdit->insertPlainText(QString('\n'));
	ui->input_lineEdit->setFocus();
}
