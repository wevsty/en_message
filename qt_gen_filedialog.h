#ifndef QT_GEN_FILEDIALOG_H
#define QT_GEN_FILEDIALOG_H

//qt_gen_filedialog.h
#include <QDebug>
#include <QObject>
#include <QString>
#include <QApplication>
#include <QFileDialog>
#include <QFile>
#include <QFileInfo>


QString GenOpenFileDialog(QWidget *parent = Q_NULLPTR);
QString GenSaveFileDialog(QWidget *parent = Q_NULLPTR,const QString &defaultSuffix = ".dat");

#endif // QT_GEN_FILEDIALOG_H
