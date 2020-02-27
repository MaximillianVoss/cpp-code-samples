#pragma once
#include "pch.h"
class Block
{
private:
	string idStr = "ID:";
	string ownerIdStr = "onwer id:";
public:
	/// <summary>
	/// ИД
	/// </summary>
	string id;
	/// <summary>
	/// ИД владельца
	/// </summary>
	string ownerId;
	/// <summary>
	/// 
	/// </summary>
	Block() {
	}
	/// <summary>
	/// 
	/// </summary>
	/// <param name="id"></param>
	Block(string id) {
		this->id = id;
	}
	/// <summary>
	/// 
	/// </summary>
	/// <param name="id"></param>
	Block(string id, string ownerId) {
		this->id = id;
		this->ownerId = ownerId;
	}
	/// <summary>
	/// 
	/// </summary>
	~Block() {
	}
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	string ToString(bool detailed = false) {
		stringstream ss;
		if (!detailed)
			ss << this->id << Constants::Strings::Separators::space << this->ownerId;
		else
			ss << this->idStr << this->id << Constants::Strings::Separators::space << this->ownerIdStr << this->ownerId;
		return ss.str();
	}


};


#pragma region Операторы
bool operator==(Block& b1, Block& b2) {
	return b1.id == b2.id && b1.ownerId == b2.ownerId;
}
ostream& operator<<(ostream& os, Block block)
{
	os << block.ToString();
	return os;
}
#pragma endregion
