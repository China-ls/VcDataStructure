#pragma once

#include <istream>

#ifndef VOID
#define VOID void
#endif

#ifndef OUT
#define OUT
#endif

#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void *)0)
#endif
#endif

#define VEC_ERROR_SUCCESS 1
#define VEC_ERROR_WRONG_INDEX -1
#define VEC_ERROR_FAIL_TO_EXPANED -2

typedef unsigned long       DWORD;
typedef int                 BOOL;

#ifndef FALSE
#define FALSE               0
#endif

#ifndef TRUE
#define TRUE                1
#endif

template<class T_ELE>
class Vector
{

public:
	Vector();
	Vector(DWORD dwSize);
	~Vector();

public:
	DWORD at(DWORD dwIndex, OUT T_ELE* pEle);
	DWORD push_back(T_ELE Element);
	VOID pop_back(OUT T_ELE* pEle);
	DWORD insert(DWORD dwIndex, T_ELE Element);
	DWORD capacity();
	VOID clear();
	BOOL empty();
	VOID erase(DWORD dwIndex);
	DWORD size();

private:
	BOOL expaned();
private:
	DWORD m_dwIndex;
	DWORD m_dwIncrement;
	DWORD m_dwLen;
	DWORD m_dwInitSize;
	T_ELE* m_pVector;
};

///////////////////////////////////////////////////////////

template<class T_ELE>
Vector<T_ELE>::Vector()
	:m_dwInitSize(20), m_dwIncrement(5)
{
	m_pVector = new T_ELE[m_dwInitSize];
	memset(m_pVector, 0, m_dwInitSize * sizeof(T_ELE));
	m_dwIndex = 0;
	m_dwLen = 0;
}

template<class T_ELE>
Vector<T_ELE>::Vector(DWORD dwSize)
	:m_dwInitSize(dwSize), m_dwIncrement(5)
{
	m_dwIncrement = 5;
	m_pVector = new T_ELE[m_dwInitSize];
	memset(m_pVector, 0, m_dwInitSize * sizeof(T_ELE));
	m_dwIndex = 0;
	m_dwLen = 0;
}
template<class T_ELE>
Vector<T_ELE>::~Vector()
{
	delete[] m_pVector;
}

template<class T_ELE>
DWORD Vector<T_ELE>::at(DWORD dwIndex, OUT T_ELE* pEle)
{
	if (dwIndex < 0 || dwIndex >= m_dwIndex)
	{
		return VEC_ERROR_WRONG_INDEX;
	}
	memcpy(pEle, &m_pVector[dwIndex], sizeof(T_ELE));
	return VEC_ERROR_SUCCESS;
}

template<class T_ELE>
DWORD Vector<T_ELE>::push_back(T_ELE Element)
{
	if (m_dwIndex >= m_dwLen)
	{
		if (!expaned())
		{
			return VEC_ERROR_FAIL_TO_EXPANED;
		}
	}
	memcpy(&m_pVector[m_dwIndex], &Element, sizeof(T_ELE));
	m_dwIndex++;
	return VEC_ERROR_SUCCESS;
}

template<class T_ELE>
VOID Vector<T_ELE>::pop_back(OUT T_ELE* pEle)
{
	if (m_dwIndex <= 0)
	{
		return;
	}
	memcpy(pEle, &m_pVector[m_dwIndex -1], sizeof(T_ELE));
	memset(&m_pVector[m_dwIndex - 1], 0, sizeof(T_ELE));
	m_dwIndex--;
}

template<class T_ELE>
DWORD Vector<T_ELE>::insert(DWORD dwIndex, T_ELE Element)
{
	if (dwIndex < 0)
	{
		return VEC_ERROR_WRONG_INDEX;
	}
	if (m_dwIndex >= m_dwLen)
	{
		if (!expaned())
		{
			return VEC_ERROR_FAIL_TO_EXPANED;
		}
	}
	for (size_t i = m_dwIndex; i > dwIndex; i--)
	{
		memcpy(&m_pVector[i], &m_pVector[i - 1], sizeof(T_ELE));
	}
	memcpy(&m_pVector[dwIndex], &Element, sizeof(T_ELE));
	m_dwIndex++;
	return VEC_ERROR_SUCCESS;
}

template<class T_ELE>
DWORD Vector<T_ELE>::capacity()
{
	return m_dwLen;
}

template<class T_ELE>
VOID Vector<T_ELE>::clear()
{
	memset(m_pVector, 0, sizeof(T_ELE) * m_dwLen);
}

template<class T_ELE>
BOOL Vector<T_ELE>::empty()
{
	return m_dwIndex == 0;
}

template<class T_ELE>
VOID Vector<T_ELE>::erase(DWORD dwIndex)
{
	if (dwIndex < 0 || dwIndex >= m_dwIndex)
	{
		return;
	}
	for (size_t i = dwIndex; i < m_dwIndex -1; i++)
	{
		memcpy(&m_pVector[i], &m_pVector[i + 1], sizeof(T_ELE));
	}
	memset(&m_pVector[m_dwIndex], 0, sizeof(T_ELE));
	m_dwIndex--;
}

template<class T_ELE>
DWORD Vector<T_ELE>::size()
{
	return m_dwIndex;
}

template<class T_ELE>
inline BOOL Vector<T_ELE>::expaned()
{
	DWORD nLen = m_dwLen + m_dwIncrement;
	T_ELE* nDatas = new T_ELE[nLen];
	if (nDatas == NULL)
	{
		return FALSE;
	}
	memset(nDatas, 0, sizeof(T_ELE) * nLen);
	memcpy(nDatas, m_pVector, sizeof(T_ELE) * m_dwLen);
	m_dwLen = nLen;

	delete[] m_pVector;
	m_pVector = nDatas;
	nDatas = NULL;
	return TRUE;
}
