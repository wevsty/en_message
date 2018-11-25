#include "gui_key_exchange_wizard.h"
#include "ui_gui_key_exchange_wizard.h"

Key_Exchange_Wizard::Key_Exchange_Wizard(QWidget *parent) :
    QWizard(parent),
    ui(new Ui::Key_Exchange_Wizard)
{
    ui->setupUi(this);

    //init
    b_is_have_myself_key_pair = false;
}

Key_Exchange_Wizard::~Key_Exchange_Wizard()
{
    delete ui;
}

bool Key_Exchange_Wizard::validateCurrentPage()
{
    int n_pageid = currentId();
    if(n_pageid == KEY_EXCHANGE_WIZARD_PAGE_GET_OTHER_PUBLIC_KEY)
    {
        QString qstr_text = ui->textEdit_Other_Public_Key_Display->toPlainText();
        m_other_ecdh_public_key = qstr_text.toStdString();
        bool b_agree = m_ecdh_algorithm.AgreePublicKeyWithBase64(m_other_ecdh_public_key);
        return b_agree;
    }
    if(n_pageid == KEY_EXCHANGE_WIZARD_PAGE_SAVE_KEY)
    {
        m_qstr_save_key_path = ui->lineEdit_Key_Save_Path->text();
        if(m_qstr_save_key_path.size() == 0)
        {
            QMessageBox::warning(this,
                                 QObject::tr("Warning"),
                                 QObject::tr("Must be seting save path."),
                                 QMessageBox::Default);
            return false;
        }
        //baocun
    }
    return true;
}

void Key_Exchange_Wizard::on_Key_Exchange_Wizard_currentIdChanged(int id)
{
    //qDebug()<< "pageid is " << id ;
    if(id == KEY_EXCHANGE_WIZARD_PAGE_CREATE_MYSELF_KEY_PAIR)
    {
        if(b_is_have_myself_key_pair == false)
        {
            b_is_have_myself_key_pair = true;
            emit on_pushButton_Create_Myself_Key_Pair_clicked();
        }
    }
}

void Key_Exchange_Wizard::on_pushButton_Create_Myself_Key_Pair_clicked()
{
    m_ecdh_algorithm.GenerateKeyPair();
    std::string str_base64_public_key = m_ecdh_algorithm.GetPublicKeyWithBase64();
    QString qstr_text = QString::fromStdString(str_base64_public_key);
    ui->textEdit_Myself_Public_Key_Display->setText(qstr_text);
}

void Key_Exchange_Wizard::on_pushButton_Copy_Myself_Public_Key_clicked()
{
    QString qstr_text = ui->textEdit_Myself_Public_Key_Display->toPlainText();
    SetClipboard(qstr_text);
}

void Key_Exchange_Wizard::on_pushButton_Paste_Other_Public_Key_clicked()
{
    QString qstr_text = GetClipboard();
    ui->textEdit_Other_Public_Key_Display->setText(qstr_text);
}
/*
QString save_shared_key_file(QWidget *parent = Q_NULLPTR)
{
    //QFileDialog
    QString file_path = QFileDialog::getSaveFileName(parent,
        QObject::tr("Save Key File"), ".",
        QObject::tr("Key Files(*.key *.passwd *.txt)"));
    if (file_path.length() == 0)
    {
        return "";
    }
    return file_path;
}
*/
void Key_Exchange_Wizard::on_pushButton_Key_Save_Browse_clicked()
{
    m_qstr_save_key_path = SaveKeyFileDialog(this);
    ui->lineEdit_Key_Save_Path->setText(m_qstr_save_key_path);
}

void Key_Exchange_Wizard::on_Key_Exchange_Wizard_accepted()
{
    qDebug()<< "Finish";
    std::string str_shared_key = m_ecdh_algorithm.GetSharedKey();
    QByteArray qarry_shared_key = QByteArray::fromStdString(str_shared_key);
    SaveKeyToFileWithExtension(m_qstr_save_key_path,qarry_shared_key);
}
