/*
 * CArray
*/

#pragma once

#include <vector>
#include <iostream>

struct CExceptionWrongIndex
{
	CExceptionWrongIndex()
	{
	}
};

// Vector index
typedef int INDEX;
//

template <class T> class CRMMVArray
{

	// Array
public:
	typedef std::vector<T> TVECTOR;
protected:
	TVECTOR tVector;
	//

	// Constructor
public:
	CRMMVArray()
	{
		RemoveAll();
	}
	CRMMVArray(const CRMMVArray & SS)
	{
		this->RemoveAll();
		for (INDEX i = 0; i < SS.GetCount(); i++) this->Add(SS.GetAt(i));
	}
	static CRMMVArray<T> GetEmptyArray() { CRMMVArray<T> array; return array; }
	// Destructor
public:
	~CRMMVArray()
	{
		RemoveAll();
	}
	// Overloaded operators
public:
	CRMMVArray & operator = (const CRMMVArray & SS)
	{
		this->RemoveAll();
		for (INDEX i = 0; i < SS.GetCount(); i++) this->Add(SS.GetAt(i));
		return * this;
	}
	bool operator == (const CRMMVArray & SS)
	{
		if (SS.GetCount() != this->GetCount()) return false;
		//
		for (INDEX i = 0; i < SS.GetCount(); i++)
		{
			int found = 0;
			for (INDEX j = 0; j < this->GetCount(); j++)
			{
				if (SS.GetAt(j) == this->GetAt(i))
				{
					found = 1;
					break;
				}
			}
			if (!found) return 0;
		}
		return true;
	}
	bool operator != (const CRMMVArray & SS)
	{
		return !(operator==(SS));
	}
	CRMMVArray & operator - (const CRMMVArray & SS)
	{
		for (INDEX i = 0; i < SS.GetCount(); i++)
		{
			INDEX index = this->Find(SS.GetAt(i));
			if (this->CheckIndex(index)) this->RemoveAt(index);
		}
		return * this;
	}
	//

	

	// Members
public:
	INDEX GetCount() const
	{
		return (INDEX)tVector.size();
	}
	INDEX CheckIndex(const INDEX nIndex) const 
	{
		return ( (nIndex >= 0) && (nIndex < GetCount()) );
	}
	//
	T GetLast() const
	{
		if (!CheckIndex(0)) throw CExceptionWrongIndex();
		return tVector.back();
	}
	T GetFirst() const
	{
		if (!CheckIndex(0)) throw CExceptionWrongIndex();
		return tVector.front();
	}
	T GetAt(const INDEX nIndex) const
	{
		if (!CheckIndex(nIndex)) throw CExceptionWrongIndex();
		return tVector.at(nIndex);
	}
	T GetAtNonConst(const INDEX nIndex)
	{
		if (!CheckIndex(nIndex)) throw CExceptionWrongIndex();
		return tVector.at(nIndex);
	}
	INDEX Find(const T element) const
	{
		for (INDEX nIndex = 0; nIndex < GetCount(); nIndex++)
		{
			if (GetAt(nIndex) == element) return nIndex;
		}
		return -1;
	}
	//
	void Add(const T newElement)
	{
		tVector.push_back(newElement);
	}
	int AddUnique(const T newElement)
	{
		int nIndex = Find(newElement);
		if (!CheckIndex(nIndex))
		{
			Add(newElement);
			return 1;
		}
		return 0;
	}
	void SetAt(const INDEX nIndex, const T newElement)
	{
		if (!CheckIndex(nIndex)) throw CExceptionWrongIndex();
		tVector[nIndex] = newElement;
	}
	void InsertAt(const INDEX nIndex, const T newElement)
	{
		if (!CheckIndex(nIndex-1)) throw CExceptionWrongIndex();
		tVector.insert(tVector.begin() + nIndex, newElement);
	}
	//
	void RemoveAll()
	{
		tVector.erase(tVector.begin(), tVector.end());
	}
	void RemoveAt(const INDEX nIndex)
	{
		if (!CheckIndex(nIndex)) throw CExceptionWrongIndex();
		tVector.erase(tVector.begin() + nIndex);
	}
	void RemoveLast()
	{
		if (!CheckIndex(0)) throw CExceptionWrongIndex();
		tVector.pop_back();
	}
	void RemoveElement(const T element)
	{
		INDEX index = Find(element);
		while (index != -1)
		{
			RemoveAt(index);
			index = Find(element);
		}
	}
	//
};

