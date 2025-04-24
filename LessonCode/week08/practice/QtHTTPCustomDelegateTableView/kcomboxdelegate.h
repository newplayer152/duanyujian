#ifndef __K_COMBOX_DELEGATE_H__
#define __K_COMBOX_DELEGATE_H__

#include <QStyledItemDelegate>
#include <QComboBox>
#include <QPainter>
#include <QDebug>
class KComboxDelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:
	KComboxDelegate(QObject* parent);
	~KComboxDelegate() = default;
	// ��Ⱦ��Ԫ��
	virtual void
		paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
	// ���ص�Ԫ��༭���
	virtual QWidget* createEditor(QWidget* parent,
		const QStyleOptionViewItem& option, const QModelIndex& index) const override;
	// ��ģ���������õ��༭��
	void setEditorData(QWidget* editor, const QModelIndex& index) const override;
	// ���༭�������ݴ洢��ģ����
	void setModelData(QWidget* editor, QAbstractItemModel* model,
		const QModelIndex& index) const override;
	void updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option,
		const QModelIndex& index) const override;
};

#endif
