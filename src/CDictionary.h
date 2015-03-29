/*  libscratch - Multipurpose objective C++ library.
    Copyright (C) 2012 - 2013  Angelo Geels

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>. */

#ifndef SCRATCH_CDICTIONARY_H_INCLUDED
#define SCRATCH_CDICTIONARY_H_INCLUDED

#include "Common.h"
#include "CStackArray.h"

SCRATCH_NAMESPACE_BEGIN;

template<class TKey, class TValue>
class SCRATCH_EXPORT CDictionaryPair
{
public:
  TKey* key;
  TValue* value;

  CDictionaryPair();
  ~CDictionaryPair();
};

template<class TKey, class TValue>
class SCRATCH_EXPORT CDictionary
{
private:
  CStackArray<TKey> dic_saKeys;
  CStackArray<TValue> dic_saValues;

public:
  BOOL dic_bAllowDuplicateKeys;

public:
  CDictionary(void);
  CDictionary(const CDictionary<TKey, TValue> &copy);
  ~CDictionary(void);

  /// Add to the dictionary
  void Add(const TKey &key, const TValue &value);

  /// Get the index of the given key
  INDEX IndexByKey(const TKey &key);
  /// Get the index of the given value
  INDEX IndexByValue(const TValue &value);

  /// Does this dictionary have the given key?
  BOOL HasKey(const TKey &key);
  /// Does this dictionary have the given value?
  BOOL HasValue(const TValue &value);

  /// Remove a value by its index
  void RemoveByIndex(const INDEX iIndex);
  /// Remove a value from the dictionary by key
  void RemoveByKey(const TKey &key);
  /// Remove a value from the dictionary
  void RemoveByValue(const TValue &value);

  /// Pop a value by its index
  CDictionaryPair<TKey, TValue> PopByIndex(const INDEX iIndex);
  /// Pop a value from the dictionary by key
  CDictionaryPair<TKey, TValue> PopByKey(const TKey &key);
  /// Pop a value from the dictionary
  CDictionaryPair<TKey, TValue> PopByValue(const TValue &value);

  /// Clear all items
  void Clear(void);

  /// Return how many objects there currently are in the dictionary
  INDEX Count(void);

  TValue& operator[](const TKey &key);
  
  /// Get a key from the dictionary using an index
  TKey& GetKeyByIndex(const INDEX iIndex);
  /// Get a value from the dictionary using an index
  TValue& GetValueByIndex(const INDEX iIndex);
};

SCRATCH_NAMESPACE_END;

#include "CDictionary.cpp"

#endif
