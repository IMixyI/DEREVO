#include <iostream>
#include <cmath>
using namespace std;
class MyTrees
{
	struct Uzel
	{
		int data;
		Uzel* per;
		Uzel* men;
		Uzel* bol;
		Uzel(int data, Uzel* ptr) { this->data = data; this->per = ptr; this->men = nullptr; this->bol = nullptr; }
		~Uzel()
		{
			if (this->per != nullptr) { if (this->per->bol == this) { this->per->bol = nullptr; } else if (this->per->men==this){ this->per->men = nullptr; } }
			if (this->men != nullptr) { this->men->per = nullptr; }
			if (this->bol != nullptr) { this->bol->per = nullptr; }
		}
		void destr()
		{
			if (this->men != nullptr)
			{
				this->men->destr();
			}
			if (this->bol != nullptr)
			{
				this->bol->destr();
			}
			delete this;
		}
		int get_lenght(int len, int& maxlen)
		{
			if (this == nullptr) { return 0; }
			if (this->men != nullptr)
			{
				len++;
				if (len > maxlen) { maxlen = len; }
				this->men->get_lenght(len, maxlen);
				if (this->bol != nullptr)
				{
					this->bol->get_lenght(len, maxlen);
				}
			}
			else if (this->bol != nullptr)
			{
				len++;
				if (len > maxlen) { maxlen = len; }
				this->bol->get_lenght(len, maxlen);
			}
			return maxlen + 1;
		}
		void deleteUzel(Uzel* head)
		{
			if (this->data > head->data and head->bol == nullptr)
			{
				if (this->data > this->per->data) { this->per->bol = nullptr; }
				else if (this->data < this->per->data) { this->per->men = nullptr; }
				this->per = head;
				head->bol = this;
			}
			else if (this->data < head->data and head->men == nullptr)
			{
				if (this->data > this->per->data) { this->per->bol = nullptr; }
				else if (this->data < this->per->data) { this->per->men = nullptr; }
				this->per = head;
				head->men = this;
			}
			else if (this->data > head->data and head->bol != nullptr)
			{
				this->deleteUzel(head->bol);
			}
			else if (this->data < head->data and head->men != nullptr)
			{
				this->deleteUzel(head->men);
			}
		}
		void addUzel(int data)
		{
			if (data > this->data and this->bol == nullptr)
			{
				this->bol = new Uzel(data, this);
			}
			else if (data < this->data and this->men == nullptr)
			{
				this->men = new Uzel(data, this);
			}

			else if (data > this->data and this->bol != nullptr)
			{
				this->bol->addUzel(data);
			}

			else if (data < this->data and this->men != nullptr)
			{
				this->men->addUzel(data);
			}
		}
		void Print()
		{
			if (this->men != nullptr)
			{

				if (this->bol != nullptr)
				{
					cout << this->men->data << '(' << this->data << ')' << "  ";
					cout << this->bol->data << '(' << this->data << ')' << "  ";
					cout << endl;
					this->men->Print();
					this->bol->Print();
				}
				else
				{
					cout << this->men->data << '(' << this->data << ')' << "  "; cout << endl;
					this->men->Print();
				}
			}
			else if (this->bol != nullptr)
			{
				cout << this->bol->data << '(' << this->data << ')' << "  " << endl;
				this->bol->Print();
			}
		}
		Uzel* findUzel(int data)
		{
			if (this == nullptr) { return nullptr; }
			if (this->data == data)
			{
				return this;
			}
			else if (data > this->data)
			{
				return this->bol->findUzel(data);
			}
			else if (data < this->data)
			{
				return this->men->findUzel(data);
			}
			return nullptr;
		}
		void foo(Uzel* head)
		{

			if (this->men != nullptr)
			{
				this->men->foo(head);

			}
			this->deleteUzel(head);
			if (this->bol != nullptr)
			{
				this->bol->foo(head);

			}
			this->deleteUzel(head);
		}
		void balance(Uzel* n, MyTrees* t)
		{
			int len1 = 0;
			int len2 = 0;
			int len = 0;
			if (abs(this->men->get_lenght(0, len1) - this->bol->get_lenght(0, len2)) > 1)
			{
				cout << this->data << "dfg" << endl;
				if (this->get_lenght(0, len) == 3)
				{
					if (n->data > n->per->data and n->per->data > this->data)
					{
						if (this->per != nullptr)
						{
							if (this->per->bol == this)
							{
								this->per->bol = n->per;
							}
							else { this->per->men = n->per; }
							n->per->men = n->per->per;
							n->per->per = this->per;
							this->bol = nullptr;
							this->per = n->per;
						}
						else
						{
							t->head = n->per;
							n->per->men = n->per->per;
							n->per->per = this->per;
							this->bol = nullptr;
							this->per = n->per;
							t->head->per = nullptr;
						}
					}
					if (n->data < n->per->data and n->per->data < this->data)
					{
						if (this->per != nullptr)
						{
							if (this->per->bol == this)
							{
								this->per->bol = n->per;
							}
							else { this->per->men = n->per; }
							n->per->bol = n->per->per;
							n->per->per = this->per;
							this->men = nullptr;
							this->per = n->per;
						}
						else
						{
							t->head = n->per;
							n->per->bol = n->per->per;
							n->per->per = this->per;
							this->men = nullptr;
							this->per = n->per;
							t->head->per = nullptr;
						}
					}
					if (n->data > n->per->data and n->data < this->data)
					{
						if (this->per != nullptr)
						{
							if (this->per->bol == this)
							{
								this->per->bol = n;
							}
							else { this->per->men = n; }
							n->bol = this;
							n->men = n->per;
							n->per->bol = nullptr;
							this->men = nullptr;
							n->per->per = n;
							n->per = this->per;
							this->per = n;
						}
						else
						{
							t->head = n;
							n->bol = this;
							n->men = n->per;
							n->per->bol = nullptr;
							this->men = nullptr;
							this->per = n;
							n->per->per = n;
							n->per = this->per;
							t->head->per = nullptr;

						}
					}
					if (n->data < n->per->data and n->data > this->data)
					{
						if (this->per != nullptr)
						{
							if (this->per->bol == this)
							{
								this->per->bol = n;
							}
							else { this->per->men = n; }
							n->men = this;
							n->bol = n->per;
							n->per->men = nullptr;
							this->bol = nullptr;
							n->per->per = n;
							n->per = this->per;
							this->per = n;
						}
						else
						{
							t->head = n;
							n->men = this;
							n->bol = n->per;
							n->per->men = nullptr;
							this->bol = nullptr;
							this->per = n;
							n->per->per = n;
							n->per = this->per;
							t->head->per = nullptr;
						}
					}
					return;
				}
				else
				{
					int len1 = 0;
					int len2 = 0;
					int arr[15];
					for (int i = 0; i < 15; i++)
					{
						arr[i] = -999;
					}
					if (this->bol->get_lenght(0, len1) > this->men->get_lenght(0, len2))
					{
						if (this == t->head)
						{
							t->head = this->bol;
							this->bol->per = nullptr;

							this->massive_remove(arr, this->bol->data, '<');
							int i = 0;
							while (arr[i] != -999)
							{
								t->addUzel(arr[i]);
								i++;
							}
						}
						else
						{
							this->per->bol = this->bol;
							this->bol->per = this->per;
							this->per = nullptr;
							this->massive_remove(arr, this->bol->data, '<');
							int i = 0;
							while (arr[i] != -999)
							{
								t->addUzel(arr[i]);
								i++;
							}
						}
					}
					else if (this->bol->get_lenght(0, len1) < this->men->get_lenght(0, len2))
					{
						if (this == t->head)
						{
							t->head = this->men;
							this->men->per = nullptr;

							this->massive_remove(arr, this->men->data, '>');
							int i = 0;
							while (arr[i] != -999)
							{
								t->addUzel(arr[i]);
								i++;
							}
						}
						else
						{
							this->per->men = this->men;
							this->men->per = this->per;
							this->per = nullptr;
							this->massive_remove(arr, this->men->data, '>');
							int i = 0;
							while (arr[i] != -999)
							{
								t->addUzel(arr[i]);
								i++;
							}
						}
					}
				}
			}
			else if (this->per != nullptr) { this->per->balance(n, t); }
		}
		void massive_delete(int* arr, Uzel* ptr)
		{
			int i = 0;
			while (arr[i] != -999)
			{
				i++;
			}if (this != ptr)
			{

				arr[i] = this->data;
			}
			if (this->men != nullptr)
			{
				this->men->massive_delete(arr, ptr);

			}
			if (this->bol != nullptr)
			{
				this->bol->massive_delete(arr, ptr);
			}
			delete this;
		}
		void massive_remove(int* arr, int p, char sim)
		{
			int i = 0;
			while (arr[i] != -999)
			{
				i++;
			}
			if (sim == '>')
			{
				if (this->data > p)
				{
					arr[i] = this->data;
					if (this->men != nullptr)
					{
						this->men->massive_remove(arr, p, sim);
					}
					if (this->bol != nullptr)
					{
						this->bol->massive_remove(arr, p, sim);
					}

					delete this;
				}
				else
				{
					if (this->men != nullptr)
					{
						this->men->massive_remove(arr, p, sim);
					}
					if (this->bol != nullptr)
					{
						this->bol->massive_remove(arr, p, sim);
					}
				}
			}
			else if (sim == '<')
			{
				if (this->data < p)
				{
					arr[i] = this->data;
					if (this->men != nullptr)
					{
						this->men->massive_remove(arr, p, sim);
					}
					if (this->bol != nullptr)
					{
						this->bol->massive_remove(arr, p, sim);
					}
					delete this;
				}
				else
				{
					if (this->men != nullptr)
					{
						this->men->massive_remove(arr, p, sim);
					}
					if (this->bol != nullptr)
					{
						this->bol->massive_remove(arr, p, sim);
					}
				}
			}
		}
	};
	Uzel* head = nullptr;

public:
	~MyTrees() 
	{
		if (head->men != nullptr) 
		{
			head->men->destr();
		}
		if (head->bol != nullptr)
		{
			head->bol->destr();
		}
		delete head;
	}
	int get_length(int head)
	{
		int maxlen = 0;
		this->findUzel(head)->get_lenght(0,maxlen);
		return maxlen;
	}
	void addUzel(int data)
	{
		if (head == nullptr)
		{
			head = new Uzel(data,nullptr);
		}
		else 
		{
			head->addUzel(data); 
		}
		head->findUzel(data)->balance(head->findUzel(data),this);
	}
	void deleteUzel(int data)
	{
		auto del = head->findUzel(data);
		int arr[15];
		for (int i = 0; i < 15; i++)
		{
			arr[i] = -999;
		}
		if(del->per!=nullptr)
		{
			if (del == del->per->bol) { del->per->bol = nullptr;}
			else if (del == del->per->men) { del->per->men = nullptr;}
			del->massive_delete(arr,del);
			int i = 0;
			while(arr[i]!=-999)
			{
				this->addUzel(arr[i]);
				i++;
			}
		}
		else
		{
			del->massive_delete(arr, del);
			int i = 0;head = nullptr;
			while (arr[i] != -999)
			{
				this->addUzel(arr[i]);
				i++;
			}
		}
	}
	Uzel* findUzel(int data)
	{
		return head->findUzel(data);
	}
	void Print()
	{
		if (head != nullptr)
		{
			cout << head->data << '\n';
			head->Print();
		}
	}
};
int main()
{
	setlocale(0, "");
	MyTrees trees;
	string com;
	int uz;
	cin >> com;
	while (com != "END")
	{
		if (com == "PRINT")
		{
			trees.Print();
		}
		if (com == "ADD")
		{
			cin >> uz;
			trees.addUzel(uz);
			trees.Print();
		}
		if (com == "DELETE")
		{
			cin >> uz;
			trees.deleteUzel(uz);
			trees.Print();
		}
		if (com == "FIND")
		{
			cin >> uz;
			if (trees.findUzel(uz) != nullptr)
			{
				cout << trees.findUzel(uz) << endl;
			}
			else { cout << "Íåò óçëà" << endl; }
		}
		cin>>com;
	}
	return 0;
}
