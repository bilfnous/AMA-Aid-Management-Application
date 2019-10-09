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

	AmaApp::AmaApp(const char* filename) {
		strncpy(m_filename, filename, strlen(filename));
		if (m_filename[strlen(filename)] != '\0')
			m_filename[strlen(filename)] = '\0';

		delete[] m_products;
		m_products = nullptr;
		
		m_noOfProducts = 0;
		loadProductRecords();
	}

	AmaApp::~AmaApp() {
		delete[] m_products;
		m_products = nullptr;
	}

	int AmaApp::run() {
		int selection = -1;
		const int max_sku_length = 7;
		while (selection != 0) {

			cout << flush;
			selection = menu();
			switch (selection) {
			case 0:
				cout << "Goodbye!" << endl;
				exit(0);
				break;
			case 1:
				listProducts();
				pause();
				break;
			case 2:
				char sku[max_sku_length];
				cout << "Please enter the product SKU: ";
				cin >> sku;
				cout << endl;
				if (find(sku) != nullptr) {
					find(sku)->write(std::cout);
					cout << endl;
				}
				else {
					cout << "No such product!" << endl;
				}
				pause();
				cout << endl;
				break;
			case 3:
				addProduct('N');
				loadProductRecords();
				break;
			case 4:
				addProduct('P');
				loadProductRecords();
				break;
			case 5:
				char _sku[max_sku_length];
				cout << "Please enter the product SKU: ";
				cin >> _sku;
				cout << endl;
				if (find(_sku) != nullptr) {
					addQty(find(_sku));
				}
				else {
					cout << "No such product!" << endl << endl;
				}
				break;
			case 6:
			case 7:

			default:
				cout << "~~~Invalid selection, try again!~~~" << endl;
				pause();
			}
		}
		return 0;
	}
	
	void AmaApp::pause() const {
		cout << "Press Enter to continue...";
		cin.ignore(1000, '\n');
		cout << endl;
	}
	
	int AmaApp::menu() const {
		int input;

		cout << "Disaster Aid Supply Management Program" << endl
			<< "--------------------------------------" << endl
			<< "1- List products" << endl
			<< "2- Search product" << endl
			<< "3- Add non-perishable product" << endl
			<< "4- Add perishable product" << endl
			<< "5- Add to product quantity" << endl
			<< "6- Delete product" << endl
			<< "7- Sort products" << endl
			<< "0- Exit program" << endl
			<< "> ";
		cin >> input;

		if (input >= 0 && input <= 7) {
			cin.ignore(1000, '\n');
			return input;
		}

		cin.ignore(1000, '\n');
		return -1;
	}
	
	void AmaApp::loadProductRecords() {
		ifstream readfile;
		int idx = 0;
		char buffer[100] = {};
		char tag;

		readfile.open(m_filename, ios::in);

		if (readfile.is_open() && readfile) {
			do {
				if (readfile.eof())
					break;

				//count number of records in the inventory 
				int records = 0;
				ifstream in(m_filename);
				std::string record;
				while (std::getline(in, record))
					records++;

				//create dynamic memory
				m_products = new iGood*[records];

				readfile.getline(buffer, 4, ',');
				tag = buffer[0];
				//If not instance created, null will be returned.
				m_products[idx] = CreateProduct(tag);
				if (m_products[idx] != nullptr) {
					readfile.getline(buffer, 100);
					stringstream ss(buffer);//Converts string array to string stream
					m_products[idx]->read(ss);
					idx++;
				}

			} while (true);
			m_noOfProducts = idx;
			readfile.close();
		}
		else {
			//If the file does not exist, it will create an empty file, close the file and exit.  
			readfile.open(m_filename, ios::out);
			readfile.close();
		}
	}
	
	void AmaApp::saveProductRecords() const {
		ofstream writefile;
		char line = '\n';

		writefile.open(m_filename, ios::out);
		if (writefile.is_open() && writefile) {
			for (int i = 0; i < m_noOfProducts; i++) {
				m_products[i]->write(writefile);
				writefile << line;
			}
			writefile.close();
		}
	}
	
	void AmaApp::listProducts() const {
		double cost = 0, temp = 0;
		cout << "------------------------------------------------------------------------------------------------" << endl
			<< "| Row |     SKU | Product Name     | Unit       |   Price | Tax |   QtyA |   QtyN | Expiry     |" << endl
			<< "|-----|---------|------------------|------------|---------|-----|--------|--------|------------|" << endl;

		for (int i = 0; i < m_noOfProducts; i++) {
			cout << "|" << std::right << setfill(' ') << setw(4) << i + 1 << " |";
			m_products[i]->write(std::cout);
			cout << endl;

			if (m_products[i]->quantity() != 0)
				temp = m_products[i]->total_cost() * m_products[i]->quantity();
			else
				temp = 0;

			cost += temp;
		}

		cout << "------------------------------------------------------------------------------------------------" << endl
			<< "|                                                      Total cost of support ($): | " <<

			std::right << setfill(' ') << setw(10);
		cout.setf(ios::fixed);
		cout.precision(2);
		cout << cost << " |" << endl

			<< "------------------------------------------------------------------------------------------------" << endl << endl;
	}
	
	void AmaApp::deleteProductRecord(iGood* product) {}
	
	void AmaApp::sort() {}
	
	iGood* AmaApp::find(const char* sku) const {
		for (int i = 0; i < m_noOfProducts; i++) {
			if (*m_products[i] == sku) {
				return m_products[i];
			}
		}
		return nullptr;
	}
	
	void AmaApp::addQty(iGood* product) {
		int qty;
		int qtyneed, returned;
		product->write(std::cout);
		cout << endl << endl;
		cout << "Please enter the number of purchased items: ";
		cin >> qty;
		if (cin.fail()) {
			cin.clear();//Clear errors
			cin.ignore();
			cout << "Invalid quantity value!" << endl << endl;
		}
		else {
			if (qty <= product->qtyNeeded()) {
				*product += qty;
				saveProductRecords();
				cout << endl << "Updated!" << endl << endl;
			}
			else if (qty > product->qtyNeeded()) {
				qtyneed = (product->qtyNeeded() - product->quantity());
				returned = (qty - qtyneed);
				*product += (product->qtyNeeded() - product->quantity());

				cout << "Too many items; only " << qtyneed << " is needed. Please return the extra " << returned << " items." << endl;
				saveProductRecords();
				cout << endl << "Updated!" << endl << endl;
			}
		}
	}
	
	void AmaApp::addProduct(char tag) {
		m_products[m_noOfProducts] = CreateProduct(tag);

		if (m_products[m_noOfProducts] != nullptr) {
			cin >> *m_products[m_noOfProducts];
			if (cin.fail()) {
				cout << endl << *m_products[m_noOfProducts] << endl << endl;
				cin.clear();
				cin.ignore();
			}
			else {
				m_noOfProducts++;
				saveProductRecords();
				cout << endl << "Success!" << endl << endl;
			}
		}	
	}

}
