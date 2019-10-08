/*
*	AMA Interface
*	AmaApp.cpp
*	Date 2019-10-08
*	Auther B. Alfanous
*/


#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "iGood.h"
#include "AmaApp.h"



using namespace std;
namespace ama {
	AmaApp::AmaApp(const char* filename) {}

	AmaApp::~AmaApp() {}

	int AmaApp::run() {}
	
	void AmaApp::pause() const {}
	
	int AmaApp::menu() const {}
	
	void AmaApp::loadProductRecords() {}
	
	void AmaApp::saveProductRecords() const {}
	
	void AmaApp::listProducts() const {}
	
	void AmaApp::deleteProductRecord(iGood* product) {}
	
	void AmaApp::sort() {}
	
	iGood* AmaApp::find(const char* sku) const {}
	
	void AmaApp::addQty(iGood* product) {}
	
	void AmaApp::addProduct(char tag) {}

}
