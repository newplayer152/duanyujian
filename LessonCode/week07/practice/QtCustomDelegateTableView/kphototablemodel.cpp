#include "kphototablemodel.h"

KPhotoTableModel::KPhotoTableModel(QObject* parent)
	: QAbstractTableModel(parent)
{
}

KPhotoTableModel::~KPhotoTableModel()
{

}

void KPhotoTableModel::setContent(QVector<KPhotos*> photos)
{
	m_contents = photos;
}

QVariant KPhotoTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role != Qt::DisplayRole)
		return QVariant();

	if (orientation == Qt::Horizontal)
	{
		switch (section)
		{
		case 0:
			return QString("albumId");
		case 1:
			return QString("id");
		case 2:
			return QString("title");
		case 3:
			return QString(u8"ͼƬ");
		default:
			break;

		}
	}
	return QVariant();
}

// ���ػ���ĳ���������µ�����,����Ǳ��ģ�ͣ�����������Чʱ�᷵��0
int KPhotoTableModel::rowCount(const QModelIndex& parent) const
{
	return parent.isValid() ? 0 : m_contents.size();
}
int KPhotoTableModel::columnCount(const QModelIndex& parent) const
{
	return parent.isValid() ? 0 : 4;
}

QVariant KPhotoTableModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid())
		return QVariant();

	if (index.row() >= m_contents.size() || index.row() < 0)
		return QVariant();

	if (role == Qt::DisplayRole || role == Qt::UserRole)// Qt::UserRole����ͼƬ��Ϣ
	{
		const auto& photo = m_contents.at(index.row());
		switch (index.column())
		{
		case 0:
			return photo->m_albumId;
		case 1:
			return photo->m_id;
		case 2:
			return photo->m_title;
		case 3:
			return  QVariant::fromValue(photo->m_pixmap);
		default:
			break;
		}

	}

	return QVariant();
}


//bool KPhotoTableModel::setData(const QModelIndex& index, const QVariant& value, int role)
//{
//	if (!index.isValid())
//		return false;
//
//	if (index.row() >= m_contents.size() || index.row() < 0)
//		return false;
//
//	if (role == Qt::EditRole) // ���ñ༭ʱ������
//	{
//		const auto& photo = m_contents.at(index.row());
//		switch (index.column())
//		{
//
//		case 0:
//			return photo->m_albumId= value.toInt();
//		case 1:
//			return photo->m_id = value.toInt();
//		case 2: {
//			photo->m_title = value.toString();
//			return true;
//		}
//			
//		case 3: {
//			photo->m_pixmap=;//�������ô�޸�
//			return true;
//		}
//		default:
//			break;
//		}
//	}
//
//	return true;
//}

Qt::ItemFlags KPhotoTableModel::flags(const QModelIndex& index) const
{
	if (!index.isValid())
		return Qt::NoItemFlags;
	Qt::ItemFlags defaultFlags = QAbstractTableModel::flags(index);

	//if (index.column() == 1)
	//	return defaultFlags | Qt::ItemIsEditable; // ���ڵ�һ�����ӱ༭��־
	//else
	//	return defaultFlags;

	return defaultFlags;

}