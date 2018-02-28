#include "main_ui.h"
#include "ui_main_ui.h"
#include "encrypt_str.h"
#include "hash_str.h"
#include "std_rand.h"
#include <QApplication>
#include <QClipboard>
#include <QFileDialog>
#include <QDebug>

#define ENMESSAGE_VERSION ("1.0.2")
#define ENMESSAGE_BUILD_DATE (__DATE__)
#define MAX_PASSWORD_SIZE 32
#define MAX_IV_SIZE 16

MainWindow_UI::MainWindow_UI(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow_UI)
{
	ui->setupUi(this);
	QString qstr_statusbar_tip;
	qstr_statusbar_tip.sprintf(
		"Version : %s Build Date : %s"
		, ENMESSAGE_VERSION
		, ENMESSAGE_BUILD_DATE
	);
	//ui->statusbar->setStatusTip(qstr_statusbar_tip);
	ui->statusbar->showMessage(qstr_statusbar_tip);
}

MainWindow_UI::~MainWindow_UI()
{
	delete ui;
}

void MainWindow_UI::on_Button_encrypt_clicked()
{
	QString qstr_password = ui->password_text->text();
	QString qstr_input_text = ui->encrypt_text->toPlainText();
	std::string str_out;
	if (ui->radio_is_aes256cfb->isChecked() == true)
	{
		QStringList qdata_list = qstr_input_text.split(",");
		if (qdata_list.isEmpty() == true)
		{
			str_out = QObject::tr("data error").toStdString();
		}
		else
		{
			std_rand safe_rand;
			std::string str_iv = safe_rand.rand_std_string(MAX_IV_SIZE);
			QString qstr_raw_data = qstr_input_text;
			std::string str_encrypt_data = AES_CFB_encrypt(qstr_password.toStdString()
				, str_iv
				, qstr_raw_data.toStdString());
			str_out = str_iv + ',' + str_encrypt_data;
		}
	}
	else if (ui->radio_is_aes256ecb->isChecked() == true)
	{
		str_out = AES_ECB_encrypt(qstr_password.toStdString()
			, qstr_input_text.toStdString());
	}
	else
	{
		str_out = "";
	}
	QString qstr_outtext;
	qstr_outtext = QString::fromStdString(str_out);
	ui->decrypt_text->setText(qstr_outtext);
}

void MainWindow_UI::on_Button_decrypt_clicked()
{
	QString qstr_password = ui->password_text->text();
	QString qstr_input_text = ui->encrypt_text->toPlainText();
	std::string str_out;
	if (ui->radio_is_aes256cfb->isChecked() == true)
	{
		QStringList qdata_list = qstr_input_text.split(",");
		if (qdata_list.isEmpty() == true)
		{
			str_out = QObject::tr("data error").toStdString();
		}
		else
		{
			QString qstr_iv = qdata_list.first();
			QString qstr_raw_data = qdata_list.last();
			str_out = AES_CFB_decrypt(qstr_password.toStdString()
				, qstr_iv.toStdString()
				, qstr_raw_data.toStdString());
		}
	}
	else if (ui->radio_is_aes256ecb->isChecked() == true)
	{
		str_out = AES_ECB_decrypt(qstr_password.toStdString()
			, qstr_input_text.toStdString());
	}
	else
	{
		str_out = "";
	}
	QString qstr_outtext;
	qstr_outtext = QString::fromStdString(str_out);
	ui->decrypt_text->setText(qstr_outtext);
}

void SetClipboard(const QString &input_str)
{
	QClipboard *board = QApplication::clipboard();
	board->setText(input_str);
}

QString GetClipboard()
{
	QClipboard *board = QApplication::clipboard();
	QString qstr_out = board->text();
	//QMessageBox::information(NULL, "From clipboard", str);
	return qstr_out;
}

void MainWindow_UI::on_Button_copy_clicked()
{
	QString qstr_input_text = ui->encrypt_text->toPlainText();
	SetClipboard(qstr_input_text);
}

void MainWindow_UI::on_Button_paste_clicked()
{
	QString qstr_output_text = GetClipboard();
	ui->encrypt_text->setText(qstr_output_text);
}

void MainWindow_UI::on_Button_clear_clicked()
{
	ui->encrypt_text->setText("");
}

void MainWindow_UI::on_Button_up_clicked()
{
	QString qstr_output_text = ui->decrypt_text->toPlainText();
	ui->encrypt_text->setText(qstr_output_text);
}

QString open_password_file(QWidget *parent = Q_NULLPTR)
{
	//QFileDialog
	QString file_path = QFileDialog::getOpenFileName(parent,
		QObject::tr("Open Password File"), ".",
		QObject::tr("Password Files (*.txt *.passwd);;All Files (*)"));
	if (file_path.length() == 0)
	{
		return "";
	}
	return file_path;
}

QString save_password_file(QWidget *parent = Q_NULLPTR)
{
	//QFileDialog
	QString file_path = QFileDialog::getSaveFileName(parent,
		QObject::tr("Save Password File"), ".",
		QObject::tr("Password Files(*.txt *.passwd)"));
	if (file_path.length() == 0)
	{
		return "";
	}
	return file_path;
}

void MainWindow_UI::on_Button_load_clicked()
{
	QString file_path = open_password_file(this);
	if (file_path.isEmpty() == true)
	{
		return;
	}
	QFile pwd_file(file_path);
	if (!pwd_file.open(QIODevice::ReadOnly))
	{
		qDebug() << "open failed";
		return;
	}
	else
	{
		qDebug() << "open ok";
	}
	QByteArray q_pwd_bytes = pwd_file.read(MAX_PASSWORD_SIZE);
	pwd_file.close();
	QString qstr_password = QString::fromLocal8Bit(q_pwd_bytes.data(),
		q_pwd_bytes.size());
	ui->password_text->setText(qstr_password);
	ui->statusbar->showMessage(file_path);
	return;
}

void MainWindow_UI::on_Button_save_clicked()
{
	QString qstr_password = ui->password_text->text();
	QString file_path = save_password_file(this);
	if (file_path.isEmpty() == true)
	{
		return;
	}
	QFile pwd_file(file_path);
	if (!pwd_file.open(QIODevice::WriteOnly))
	{
		qDebug() << "open failed";
		return;
	}
	else
	{
		qDebug() << "open ok";
	}
	QByteArray q_pwd_bytes = qstr_password.toUtf8();
	pwd_file.write(q_pwd_bytes);
	pwd_file.close();
	ui->statusbar->showMessage(file_path);
	return;
}

void MainWindow_UI::on_Button_copy_decrypted_clicked()
{
	QString qstr_input_text = ui->decrypt_text->toPlainText();
	SetClipboard(qstr_input_text);
}



void MainWindow_UI::on_Button_SHA256_clicked()
{
	QString file_path = open_password_file(this);
	if (file_path.isEmpty() == true)
	{
		return;
	}
	QFile pwd_file(file_path);
	if (!pwd_file.open(QIODevice::ReadOnly))
	{
		qDebug() << "open failed";
		return;
	}
	else
	{
		qDebug() << "open ok";
	}
	QByteArray q_pwd_bytes = pwd_file.readAll();
	pwd_file.close();
	std::string str_hash = calc_SHA256(q_pwd_bytes.toStdString());
	QString qstr_password = QString::fromStdString(str_hash);
	ui->password_text->setText(qstr_password);
	ui->statusbar->showMessage(file_path);
	return;
}
