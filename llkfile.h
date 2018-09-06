#ifndef LLKFILE_H
#define LLKFILE_H
#include <QString>


class llkFile
{
public:
    llkFile();
    static QString readFile(QString path);
    static void writeFile(QString path, QString content);
    static void encodeOrdecode(QByteArray& text);
    static void creatFile(QString filePath, QString fileName);
};

#endif // LLKFILE_H
