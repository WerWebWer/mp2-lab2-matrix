#ifndef __TMATRIX_H__
#define __TMATRIX_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;


template <class ValType>
class TVector {
	protected:
		ValType* pVector;
		int Size;
		int StartIndex;
	public:
		TVector(int s = 5, int si = 0);
		TVector(const TVector <ValType>& v);
		~TVector();
		int GetSize() { return Size; }
		int GetStartIndex() { return StartIndex; }
		ValType& operator[](int pos);
		bool operator==(const TVector<ValType>& v) const;
		bool operator!=(const TVector<ValType>& v) const;
		TVector<ValType>& operator=(const TVector<ValType>& v);
		void Resize(int ns);

		TVector<ValType>   operator+(const ValType& val);
		TVector<ValType>   operator-(const ValType& val);
		TVector<ValType>   operator*(const ValType& val);

		TVector<ValType>  operator+(const TVector<ValType>& v);
		TVector<ValType>  operator-(const TVector<ValType>& v);
		ValType  operator*(const TVector<ValType>& v);

		friend ostream& operator <<(ostream& os, const TVector<ValType>& v) 		{
			os << "{";
			for (int i = 0; i < v.Size - 1; i++) os << v.pVector[i] << ",";
			os << v.pVector[v.Size - 1] << "}";
			return os;
		}
		friend istream& operator >>(istream& is, TVector<ValType>& v) {
			for (int i = 0; i < v.Size; i++) is >> v.pVector[i];
			return is;
		}
		friend const TVector<ValType> operator *(ValType a, TVector<ValType>& w) {
			TVector<ValType> res(w);
			for (int i = 0; i < res.Size; i++) res.pVector[i] *= a;
			return res;
		}
};

template <class ValType>
TVector<ValType>::TVector(int s, int si) {
	if (s > 0 && s <= MAX_VECTOR_SIZE) {
		if (si >= 0) {
			Size = s;
			StartIndex = si;
			pVector = new ValType[Size];
		} else {
			char e[] = "Error";
			throw e;
		}
		
	} else {
		char e[] = "Error";
		throw e;
	}
}

template <class ValType> //copy constructor
TVector<ValType>::TVector(const TVector<ValType> &v) {
	Size = v.Size;
	StartIndex = v.StartIndex;
	pVector = new ValType[Size];
	for (int i = 0; i < Size; i++) pVector[i] = v.pVector[i];
}
template <class ValType>
TVector<ValType>::~TVector() {
	delete[]pVector;
} 
template <class ValType> //access
ValType& TVector<ValType>::operator[](int pos) {
	if (pos >= StartIndex && pos < Size+StartIndex) {
		return pVector[pos - StartIndex];
	} else {
		char e[] = "Error";
		throw e;
	}
} 

template <class ValType> //comparison
bool TVector<ValType>::operator==(const TVector &v) const {
	if (Size != v.Size) return false;
	else {
		for (int i = 0; i < Size; i++) if (pVector[i] != v.pVector[i]) return false;
		return true;
	}
} 

template <class ValType> //comparison
bool TVector<ValType>::operator!=(const TVector& v) const {
	if (Size != v.Size) return true;
	else {
		for (int i = 0; i < Size; i++) if (pVector[i] != v.pVector[i]) return true;
		return false;
	}
}

template <class ValType> //assignment
TVector<ValType>& TVector<ValType>::operator=(const TVector& v) {
	if (this != &v) {
		if (Size != v.Size) {
			Size = v.Size;
			delete[]pVector;
			pVector = new ValType[Size];
		}
		StartIndex = v.StartIndex;
		for (int i = 0; i < Size; i++) pVector[i] = v.pVector[i];
	}
	return *this;
}

template <class ValType>
void TVector<ValType>::Resize(int ns) {
	if (ns > 0) {
		if (Size != ns) {
			ValType* pVector2 = new ValType[ns];
			if (ns < Size) for (int i = 0; i < ns; i++) pVector2[i] = pVector[i];
			else {
				for (int i = 0; i < ns; i++) {
					if (i < Size) pVector2[i] = pVector[i];
					else pVector2[i] = 0;
				}
			}
			delete[]pVector;
			pVector = pVector2;
			Size = ns;
		}
	} else {
		char e[] = "Error";
		throw e;
	}
}

template <class ValType> //add scalar
TVector<ValType> TVector<ValType>::operator+(const ValType& val) {
	TVector<ValType> res(Size, StartIndex);
	for (int i = 0; i < Size; i++) res.pVector[i] = val + pVector[i];
	return res;
}

template <class ValType> //subtract scalar
TVector<ValType> TVector<ValType>::operator-(const ValType& val) {
	TVector<ValType> res(Size, StartIndex);
	for (int i = 0; i < Size; i++)res.pVector[i] = pVector[i] - val;
	return res;
}

template <class ValType> //multiply by scalar
TVector<ValType> TVector<ValType>::operator*(const ValType& val) {
	TVector<ValType> res(Size, StartIndex);
	for (int i = 0; i < Size; i++) res.pVector[i] = val * pVector[i];
	return res;
}

template <class ValType> //addition
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType>& v) {
	if (Size == v.Size) {
		TVector<ValType> res(v);
		for (int i = 0; i < Size; i++) res.pVector[i] = pVector[i] + v.pVector[i];
		return res;
	} else {
		char e[] = "Error";
		throw e;
	}
}

template <class ValType> //subtraction
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType>& v) {
	if (Size == v.Size) {
		TVector<ValType> res(v);
		for (int i = 0; i < Size; i++) res.pVector[i] = pVector[i] - v.pVector[i];
		return res;
	} else {
		char e[] = "Error";
		throw e;
	}
}

template <class ValType> //scalar product
ValType TVector<ValType>::operator*(const TVector<ValType> &v) {
	if (Size == v.Size) {
		ValType sum = 0;
		for (int i = 0; i < Size; i++) sum += pVector[i] * v.pVector[i];
		return sum;
	} else {
		char e[] = "Error";
		throw e;
	}
}

//#######################

//Upper triangular matrix

//#######################

template <class ValType>
class TMatrix : public TVector<TVector<ValType> > {
	public:
		TMatrix(int s = 5);
		TMatrix(const TMatrix& mt);
		TMatrix(const TVector<TVector<ValType> >& mt);
		bool operator==(const TMatrix& mt) const;
		bool operator!=(const TMatrix& mt) const;
		TMatrix& operator= (const TMatrix& mt);
		TMatrix  operator+ (const TMatrix& mt);
		TMatrix  operator- (const TMatrix& mt);


		friend istream& operator>>(istream& in, TMatrix& mt) {
			for (int i = 0; i < mt.Size; i++) in >> mt.pVector[i];
			return in;
		}
		friend ostream& operator<<(ostream& out, const TMatrix& mt) {
			for (int i = 0; i < mt.Size; i++) out << mt.pVector[i] << endl;
			return out;
		}
};

template <class ValType>
TMatrix<ValType>::TMatrix(int s): TVector<TVector<ValType> >(s) {
	if (s >= MAX_MATRIX_SIZE){
		char e[] = "Error";
		throw e;
	} else {
		for (int i = 0; i < Size; i++) {
			TVector<ValType> a(Size - i, i);
			pVector[i] = a;
		}
	}
} 

template <class ValType> //copy constructor
TMatrix<ValType>::TMatrix(const TMatrix<ValType> &mt):
  TVector<TVector<ValType> >(mt) {}

template <class ValType> //type conversion constructor
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> > &mt):
  TVector<TVector<ValType> >(mt) {}

template <class ValType> //comparison
bool TMatrix<ValType>::operator==(const TMatrix<ValType> &mt) const {
	if (Size != mt.Size)return false;
	else {
		for (int i = 0; i < Size; i++) if (pVector[i] != mt.pVector[i]) return false;
		return true;
	}
} 

template <class ValType> //comparison
bool TMatrix<ValType>::operator!=(const TMatrix<ValType> &mt) const {
	if (Size != mt.Size) return true;
	else {
		for (int i = 0; i < Size; i++) if (pVector[i] != mt.pVector[i]) return true;
		return false;
	}
} 

template <class ValType> //assignment
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType> &mt) {
	if (this != &mt) {
		if (Size != mt.Size) {
			delete[]pVector;
			Size = mt.Size;
			pVector = new TVector<ValType>[Size];
		}
		for (int i = 0; i < Size; i++) pVector[i] = mt.pVector[i];
	}
	return *this;
} 

template <class ValType> //addition
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType> &mt) {
		TMatrix<ValType> res(mt);
		for (int i = 0; i < Size; i++) res.pVector[i] = mt.pVector[i] + pVector[i];
		return res;
} 
template <class ValType> //subtraction
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType> &mt) {
	TMatrix<ValType> res(mt);
	for (int i = 0; i < Size; i++) res.pVector[i] = pVector[i] - mt.pVector[i];
	return res;
}
// TVector О3 Л2 П4 С6
// TMatrix О2 Л2 П3 С3
#endif
