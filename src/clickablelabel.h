#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H



class clickablelabel : public QLabel
{
Q_OBJECT
public:
    explicit clickablelabel(QWidget* parent);
    ~clickablelabel();
signals:
    void clicked();
protected:
    void mousePressEvent(QMouseEvent* event);
};


#endif
