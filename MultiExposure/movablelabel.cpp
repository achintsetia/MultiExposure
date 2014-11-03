#include "movablelabel.h"
#include "multislider.h"

MovableLabel::MovableLabel(QWidget *parent, QPoint position, int index) :
    QLabel(parent)
{
    this->setPixmap(QPixmap(":/GelStanChemi/handle.png"));
    MultiSlider* p = dynamic_cast<MultiSlider*> (this->parent());
    m_labels = p->getLabelList();
	this->move(mapToParent(position));
	m_index = index;
	this->setShown(true);
}

void MovableLabel::mousePressEvent(QMouseEvent *ev)
{
    m_offset = ev->pos();
}

void MovableLabel::mouseMoveEvent(QMouseEvent *ev)
{
    if(ev->buttons() & Qt::LeftButton)
    {        
        QPoint p(ev->pos()-m_offset);
        p.setY(0);
		MultiSlider* parent = dynamic_cast<MultiSlider*> (this->parent());
		//m_index == 0 means first label
		QPoint lp = parent->getLastPos(m_index);
		QPoint np = parent->getNextPos(m_index);
		if(p.x() < 0 && this->pos().x()+p.x() > lp.x()+5) //Moving to the left
			this->move(mapToParent(p));
		else if( p.x() > 0 && this->pos().x()+p.x()<np.x()-5)
			this->move(mapToParent(p));
		emit labelMoved(this->m_index);
	}
}
