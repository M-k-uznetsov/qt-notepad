#ifndef EDITOR_H
#define EDITOR_H

#include <QPlainTextEdit>
#include <QWidget>

#include "mainwindow.h"

class Editor: public QPlainTextEdit {

    Q_OBJECT

public:

    Editor(QWidget *parent = nullptr);

    void AreaPaintEvent(QPaintEvent *event);
    int AreaWidth();

protected:

    void resizeEvent(QResizeEvent *event) override;

private slots:

    void UpdateAreaWidth();
    void Highlight();
    void UpdateArea(const QRect &rect, int dy);

private:

    QWidget* Area;

};

class LineNumberArea : public QWidget
{
public:

    LineNumberArea(Editor *editor) : QWidget(editor), EditCode(editor)
    {}

    QSize sizeHint() const override
    {
        return QSize(EditCode->AreaWidth(), 0);
    }

protected:

    void paintEvent(QPaintEvent *event) override
    {
        EditCode->AreaPaintEvent(event);
    }

private:

    Editor *EditCode;

};

#endif // EDITOR_H
