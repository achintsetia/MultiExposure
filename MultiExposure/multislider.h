#ifndef MULTISLIDER_H
#define MULTISLIDER_H

#include <QSlider>
#include "movablelabel.h"

class MultiSlider : public QSlider
{
    Q_OBJECT
public:
    explicit MultiSlider(QWidget *parent = 0);
    ~MultiSlider();
	QPoint                  getLastPos(int index);
    QPoint                  getNextPos(int index);
	QPoint                  handlePos();
    int                     sliderVal(int index);
    QPoint                  sliderPos(int index);
    QVector<int>            values();
    int                     sliderCount();
    QVector<MovableLabel*>  getLabelList();

private:
	void	resizeEvent(QResizeEvent* ev);
    void    mousePressEvent(QMouseEvent* ev);
	void    mouseReleaseEvent(QMouseEvent* ev);
    void    mouseMoveEvent(QMouseEvent* ev);
    void    wheelEvent(QWheelEvent* ev);
    QPoint  val2Pos(int val);
    int     pos2Val(QPoint position);
	QPoint  val2Pos(int val, QSize size);
    int     pos2Val(QPoint position, QSize size);

    int                     m_labelCount;
    int                     m_maxLabels;
	int						m_width();
    QVector<MovableLabel*>  m_labels;
	bool					m_sliderSelected;

signals:
    void sliderMovedSignal(int index);
	void sliderAdded(int index);
    void sliderRemoved();
	void resized();

public slots:
	void labelMoved(int index);	
    void addSlider();
    void removeSlider();
};
#endif // MULTISLIDER_H
