# AMA-Aid-Management-Application

When disaster hits a populated area, the most critical task is to provide immediately affected people with what they need as quickly and as efficiently as possible.

This project creates an application that manages the list of goods that need to be shipped to a disaster area. The application tracks the quantity of items needed, tracks the quantity on hand, and stores the information in a file for future use.

There are two categories for the types of goods that need to be shipped:
* Non-Perishable goods, such as blankets and tents, which have no expiry date. We refer to goods in this category as Good objects.
* Perishable goods, such as food and medicine, that have an expiry date. We refer to goods in this category as Perishable objects.

## To Run the Project
**Windows** 
* Download the repository
* Create a C++ project with your compiler of choice *i.e. Visual Studio*
* Add .cpp files to your *Resource Files* and add .h files to your *Header Files*
* Go to project properties within the compiler and make sure to add `inventory.txt` file as command argument  
* Compile the program and run it

<br>

**Linux**
* Download the repository
* Go to the directory that has the project files and makefile
* Run the command `make` 
* Type `ama` to the run the program and make sure to add `inventory.txt` as an argument
