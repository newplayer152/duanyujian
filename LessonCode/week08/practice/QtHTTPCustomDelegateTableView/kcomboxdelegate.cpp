#include "kcomboxdelegate.h"


KComboxDelegate::KComboxDelegate(QObject* parent)
	:QStyledItemDelegate(parent)
{}


void KComboxDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	if (index.column() == 3) // ��ȡͼ������
	{
		// ��ģ���л�ȡ QPixmap ����
		QImage pixmap = index.model()->data(index, Qt::UserRole).value<QImage>();
		qDebug() << "Loaded image size: " << index.model()->data(index, Qt::UserRole);
		qDebug() << "Loaded image size: " << pixmap.size();
		if (!pixmap.isNull()) {
			// ����ͼ��
			QSize imageSize = pixmap.size();
			QRect imageRect = option.rect;
			imageRect.setSize(imageSize.scaled(imageRect.size(), Qt::KeepAspectRatio));
			qDebug() << pixmap.size();
			// ����ͼ��
			painter->drawImage(imageRect, pixmap);
		}
		else {
			qDebug() << -1;
		}
	}

	// ���ø��෽��������������
	QStyledItemDelegate::paint(painter, option, index);
}


//�༭��Ԫ�񣬷���һ���������
QWidget* KComboxDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{

	//if (index.column() == 1)
	//{
	//	QComboBox* pcombox = new QComboBox(parent);

	//	pcombox->addItem("Male");
	//	pcombox->addItem("Female");
	//	pcombox->setCurrentIndex(0);

	//	return pcombox;
	//}
	return QStyledItemDelegate::createEditor(parent, option, index);
}

// ��ģ���е����ݸ�ֵ���༭�ؼ���
void KComboxDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
	////��ģ���л�ȡ���ݸ�ֵ���༭�ؼ��� 
	//if (index.column() == 1)
	//{
	//	// ��ģ���л�ȡ��һ�е�����
	//	QString gender = index.model()->data(index, Qt::EditRole).toString();
	//	// ��ֵ���ؼ���
	//	QComboBox* pcombox = static_cast<QComboBox*>(editor);
	//	int currentIndex = pcombox->findText(gender);

	//	if (currentIndex >= 0)
	//		pcombox->setCurrentIndex(currentIndex);
	//}
	//else
		QStyledItemDelegate::setEditorData(editor, index);
}

//���ؼ��е����ݴ洢��ģ����
void KComboxDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
	////����1�е����ݴ洢��ģ����
	//if (index.column() == 1)
	//{
	//	QComboBox* pcombox = static_cast<QComboBox*>(editor);
	//	// �ӿؼ��ϻ�ȡ����
	//	QVariant data = pcombox->currentText();
	//	// ����ȡ�����ݴ洢��ģ����
	//	model->setData(index, data, Qt::EditRole);
	//}
	//else
		QStyledItemDelegate::setModelData(editor, model, index);// ����������У������ʹ��Ĭ��ί�������
}

void KComboxDelegate::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	editor->setGeometry(option.rect);
}