#include <Python.h> // For usage of Python in C++.

#include <fstream> // File Stream for reading and writing files.
#include <iostream> // Input/Output Stream.
#include <iomanip> // Manipulation of Input/Output.
#include <string> // For using strings.
#include <vector> // For using vectors.

using namespace std; // To make declarations easier.

/*
* void CallProcedure()
* To call this function, pass the name of the Python function
* you wish to call and the string parameter you want to send.
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("CornerGrocerPy");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
* int callIntFunc()
* To call this function, pass the name of the Python function
* you wish to call and the string parameter you want to send.
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"CornerGrocerPy");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
* void Specifics()
* Provides a list of all items currently available.
* Asks for user to specify a word. 
* You can still type something that isn't on
* the list to make FOR CERTAIN that it isn't there.
* 
* OUTPUT: There are _ sales of 'userInputWord' for today.
* 
* Then it pauses the screen until a key is pressed so that
* the screen can be examined by the user.
*/
void Specifics() {
	string specificWord;

	// ItemsList is a Python Function in the "CornerGrocerPy.py" file.
	CallProcedure("ItemsList");

	cout << "Enter a word from the list: ";
	cin >> specificWord;

	cout << "There are " <<
		// PrintSpecificFrequencies is a Python Function in the "CornerGrocerPy.py" file.
		callIntFunc("PrintSpecificFrequencies", specificWord) << " "
		<< "sales of '" << specificWord
		<< "' for today." << endl;

	// Pauses the Screen until a key is pressed on the keyboard.
	system("pause");
}

/*
* void HistogramPlusFiles()
* Prints what will be saved to frequency.dat.
* Saves the file frequency.dat.
* Opens saved file frequency.dat.
* 
* Reads file line by line, saving contents to
* the two vectors 'fAmounts' and 'fItems'.
* 
* Displays a Histogram of the file frequency.dat.
*/
void HistogramPlusFiles() {
	unsigned int i;
	unsigned int j;
	ifstream fItemsFS;
	int amount;
	string item;
	vector<int> fAmounts;
	vector<string> fItems;

	// SaveDat is a Python Function in the "CornerGrocerPy.py" file.
	CallProcedure("SaveDat");
	// Pauses the Screen until a key is pressed on the keyboard.
	system("pause");

	// Open file that list was saved to.
	fItemsFS.open("C:\\Users\\dougl\\Desktop\\frequency.dat");

	// If file is already in use. Cease the activity.
	if (!fItemsFS.is_open()) {
		cout << "Could not open the file frequency.dat." << endl;
	}
	else {
		fItemsFS >> item;
		fItemsFS >> amount;

		// If it can proceed, it saves each item to their respective vector.
		while (!fItemsFS.fail()) {
			fItems.push_back(item);
			fAmounts.push_back(amount);

			fItemsFS >> item;
			fItemsFS >> amount;
		}
		// Close the file so that it can be used by other applications.
		fItemsFS.close();
	}
	// 'system("cls")' clears the console.
	system("cls");

	cout << "Thank you for using the Corner Grocer Software!" << endl;
	cout << "Histogram for the file frequency.dat:" << endl << endl;

	// This for loop Displays the histogram using the saved vectors.
	for (i = 0; i < fItems.size(); i++) {
		// 'setw(15)' sets width for the field 
		// 'right' aligns all items to the right side of the field.
		cout << setw(15) << fItems.at(i) << right;
		for (j = 0; j < fAmounts.at(i); j++) {
			cout << '*';
		}
		cout << endl;
	}
	// Pauses the Screen until a key is pressed on the keyboard.
	system("pause");
}

/*
* void ExitProtocol()
* Makes sure that the user meant to exit the Program.
*/
void ExitProtocol(char& keepGoing, int& userChoice) {
	while (userChoice == 4) {
		string confirmation;

		cout << "Are you sure you wish to exit the Corner Grocer program? Y or N" << endl;
		getline(cin, confirmation);

		if ((confirmation == "y") || (confirmation == "Y")) {
			keepGoing = 'n';
			break;
		}
		else if ((confirmation == "n") || (confirmation == "N")) {
			keepGoing = 'y';
			break;
		}
		else {
			cout << "Please Enter Y or N." << endl;
		}
	}
}

/*
* void MainLoop()
* Displays UI for user choices.
* Gets input from user to execute what user wants from list.
* Displays what is requested by user.
*/
void MainLoop() {
	char keepGoing = 'y';

	// Infinite loop to keep the program going.
	while (keepGoing == 'y') {
		int userChoice;

		cout << "Thank you for using the Corner Grocer Software!" << endl;
		cout << " __________________________________" << endl;
		cout << "|1. All Item Frequencies           |" << endl;
		cout << "|2. Display Certain Item Frequency |" << endl;
		cout << "|3. View Frequency Histogram       |" << endl;
		cout << "|4. Exit Program                   |" << endl;
		cout << "|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|" << endl;

		cin >> userChoice;

		// The next two lines are used to clear the input buffer.
		// This makes it possible to do better input validation.
		cin.clear();
		cin.ignore(5000, '\n');

		if (userChoice == 1) {
			// PrintFrequencies is a Python Function in the "CornerGrocerPy.py" file.
			CallProcedure("PrintFrequencies");
			// Pauses the Screen until a key is pressed on the keyboard.
			system("pause");
		}
		else if (userChoice == 2) {
			// Executes the 'Specifics' function.
			Specifics();
		}
		else if (userChoice == 3) {
			// Executes the 'HistogramPlusFiles' function.
			HistogramPlusFiles();
		}
		else if (userChoice == 4) {
			// Executes the 'ExitProtocol' function.
			ExitProtocol(keepGoing, userChoice);
		}
		else {
			cout << "That was an invalid choice." << endl;
			// Pauses the Screen until a key is pressed on the keyboard.
			system("pause");
		}
		// 'system("cls")' clears the console.
		system("cls");
	}
}

/*
* This is where our code starts! THE MAIN FUNCTION.
*/
int main()
{
	// Executes the 'MainLoop' function.
	MainLoop();
	cout << "Thank you for using the Corner Grocer Software!";
	//ALWAYS END ON A GOOD NOTE.
	return 0;
}
