#ifndef MOVABLELABEL_H
#define MOVABLELABEL_H

#include <QLabel>
#include <QMouseEvent>

class MovableLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MovableLabel(QWidget *parent = 0, QPoint posotion = QPoint(0,0), int index=0);

private:
    QPoint                  m_offset;
    int                     m_index;
    QVector<MovableLabel*>  m_labels;

    void mousePressEvent(QMouseEvent* ev);
    void mouseMoveEvent(QMouseEvent* ev);

signals:
	void labelMoved(int index);
};
#endif // MOVABLELABEL_H