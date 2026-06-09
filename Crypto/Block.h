#pragma once
#include "pch.h"
#include "SHA1.h"
class Block
{
private:
	/// <summary>
	/// ID в виде хэш SHA-1
	/// </summary>
	string id;
	/// <summary>
	/// ID владельца в виде хэш SHA-1 
	/// </summary>
	string ownerId;
	string idStr = "ID:";
	string ownerIdStr = "onwer id:";
public:
	/// <summary>
	/// Создает блок с указанным ID и ID владельца
	/// </summary>
	/// <param name="id">ID в виде хэш SHA-1</param>
	/// <param name="ownerId">ID владельца в виде хэш SHA-1 </param>
	Block(string id = Constants::Strings::undefined, string ownerId = Constants::Strings::undefined) {
		this->id = id;
		this->ownerId = ownerId;
	}
	/// <summary>
	/// Создает блок с указанным ID и ID владельца
	/// </summary>
	/// <param name="id">ID в виде целого числа</param>
	/// <param name="ownerId">ID владельца в виде хэш SHA-1 </param>
	Block(long id, string ownerId = Constants::Strings::undefined) {
		this->id = SHA1().GetHash(to_string(id));
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
	/// <summary>
	/// Задает ID в виде хэш SHA-1
	/// </summary>
	/// <param name="id">ID в виде хэш SHA-1</param>
	void SetId(string id) {
		this->id = id;
	}
	/// <summary>
	/// Получает ID в виде хэш SHA-1
	/// </summary>
	/// <returns></returns>
	string GetId() {
		return this->id;
	}
	/// <summary>
	/// Задает ID владельца в виде хэш SHA-1
	/// </summary>
	/// <param name="ownerId">ID владельца в виде хэш SHA-1 </param>
	void SetOwnerId(string ownerId) {
		this->ownerId = ownerId;
	}
	/// <summary>
	/// Получает ID владельца в виде хэш SHA-1
	/// </summary>
	/// <returns></returns>
	string GetOwnerId() {
		return this->ownerId;
	}
};


#pragma region Операторы
bool operator==(Block& b1, Block& b2) {
	return b1.GetId() == b2.GetId();
}
ostream& operator<<(ostream& os, Block block)
{
	os << block.ToString();
	return os;
}
#pragma endregion
