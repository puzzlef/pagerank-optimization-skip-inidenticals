#pragma once
#include <vector>
#include <unordered_map>
#include <iterator>
#include <algorithm>
#include <functional>

using std::vector;
using std::unordered_map;
using std::iterator_traits;
using std::hash;
using std::back_inserter;
using std::set_difference;
using std::count;
using std::count_if;
using std::find;




// FIND
// ----

template <class J, class T>
auto find(const J& x, const T& v) {
  return find(x.begin(), x.end(), v);
}

template <class J, class T>
int findIndex(const J& x, const T& v) {
  auto i = find(x.begin(), x.end(), v);
  return i==x.end()? -1 : i-x.begin();
}




// COUNT-*
// -------

template <class J, class T>
int count(const J& x, const T& v) {
  return count(x.begin(), x.end(), v);
}


template <class I, class F>
int countIf(I ib, I ie, F fn) {
  return count_if(ib, ie, fn);
}

template <class J, class F>
int countIf(const J& x, F fn) {
  return count_if(x.begin(), x.end(), fn);
}




// INDICES
// -------

template <class I>
auto indices(I ib, I ie) {
  using K = typename iterator_traits<I>::value_type;
  unordered_map<K, int> a; int i = 0;
  for (I it=ib; it!=ie; ++it)
    a[*it] = i++;
  return a;
}

template <class J>
auto indices(J&& x) {
  return indices(x.begin(), x.end());
}




// SET-DIFFERENCE
// --------------

template <class L, class J, class K>
void setDifference(L&& a, J&& x, K&& y) {
  set_difference(x.begin(), x.end(), y.begin(), y.end(), a.begin());
}

template <class T, class J, class K>
void setDifference(vector<T>& a, J&& x, K&& y) {
  set_difference(x.begin(), x.end(), y.begin(), y.end(), back_inserter(a));
}

template <class J, class K>
auto setDifference(J&& x, K&& y) {
  using I = decltype(x.begin());
  using T = typename iterator_traits<I>::value_type;
  vector<T> a; setDifference(a, x, y);
  return a;
}




// TO-*
// ----

template <class T, class I>
void toVector(vector<T>& a, I ib, I ie) {
  a.clear();
  for (I it=ib; it!=ie; ++it)
    a.push_back(*it);;
}

template <class I>
auto toVector(I ib, I ie) {
  using T = typename I::value_type;
  vector<T> a; toVector(a, ib, ie);
  return a;
}

template <class T, class J>
void toVector(vector<T>& a, const J& x) {
  toVector(a, x.begin(), x.end());
}

template <class J>
void toVector(const J& x) {
  return toVector(x.begin(), x.end());
}




// HASH-VALUE
// ----------

template <class T, class I>
size_t hashValue(vector<T>& vs, I ib, I ie) {
  size_t a = 0;
  toVector(vs, ib, ie);
  sort(vs.begin(), vs.end());
  for (const T& v : vs)
    a ^= hash<T>{}(v) + 0x9e3779b9 + (a<<6) + (a>>2); // from boost::hash_combine
  return a;
}

template <class I>
size_t hashValue(I ib, I ie) {
  using T = typename I::value_type;
  vector<T> vs;
  return hashValue(vs, ib, ie);
}

template <class T, class J>
size_t hashValue(vector<T>& vs, const J& x) {
  return hashValue(vs, x.begin(), x.end());
}

template <class J>
size_t hashValue(const J& x) {
  return hashValue(x.begin(), x.end());
}
