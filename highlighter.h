#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include"mainwindow.h"

#include <QSyntaxHighlighter>
#include<QXmlStreamReader>
#include <QXmlStreamAttribute>
#include <QXmlStreamAttributes>
#include<QRegularExpression>
#include<QBrush>
#include<QColor>
#include<QFile>
#include <fstream>

struct HighlightingRule
{
    QRegularExpression pattern;
    QTextCharFormat format;
};


class Highlighter : public QSyntaxHighlighter
{
    Q_OBJECT

private:


    QVector<HighlightingRule> highlighting_rules;

    QRegularExpression expr_begin;
    QRegularExpression expr_end;

    QTextCharFormat comment_format;

    QXmlStreamReader XMLStream;

    QString file;


public:

    Highlighter(QTextDocument *parent, QVector<HighlightingRule>& highlightingRules);

protected:
        void highlightBlock(const QString &text) override;

        friend class MainWindow;

};



#endif // HIGHLIGHTER_H
