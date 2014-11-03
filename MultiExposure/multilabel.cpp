#include "multilabel.h"

MultiLabel::MultiLabel(QWidget *parent) :
    QAbstractSlider(parent)
{
    this->setOrientation(Qt::Horizontal);
    this->setTracking(false);
    m_height = 30;
    m_width = 15;
    this->setFixedHeight(m_height);
}

MultiLabel::~MultiLabel()
{
    for(int i=0; i<m_labels.size(); i++)
        delete m_labels[i];
    m_labels.clear();
}

void MultiLabel::attachMultiSlider(MultiSlider* msl)
{
    m_mlsObj = msl;
    int sliderCount = m_mlsObj->sliderCount();
    for( int i=0; i<sliderCount; i++)
    {
        QString val = QString::number(m_mlsObj->sliderVal(i));
        QLabel* label = new QLabel(val, this);
        label->setFixedHeight(m_height);
        //label->setFixedWidth(m_width);
        label->setAlignment(Qt::AlignCenter);
        label->setStyleSheet("QLabel { background-color : #cccccc; color : black; border:2px;}");
        label->move(m_mlsObj->sliderPos(i));
        m_labels.push_back(label);
    }

    connect(m_mlsObj, SIGNAL(sliderMovedSignal(int)), this, SLOT(labelMoved(int)));
    connect(m_mlsObj, SIGNAL(sliderAdded(int)), this, SLOT(sliderAdded(int)));
    connect(m_mlsObj, SIGNAL(sliderRemoved()), this, SLOT(sliderRemoved()));
    connect(m_mlsObj, SIGNAL(resized()), this, SLOT(updateLabels()));
}

void MultiLabel::sliderAdded(int index)
{
    QString val = QString::number(m_mlsObj->sliderVal(index));
    QLabel* label = new QLabel(val, this);
	label->setStyleSheet("QLabel { background-color : #cccccc; color : black; border:2px;}");
    label->setFixedHeight(m_height);
    label->setFixedWidth(m_width);
    label->setAlignment(Qt::AlignCenter);
    label->move(m_mlsObj->sliderPos(index));
	label->setShown(true);
    m_labels.push_back(label);
}

void MultiLabel::labelMoved(int index)
{
    QString val = QString::number(m_mlsObj->sliderVal(index));
    m_labels[index]->setText(val);
	m_labels[index]->resize(m_labels[index]->minimumSizeHint());
    m_labels[index]->move(m_mlsObj->sliderPos(index));
}

void MultiLabel::sliderRemoved()
{
    delete m_labels[m_labels.size()-1];
    m_labels.pop_back();
}

void MultiLabel::updateLabels()
{
    for( int i=0; i<m_labels.size(); i++)
    {
        QString val = QString::number(m_mlsObj->sliderVal(i));
        m_labels[i]->setText(val);
        m_labels[i]->move(m_mlsObj->sliderPos(i));
	}
}
