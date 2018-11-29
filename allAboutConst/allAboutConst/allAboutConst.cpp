// allAboutConst.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

class A {
public:
	 A(){};
	~A(){};

	int func(int& x){
		std::cout << "'int func(int& x)' " << "is called. " ;
		this->a++;				/* allowed */
		this->p = &x;			/* allowed */
		// this->aConst++;		/* NOT allowed: the value of const member cannot be changed. */
		// this->pConst = &x;	/* NOT allowed: the value of const member cannot be changed. */
		x++;                    /* allowed */
		return x;
	}

	int func(const int &x){
		std::cout << "'int func(const int &x)' " << "is called. ";
		this->a++;				/* allowed */
		return x;
	}

	int func(int& x) const{
		std::cout << "'int func(int& x) const' " << "is called. ";
		//this->a++;			/* NOT allowed */
		x++;                    /* allowed */
		this->b++;				/* allowed because b is mutable*/
		return x;
	}

	int func(const int& x) const{
		std::cout << "'int func(const int& x) const' " << "is called. ";
		//this->a++;				/* NOT allowed */
		//x++;						/* NOT allowed */
		const_cast<A*>(this)->a++;	/* allowed by casting*/
		return x;
	}
	 
	int func(int* p){
		std::cout << "'int func(int* p)' " << "is called. ";
		(*p)++;                    /* allowed */
		return *p;
	}

	int func(const int* p){
		std::cout << "'int func(const int* p)' " << "is called. ";
		//(*p)++;                    /* NOT allowed */
		return *p;
	}

	int func(int* p) const {
		std::cout << "'int func(int* p) const' " << "is called. ";
		(*p)++;                    /* allowed */
		return *p;
	}

	int func(const int* p) const {
		std::cout << "'int func(const int* p) const' " << "is called. ";
		//(*p)++;                    /* NOT allowed */
		return *p;
	}

	// const int& func(int& x)      /* NOT allowed */
	// int func(int x);             /* NOT allowed */
	// int func(const int& x);		/* NOT allowed as "func(const int& x) const" is defined */
	// int func(int& x);			/* NOT allowed as "int func(int x)" is defined */
	// int func(int& x) const;		/* NOT allowed as "int func(const int& x) const" is defined */

	const int* const gFunc(const int& x) const {
		std::cout << "'const int* const gFunc(const int& x) const' " << "is called. ";		
		return &x;
	}

public:
	mutable int  b    = 0;
	int a             = 0;
	const int aConst  = 0;
	int* p            = nullptr;
	int* const pConst = nullptr;

};


int main(int argc, _TCHAR* argv[])
{
	int x = 0;
	int y = 0;

	const int  xConst = 0;

	int*       pX ;					    // variable pointer variable data
	int* const pConstX = &x;			// fixed pointer variable data (same as const* int)	(has to be initialized)
	const int* pXConst;					// variable pointer fixed data (same as int const*)
	const int* const pConstXConst = &x; // fixed pointer fixed data (same as int const* const) (has to be initialized)

	A s;
	const A sConst;

	// let's check gFunc()
	const int* const qConstXConst = s.gFunc(x); 
	//  *qConstXConst++;  /* NOT allowed */
	// (*qConstXConst)++; /* NOT allowed */

	std::cout << std::endl;

	// lets check s
	pX      = &x;
	std::cout << "*pX -> " << *pX << " and pX " << pX << std::endl;
	std::cout << "*pConstX -> " << *pConstX << " and pConstX " << pConstX << std::endl;
	std::cout << " s.func(pConstX)     -> "; y = s.func(pConstX);      std::cout << " out value is : " << y << std::endl;
	std::cout << " s.func(pX)          -> "; y = s.func(pX);      std::cout << " out value is : " << y << std::endl;
	std::cout << " s.func(x)           -> "; y = s.func(x);           std::cout << " out value is : " << y << std::endl;
	std::cout << " s.func(xConst)      -> "; y  = s.func(xConst);      std::cout << " out value is : " << y << std::endl;

	std::cout << std::endl;

	//lets check sConst
	pX = &x;
	std::cout << "*pX -> " << *pX << " and pX " << pX << std::endl;
	std::cout << "*pConstX -> " << *pConstX << " and pConstX " << pConstX << std::endl;
	std::cout << " sConst.func(pConstX)-> "; y = sConst.func(pConstX);      std::cout << " out value is : " << y << std::endl;
	std::cout << " sConst.func(pX)     -> "; y = sConst.func(pX);      std::cout << " out value is : " << y << std::endl;
	std::cout << " sConst.func(x)      -> "; y = sConst.func(x);      std::cout << " out value is : " << y << std::endl;
	std::cout << " sConst.func(xConst) -> "; y = sConst.func(xConst); std::cout << " out value is : " << y << std::endl;


	std::cout << std::endl;

	return 0;
}

