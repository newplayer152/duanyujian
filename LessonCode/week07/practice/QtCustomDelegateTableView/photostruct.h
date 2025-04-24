#ifndef __K_KPHOTO_H_
#define __K_KPHOTO_H_

#include<QString>
#include<QImage>

struct KPhotos{
	int m_albumId;
	int m_id;
	QString m_title;
	QImage  m_pixmap;
};


#endif//__K_KPHOTO_H_
