/*
*	AMA Interface
*	AmaApp.cpp
*	Date 2019-10-08
*	Auther B. Alfanous
*/

#include"iGood.h"

#ifndef AMA_AmaApp_H
#define AMA_AmaApp_H

namespace ama {

	class AmaApp {
		// An array of iGood pointers 
		//(i.e. each element of this array is a pointer to a dynamically allocated instance of type iProduct).
		iGood* m_products[100];
		//Holds the name of the text file used to store the product information.
		char m_filename[256];
		//Number of products (perishable or non-perishable) pointed to by the m_products array.
		int m_noOfProducts;


		AmaApp(const AmaApp& source) = delete;
		AmaApp& operator=(const AmaApp& source) = delete;
		void pause() const;
		int menu() const;
		void loadProductRecords();
		void saveProductRecords() const;
		void listProducts() const;
		void deleteProductRecord(iGood* product);
		void sort();
		iGood* find(const char* sku) const;
		void addQty(iGood* product);
		void addProduct(char tag);


	public:
		AmaApp(const char*);
		~AmaApp();
		int run();

	};
}

#endif
