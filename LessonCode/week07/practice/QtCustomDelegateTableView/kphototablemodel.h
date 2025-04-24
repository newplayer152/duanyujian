#ifndef __K_STUTABLEMODEL_H_
#define __K_STUTABLEMODEL_H_

#include "photostruct.h"
#include <QAbstractTableModel>
#include <QVector>


class KPhotoTableModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	KPhotoTableModel(QObject* parent);
	~KPhotoTableModel();
	void setContent(QVector<KPhotos*> photos);

	// ���ر�ͷ��ͷ����
	virtual QVariant
		headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

	virtual int
		rowCount(const QModelIndex& parent = QModelIndex()) const override; // ����ģ�͵�����
	virtual int
		columnCount(const QModelIndex& parent = QModelIndex()) const override; // ����ģ�͵�����

	//����ģ�͵�����,����ģ�����������ݽ�ɫ
	virtual QVariant
		data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	//// ����ģ�����ݣ�һ���ɴ������������
	//virtual bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
	// ָ����Ԫ������һЩ��־
	virtual  Qt::ItemFlags flags(const QModelIndex& index) const;


private:
	QStringList m_headerData; // ��ͷ����
	QVector<KPhotos*>    m_contents;
};
#endif