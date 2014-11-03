#include "multiexposure.h"


MultiExposure::MultiExposure(QWidget *parent)
	: QWidget(parent)
{
	layout = new QVBoxLayout(this);
	sl = new MultiSlider(this);
    ml = new MultiLabel(this);
    ml->attachMultiSlider(sl);
    //sl->setFixedWidth(500);
    layout->addWidget(ml);
    layout->addWidget(sl);
	this->setLayout(layout);
}

MultiExposure::~MultiExposure()
{
	delete sl;
	delete ml;
	delete layout;
}

void MultiExposure::addSlider()
{
	sl->addSlider();	
}

void MultiExposure::removeSlider()
{
	sl->removeSlider();
}

void MultiExposure::setRange(int min, int max)
{
	sl->setRange(min, max);
}

QVector<int> MultiExposure::values()
{
	return sl->values();
}