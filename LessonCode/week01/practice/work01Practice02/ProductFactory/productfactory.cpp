#include "productfactory.h"
#include "productmouse.h"
#include "productkeyboard.h"


Product* ProductFactory::CreateProduct(ProduceID id)
{
	switch (id) {

	case ProduceID::MouseProduce:{
		ProductMouse* pm = new ProductMouse();
			return pm;
	}
	case ProduceID::KeyBoardProduce:{
		ProductKeyBoard* pkb = new ProductKeyBoard();
			return pkb;
	}
	default:
			return nullptr;
	}

	return nullptr;
}
