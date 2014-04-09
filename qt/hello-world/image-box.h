
#include <QWidget>
#include <QLabel>

class ImageBox : public QWidget
{
public:
    ImageBox(QWidget *parent = 0);
    ~ImageBox();
private:
    QLabel * label;
};
