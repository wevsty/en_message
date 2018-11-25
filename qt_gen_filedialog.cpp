#include "qt_gen_filedialog.h"

//QString GenOpenFileDialog(QWidget *parent = Q_NULLPTR)
QString GenOpenFileDialog(QWidget *parent)
{
    //QFileDialog
    QFileDialog qfd(parent);
    //设置模式
    qfd.setAcceptMode(QFileDialog::AcceptOpen);
    //返回文件名，无论文件是否存在
    qfd.setFileMode(QFileDialog::AnyFile);
    //设置标题
    qfd.setWindowTitle(QObject::tr("Open File"));
    //设置起始目录
    qfd.setDirectory(".");
    //设置显示过滤列表
    QStringList name_filter_list;
    name_filter_list << QObject::tr("Any files (*)");
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

//QString GenSaveFileDialog(QWidget *parent = Q_NULLPTR,const QString &defaultSuffix = ".dat")
QString GenSaveFileDialog(QWidget *parent,const QString &defaultSuffix)
{
    QFileDialog qfd(parent);
    qfd.setAcceptMode(QFileDialog::AcceptSave);
    //返回文件名，无论文件是否存在
    qfd.setFileMode(QFileDialog::AnyFile);
    //设置标题
    qfd.setWindowTitle(QObject::tr("Save File"));
    //设置起始目录
    qfd.setDirectory(".");
    //设置显示过滤列表
    QStringList name_filter_list;
    name_filter_list << QObject::tr("Any files (*)");
    //设置显示过滤
    qfd.setNameFilters(name_filter_list);
    //设置默认扩展名
    qfd.setDefaultSuffix(defaultSuffix);
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
