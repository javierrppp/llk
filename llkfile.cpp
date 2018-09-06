#include "llkfile.h"
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QByteArray>
#include <QDebug>
#include <QDir>
#include <QCoreApplication>

llkFile::llkFile()
{

}

QString llkFile::readFile(QString path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return "";

    QByteArray decode_result;
    while (!file.atEnd()) {
          QByteArray line = file.readLine();
          decode_result += line;
    }
    encodeOrdecode(decode_result);
    return decode_result;
}

void llkFile::writeFile(QString path, QString content)
{
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    QByteArray encode_content = content.toLatin1();
    encodeOrdecode(encode_content);
    out << encode_content;
}


void llkFile::encodeOrdecode(QByteArray & text)
{
    static QByteArray key1 = "myprivatekey";
    static QByteArray key2 = "helloworld";
    qDebug() << "text.size:" + QString::number(text.size());
    for(int i = 0; i < text.size(); i++)
    {
        int keyIndex1 = i % key1.size();
        int keyIndex2 = i % key2.size();
        text[i] = text[i] ^ key1[keyIndex1];
        text[i] = text[i] ^ key2[keyIndex2];
    }
}

void llkFile::creatFile(QString filePath,QString fileName)
{
    QString currentDir = QCoreApplication::applicationDirPath();
    QDir tempDir;
    tempDir.setCurrent(currentDir);
    qDebug() << "path:" + QCoreApplication::applicationDirPath();
    if(!tempDir.exists(filePath))
     {
         qDebug()<<"不存在该路径"<<endl;
         tempDir.mkpath(filePath);
     }
     QFile *tempFile = new QFile;
     tempDir.setCurrent(filePath);
     qDebug()<<tempDir.currentPath();
     if(tempFile->exists(fileName))
     {
         qDebug()<<"文件存在";
         return ;
     }
     tempFile->setFileName(fileName);
     if(!tempFile->open(QIODevice::WriteOnly|QIODevice::Text))
     {
         qDebug()<<"打开失败";
     }
     tempFile->close();
     tempDir.setCurrent(currentDir);
     qDebug()<<tempDir.currentPath();
}
