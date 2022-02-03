#include "highlighter.h"
#include <QtWidgets>

Highlighter::Highlighter(QTextDocument *parent, QVector<HighlightingRule>& rules)
    : QSyntaxHighlighter(parent)
{
    for(int i =0 ; i < rules.count() ; i++)
        highlighting_rules.push_back(rules.at(i));
    expr_begin = QRegularExpression(QStringLiteral("NoOption"));
    expr_end = QRegularExpression(QStringLiteral("NoOption"));

}


void Highlighter::highlightBlock(const QString &text) {

    for (const HighlightingRule &rule : qAsConst(highlighting_rules)) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
    setCurrentBlockState(0);

    int startIndex = 0;
       if (previousBlockState() != 1)
           startIndex = text.indexOf(expr_begin);

       while (startIndex >= 0) {
               QRegularExpressionMatch match = expr_end.match(text, startIndex);
               int endIndex = match.capturedStart();
               int commentLength = 0;
               if (endIndex == -1) {
                   setCurrentBlockState(1);
                   commentLength = text.length() - startIndex;
               } else
                   commentLength = endIndex - startIndex + match.capturedLength();
               setFormat(startIndex, commentLength, comment_format);
               startIndex = text.indexOf(expr_begin, startIndex + commentLength);
           }
}












