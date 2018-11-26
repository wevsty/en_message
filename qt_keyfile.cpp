#include "qt_keyfile.h"

//QString OpenKeyFileDialog(QWidget *parent = Q_NULLPTR)
QString OpenKeyFileDialog(QWidget *parent)
{
    //QFileDialog
    QFileDialog qfd(parent);
    //设置模式
    qfd.setAcceptMode(QFileDialog::AcceptOpen);
    //返回文件名，无论文件是否存在
    qfd.setFileMode(QFileDialog::AnyFile);
    //设置标题
    qfd.setWindowTitle(QObject::tr("Open Key File"));
    //设置起始目录
    qfd.setDirectory(".");
    //设置显示过滤列表
    QStringList name_filter_list;
    name_filter_list << QObject::tr("Key files (*.key *.bin)")
                     << QObject::tr("Hex files (*.hex)")
                     << QObject::tr("Base64 files (*.base64)")
                     << QObject::tr("Text files (*.txt)")
                     << QObject::tr("Any files (*)");
    //设置显示过滤
    qfd.setNameFilters(name_filter_list);
    //显示对话框
    qfd.exec();
    //获取选择路径
    QStringList qlist_filepath = qfd.selectedFiles();
    if(qlist_filepath.size() == 0)
    {
        return QString();
    }
    else
    {
        return qlist_filepath.first();
    }
}

//QString SaveKeyFileDialog(QWidget *parent = Q_NULLPTR)
QString SaveKeyFileDialog(QWidget *parent)
{
    QFileDialog qfd(parent);
    qfd.setAcceptMode(QFileDialog::AcceptSave);
    //返回文件名，无论文件是否存在
    qfd.setFileMode(QFileDialog::AnyFile);
    //设置标题
    qfd.setWindowTitle(QObject::tr("Save Key File"));
    //设置起始目录
    qfd.setDirectory(".");
    //设置显示过滤列表
    QStringList name_filter_list;
    name_filter_list << QObject::tr("Key files (*.key *.bin)")
                     << QObject::tr("Hex files (*.hex)")
                     << QObject::tr("Base64 files (*.base64)")
                     << QObject::tr("Text files (*.txt)")
                     << QObject::tr("Any files (*)");
    //设置显示过滤
    qfd.setNameFilters(name_filter_list);
    //设置默认扩展名
    qfd.setDefaultSuffix(".key");
    //显示对话框
    qfd.exec();
    //获取选择路径
    QStringList qlist_filepath = qfd.selectedFiles();
    if(qlist_filepath.size() == 0)
    {
        return QString();
    }
    else
    {
        return qlist_filepath.first();
    }
}

bool IsFilePathExtension(const QString &FilePath,const QString &FileExtension)
{
    QFileInfo finfo(FilePath);
    if(finfo.suffix() == FileExtension)
    {
        return true;
    }
    return false;
}

QByteArray ReadKeyFromFile(const QString &KeyFilePath,qint64 MaxReadSize)
{

    QByteArray q_bin_bytes;
    QFile key_file(KeyFilePath);
    if (!key_file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Open file failed.";
        return q_bin_bytes;
    }
    if(MaxReadSize <= 0)
    {
        q_bin_bytes = key_file.readAll();
    }
    else
    {
        q_bin_bytes = key_file.read(MaxReadSize);
    }
    key_file.close();
    return q_bin_bytes;
}

QByteArray ReadBase64KeyFromFile(const QString &KeyFilePath,qint64 MaxReadSize)
{
    QByteArray base64_array = ReadKeyFromFile(KeyFilePath,MaxReadSize);
    QByteArray bin_array = QByteArray::fromBase64(base64_array);
    return bin_array;
}

QByteArray ReadHexKeyFromFile(const QString &KeyFilePath,qint64 MaxReadSize)
{
    QByteArray hex_array = ReadKeyFromFile(KeyFilePath,MaxReadSize);
    QByteArray bin_array = QByteArray::fromHex(hex_array);
    return bin_array;
}

bool SaveKeyToFile(const QString &KeyFilePath,const QByteArray &BinData)
{
    QFile key_file(KeyFilePath);
    if (!key_file.open(QFile::WriteOnly))
    {
        qDebug() << "Open file failed.";
        return false;
    }
    key_file.write(BinData);
    key_file.close();
    return true;
}

bool SaveKeyToBase64File(const QString &KeyFilePath,const QByteArray &BinData)
{
    QByteArray bin_array = BinData.toBase64();
    return SaveKeyToFile(KeyFilePath,bin_array);
}

bool SaveKeyToHexFile(const QString &KeyFilePath,const QByteArray &BinData)
{
    QByteArray bin_array = BinData.toHex();
    return SaveKeyToFile(KeyFilePath,bin_array);
}

bool SaveKeyToFileWithExtension(const QString &KeyFilePath,const QByteArray &BinData)
{
    if(IsFilePathExtension(KeyFilePath,"base64")==true)
    {
        return SaveKeyToBase64File(KeyFilePath,BinData);
    }
    else if(IsFilePathExtension(KeyFilePath,"hex")==true)
    {
        return SaveKeyToHexFile(KeyFilePath,BinData);
    }
    else
    {
        return SaveKeyToFile(KeyFilePath,BinData);
    }
}
