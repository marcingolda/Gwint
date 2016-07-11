#include "clickablelabel.h"

clickablelabel::clickablelabel(QWidget* parent) : QLabel(parent) {}

clickablelabel::~clickablelabel() {}

void clickablelabel::mousePressEvent(QMouseEvent* event)
{
    emit clicked();
}
