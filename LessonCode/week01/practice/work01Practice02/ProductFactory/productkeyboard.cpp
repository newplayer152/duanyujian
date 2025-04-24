#include "productkeyboard.h"

ProductKeyBoard::ProductKeyBoard()
{
}

ProductKeyBoard::ProductKeyBoard(const ProductKeyBoard& other) {

}

ProductKeyBoard& ProductKeyBoard::operator=(const ProductKeyBoard& other)
{
	return *this;
}

ProductKeyBoard::~ProductKeyBoard()
{
}

void ProductKeyBoard::showProduct()
{
	std::cout << "create keyBoard Product" << std::endl;
}
