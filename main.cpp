#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>
#include <fstream>

using namespace std;
class Huffman
{
public:
	struct Node //the strcuture of each node in tree
	{
		char letter; //letter for each frequency
		int freq; //
		Node* left;
		Node* right;
		Node(char data, int freq) : letter(data), //direct initialization constructor
			freq(freq),
			left(nullptr),
			right(nullptr)
		{}
		~Node()//deconstructor
		{
			delete left;
			delete right;
		}
	};

	struct compare //anytime compare is called it returns a true or false whether left freq greater than right freq
	{
		bool operator()(Node* l, Node* r)
		{
			return (l->freq > r->freq);
		}
	};

	Node* top; //basically the parents

	void printCode(Node* current, string code, vector <string> &stdt,vector <char> &d) //prints and stores Codes for each letter in a vector. vector passed by reference to retain data
	{
		if (current == nullptr) { //this is my out for the recursive function if current is null start going back
			return;
		}
		if (current->letter == '/')// the / is for each letter that the sum of two frequencies that is how to distinguish between letter frequencies and sumation of letter frequencies
		{
			printCode(current->left, code + "0", stdt, d);
			printCode(current->right, code + "1", stdt, d);
		}

		if (current->letter != '/')//not equal so this is for the letters and as you can see the current letter is stored in referenced vector
		{
			cout << current->letter << " : " << code << "\n";
			insert(code, stdt);
			insert(current->letter, d);
			printCode(current->left, code + "0",stdt,d);
			printCode(current->right, code + "1",stdt, d);
		}
		//stdt.push_back(str);

	}
	void insert(string s, vector <string> &std)//overloaded method of adding to vector. push_back in function wouldnt work for some reason
	{
		std.push_back(s);
	}
	void insert(char s, vector <char> &std)
	{
		std.push_back(s);
	}

	Huffman() { //default constructor class
	}
	~Huffman()//deconstructor class
	{
		delete top;
	}

	void getCode(vector<char>& data, vector<int>& freq, int size, vector <string> &stdt, vector <char> &d)//I kept methods in class because i was lazy. But getCode gets the code for each frequency and stores in vector. It uses printcode
	{
		Node* left;
		Node* right;//left and right children
		priority_queue<Node*, vector<Node*>, compare > minHeap; //this is a built in queue that makes this project a whole lot easier. Its parameters are a type of object, vector of the object and puts them in order from highest to lowest frequencies
		for (int i = 0; i < size; ++i)
		{
			minHeap.push(new Node(data[i], freq[i])); //adds new node in queue
		}

		while (minHeap.size() != 1) //this makes the tree
		{
			left = minHeap.top();
			minHeap.pop();

			right = minHeap.top();
			minHeap.pop();

			top = new Node('/', left->freq + right->freq);
			top->left = left;
			top->right = right;
			minHeap.push(top);
		}
		cout << "Binary Tree Order (NOT SORTED): " << endl;
		printCode(minHeap.top(), "", stdt, d); //function above

	}
};
int setFromFile(int* frequency, char* letter) { //sets frequency and letter array from file
	int temp;
	ifstream file;
	file.open("test1.txt"); //opens file
	int i = 0;
	bool t=false;
	if (file.is_open()) { //checks if open
		while (!file.eof()) //while not at EOF
		{
			file >> letter[i];
			while (letter[i] >= 48 && letter[i] <= 57) //if it starts with a number ignore it
			{
				file >> temp; //add it to a temporary basically eraser
				file >> letter[i]; //then take next value until its a character
				t = true;
			}
			file >> frequency[i]; //then insert freq
			i++;
		}
		if(t==true)i--;
	}
	else
		cout << "unopened"; //file not found
	return i; //size of samples
}

string decoder(vector <string> freq, vector <char> data, int size)
{
	ifstream file;
	file.open("test2.txt"); //second file
	string line;
	string code="";//start code empty
	int i = 0;
	int t = 0;
	bool val=true;
	int j = 0;
	if (file.is_open()) {
		while (!file.eof())
		{
			file >> line;//take in line
		}
	}
	else
		cout << "unopened";

	while (t < line.length()) { //this whole 3 loop thing keeps increasing the size of string until it matches one of the encoded letters
		while (val==true)
		{
			for (int x = 0; x < size; x++) {
			//	cout << j << endl;
				if (line.substr(t, j) == freq[x] && t + j <= line.length())
				{
					code += data[x]; //then adds the letter in this string
					t = t + j;
					val = false;
				}
				else if (t + j > line.length())
					val = false;
			}
			j++;
		}
		val = true;
		j = 0;
		i++;
	}


	return code; //returns it to main
}

void sort(int n, vector <char> &a) { //sorts using insertion

		int i, key, j;
		for (i = 1; i < n; i++)
		{
			key = a[i];
			j = i - 1;
			while (j >= 0 && a[j] > key)
			{
				a[j + 1] = a[j];
				j = j - 1;
			}
			a[j + 1] = key;
		}

}
void add(vector <string> s, vector <char> c, vector <char> r,vector <string> &f) {
	for(int j=0;j<c.size();j++) {
		for (int i = 0; i < c.size(); i++) {
			if (c[i] == r[j])
			{
				f.push_back(s[i]); //makes in alphabetical order arranges string vector with char vector
			}
		}
	}
}
int main()
{
	Huffman huff;
	int* frequency = new int[52]; //creates 52 ints and chars
	char* letter = new char[52];
	vector <int> freq; //freq vector data d and freq1 are all for retaining values from class
	vector <char> data;
	vector <char> d;

	vector <string> freq1;
	int numSamples;
	numSamples = setFromFile(frequency, letter); //gets values from file
	for (int i = 0; i < numSamples; i++)
	{
		freq.push_back(frequency[i]);// push frequency and data
		data.push_back(letter[i]);
	}
	int size = data.size();
	huff.getCode(data, freq, size,freq1,d);//gets binary code
	int count = freq1.size();
	string code = decoder(freq1, d, count);//gets codeword from decoder
	//sort(size, d);
	vector <string> f;
	add(freq1, d, data, f);
	cout << "Alphabetical Order: " << endl;
	for (int i = 0; i < size; i++)
		cout << data[i] << " : "<<f[i]<<endl; //prints out sorted vector
	cout << endl;
	cout << "CODEWORD: ";
	cout << code << endl;//prints it
	return 0;
}
