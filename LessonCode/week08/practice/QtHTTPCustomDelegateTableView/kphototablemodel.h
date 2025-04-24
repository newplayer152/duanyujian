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

	// 返回表头表头数据
	virtual QVariant
		headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

	virtual int
		rowCount(const QModelIndex& parent = QModelIndex()) const override; // 返回模型的行数
	virtual int
		columnCount(const QModelIndex& parent = QModelIndex()) const override; // 返回模型的列数

	//返回模型的数据,根据模型索引与数据角色
	virtual QVariant
		data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	//// 设置模型数据，一般由代理来负责调用
	//virtual bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
	// 指定单元格设置一些标志
	virtual  Qt::ItemFlags flags(const QModelIndex& index) const;


private:
	QStringList m_headerData; // 表头数据
	QVector<KPhotos*>    m_contents;
};
#endif