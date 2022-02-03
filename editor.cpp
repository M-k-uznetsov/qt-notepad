#include "editor.h"


Editor::Editor(QWidget *parent): QPlainTextEdit(parent) {
    Area = new LineNumberArea(this);
    connect(this, &Editor::blockCountChanged, this, &Editor::UpdateAreaWidth);
    connect(this, &Editor::updateRequest, this, &Editor::UpdateArea);
    connect(this, &Editor::cursorPositionChanged, this, &Editor::Highlight);
    UpdateAreaWidth();
    Highlight();
}

int Editor::AreaWidth() {
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }
    int space = 3 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;

    return space;
}

void Editor::UpdateAreaWidth() {
    setViewportMargins(AreaWidth(), 0, 0, 0);
}

void Editor::UpdateArea(const QRect &rect, int number) {
    if (number)
        Area->scroll(0, number);
    else
        Area->update(0, rect.y(), Area->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        UpdateAreaWidth();
}

void Editor::resizeEvent(QResizeEvent *e) {
    QPlainTextEdit::resizeEvent(e);
    QRect cr = contentsRect();
    Area->setGeometry(QRect(cr.left(), cr.top(), AreaWidth(), cr.height()));
}

void Editor::Highlight() {
    QList<QTextEdit::ExtraSelection> extraSelections;
    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;
        QColor lineColor = QColor(Qt::yellow).lighter(160);
        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}

void Editor::AreaPaintEvent(QPaintEvent *event) {
    QPainter painter(Area);
    painter.fillRect(event->rect(), Qt::lightGray);
    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = qRound(blockBoundingGeometry(block).translated(contentOffset()).top());
    int bottom = top + qRound(blockBoundingRect(block).height());

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(Qt::black);
            painter.drawText(0, top, Area->width(), fontMetrics().height(), Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + qRound(blockBoundingRect(block).height());
        ++blockNumber;
    }
}
