#ifndef QT_KEYFILE_H
#define QT_KEYFILE_H

#include <QDebug>
#include <QObject>
#include <QString>
#include <QApplication>
#include <QFileDialog>
#include <QFile>
#include <QFileInfo>

QString OpenKeyFileDialog(QWidget *parent = Q_NULLPTR);
QString SaveKeyFileDialog(QWidget *parent = Q_NULLPTR);
bool IsFilePathExtension(const QString &FilePath,const QString &FileExtension);

QByteArray ReadKeyFromFile(const QString &KeyFilePath,qint64 MaxReadSize = -1);
QByteArray ReadBase64KeyFromFile(const QString &KeyFilePath,qint64 MaxReadSize = -1);
QByteArray ReadHexKeyFromFile(const QString &KeyFilePath,qint64 MaxReadSize = -1);

bool SaveKeyToFile(const QString &KeyFilePath,const QByteArray &BinData);
bool SaveKeyToBase64File(const QString &KeyFilePath,const QByteArray &BinData);
bool SaveKeyToHexFile(const QString &KeyFilePath,const QByteArray &BinData);
bool SaveKeyToFileWithExtension(const QString &KeyFilePath,const QByteArray &BinData);

#endif // QT_KEYFILE_H
