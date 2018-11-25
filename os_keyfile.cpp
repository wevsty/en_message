#include "os_keyfile.h"

os_keyfile::os_keyfile()
{

}

QByteArray ReadKeyFile(QString KeyFilePath,qint64 MaxReadSize = 0)
{
    QByteArray q_bin_bytes;
    QFile key_file(file_path);
    if (!key_file.open(QIODevice::ReadOnly))
    {
        qDebug() << "open failed";
        return q_bin_bytes;
    }
    q_bin_bytes = key_file.read(MaxReadSize);
    key_file.close();
    return q_bin_bytes;
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
    QByteArray q_pwd_bytes = pwd_file.read(MAX_KEY_BYTES_SIZE);
    pwd_file.close();
    QString qstr_password = QString::fromLocal8Bit(q_pwd_bytes.data(),
        q_pwd_bytes.size());
    ui->password_text->setText(qstr_password);
    ui->statusbar->showMessage(file_path);
    return;
}
