#include "multislider.h"
#include <QStyle>

MultiSlider::MultiSlider(QWidget *parent) : QSlider(parent)
{
    this->setStyleSheet("QSlider::handle{image: url(:/GelStanChemi/handle.png);}");
    this->setMouseTracking(false);
    this->setOrientation(Qt::Horizontal);
	this->setFixedHeight(20);

    m_labelCount = 0;
    m_maxLabels = 10;
    m_sliderSelected = false;

    addSlider();
    addSlider();
    addSlider();
}
MultiSlider::~MultiSlider()
{
    for(int i=0; i<m_labels.size(); i++)
        delete m_labels[i];
    m_labels.clear();
}

QPoint MultiSlider::getLastPos(int index)
{
    if(index==0)
        return handlePos();
    else if(index>0 && index <= m_labels.size())
        return QPoint(m_labels[index-1]->pos().x(),0);
	else
		return QPoint(0,0);
}

QPoint MultiSlider::getNextPos(int index)
{
	if(m_labels.size() == 0)
		return val2Pos(maximum());	
    else if(index>=-1 && index<m_labels.size()-1)
        return QPoint(m_labels[index+1]->pos().x(),0);
	else
		return val2Pos(maximum());
}

int MultiSlider::sliderVal(int index)
{
    //Has to return value of the label
    //Index == 0 is the original slider others are labels
    if(index < 0 || index > m_labels.size())
        return -1;
    else if (index == 0)
        return this->value();
    else
        return pos2Val(m_labels[index-1]->pos());
}

QPoint MultiSlider::sliderPos(int index)
{
    if (index == 0)
        return val2Pos(this->value());
    else if (index > 0 && index <= m_labels.size())
        return QPoint(m_labels[index-1]->pos().x(),0);
    else
        return QPoint(0,0);
}

QVector<int> MultiSlider::values()
{
    int total = sliderCount();
    QVector<int> res;
    for(int i=0; i<total; i++)
        res.push_back(sliderVal(i));
    return res;
}

int MultiSlider::sliderCount()
{
    return m_labelCount+1;
}

QVector<MovableLabel*> MultiSlider::getLabelList()
{
    return m_labels;
}

QPoint MultiSlider::handlePos()
{	
    return val2Pos(this->value());
}

QPoint MultiSlider::val2Pos(int val)
{
	int width = this->size().width();
	int p = QStyle::sliderPositionFromValue(minimum(), 
					maximum(), val, width, false);
	return QPoint(p,0);
}

QPoint MultiSlider::val2Pos(int val, QSize size)
{
	int width = size.width();
	int p = QStyle::sliderPositionFromValue(minimum(), 
					maximum(), val, width, false);
	return QPoint(p,0);
}

int MultiSlider::pos2Val(QPoint position)
{
	int width = this->size().width();
	return QStyle::sliderValueFromPosition(minimum(), 
					maximum(), position.x(), width, false);	
}

int MultiSlider::pos2Val(QPoint position, QSize size)
{
	int width = size.width();
	return QStyle::sliderValueFromPosition(minimum(), 
					maximum(), position.x(), width, false);	
}

void MultiSlider::resizeEvent(QResizeEvent* ev)
{
	QSize oldS = ev->oldSize();
	
	if( oldS.width() < 0)
	{
		emit resized();
		return;
	}
	QSize newS = ev->size();
	for(int i=0; i<m_labels.size(); i++)
	{
		int prevVal = pos2Val(m_labels[i]->pos(), oldS);
		m_labels[i]->move(val2Pos(prevVal));
	}	
	emit resized();
}
void MultiSlider::mousePressEvent(QMouseEvent* ev)
{
	if((ev->buttons() & Qt::LeftButton) && 
		(ev->pos() - handlePos()).manhattanLength()<20)
		m_sliderSelected = true;
}

void MultiSlider::mouseReleaseEvent(QMouseEvent*)
{
	m_sliderSelected = false;
}

void MultiSlider::mouseMoveEvent(QMouseEvent* ev)
{
	if(ev->buttons() & Qt::LeftButton && m_sliderSelected)
	{
		QPoint np = getNextPos(-1);
		QPoint diff = ev->pos()-val2Pos(this->value());
		if( ev->pos().x() < np.x())
		{
			int v = pos2Val(QPoint(abs(diff.x()),0)) - minimum();
			if(diff.x() < 0)
				this->setValue(this->value() - v);
			else
				this->setValue(this->value() + v);
		}
        emit sliderMovedSignal(0);
    }
}

void MultiSlider::wheelEvent(QWheelEvent* )
{
    return;
}

//Slot
void MultiSlider::addSlider()
{
    if(m_labelCount < m_maxLabels)
    {
        m_labelCount++;
		QPoint p = getLastPos(m_labelCount-1);
		QPoint maxPos = val2Pos(maximum());
        p = p + QPoint((maxPos.x()-p.x())/4,0);
        MovableLabel* ml = new MovableLabel(this, p, m_labelCount-1);        
        m_labels.push_back(ml);
        connect(m_labels[m_labelCount-1], SIGNAL(labelMoved(int)), this, SLOT(labelMoved(int)));
		emit sliderAdded(m_labelCount);
    }
}

//Slot
void MultiSlider::removeSlider()
{
	if(m_labelCount > 0)
	{
		delete m_labels[m_labels.size()-1];
		m_labels.pop_back();
		m_labelCount--;
        emit sliderRemoved();
	}
}

//Slot
void MultiSlider::labelMoved(int index)
{
    emit sliderMovedSignal(index+1);
}