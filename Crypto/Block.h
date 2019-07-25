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
	string ToString() {
		stringstream ss;
		ss << this->id << Constants::Strings::Separators::space << this->ownerId;
		return ss.str();
	}


};
ostream& operator<<(ostream& os, Block block)
{
	os << block.ToString();
	return os;
}
