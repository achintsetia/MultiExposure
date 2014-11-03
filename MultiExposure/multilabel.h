#ifndef MULTILABEL_H
#define MULTILABEL_H

#include <QAbstractSlider>
#include <QLabel>
#include "movablelabel.h"
#include "multislider.h"

class MultiLabel : public QAbstractSlider
{
    Q_OBJECT
public:
    explicit MultiLabel(QWidget *parent = 0);
    ~MultiLabel();
    void attachMultiSlider(MultiSlider* msl);

private:
    QVector<QLabel*>    m_labels;
    MultiSlider*        m_mlsObj;
    int                 m_height;
    int                 m_width;

public slots:
    void labelMoved(int index);
    void sliderAdded(int index);
    void sliderRemoved();
    void updateLabels();
};

#endif // MULTILABEL_H
