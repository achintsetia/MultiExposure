#ifndef MULTIEXPOSURE_H
#define MULTIEXPOSURE_H

#include <QtGui/QWidget>
#include <QVBoxLayout>

#include "multislider.h"
#include "multilabel.h"

class MultiExposure : public QWidget
{
	Q_OBJECT

public:
	MultiExposure(QWidget *parent = 0);
	~MultiExposure();
	QVector<int> values();

private:
	QVBoxLayout* layout;
	MultiSlider* sl;
    MultiLabel* ml;

public slots:
	void addSlider();
	void removeSlider();
	void setRange(int min, int max);
};

#endif // MULTIEXPOSURE_H
