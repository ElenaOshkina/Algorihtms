//#define _CRTDBG_MAP_ALLOC 
//#ifdef _DEBUG 
//#ifndef DBG_NEW 
//#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
//#define new DBG_NEW 
//#endif 
//#endif  // _DEBUG 
/*#include <stdlib.h>
#include <crtdbg.h> */ 
#include <iostream>
#include <stack>
using namespace std;

//Структура содержит правого и левого потомка текущего узла и информационное поле для данных
//Ссылку на родительский узел
struct Node {
	int data;
	Node *left, * right, *parent;
	Node(int x) {
		data = x;
		left = nullptr;
		right = nullptr;
		parent = nullptr;
	}
};

//Функция для обхода в порядке in-order
void inorder(Node * r) {
	if (r == nullptr) {
		return;
	}
	//будем хранить узлы в stack
	stack<Node *> st;
	Node * node = r;

	//Посетим сначала самый левый узел
	while (node != nullptr) {
		st.push(node);
		node = node->left;
	}
	//Обходим дерево 
	while (st.size() > 0) {
		//Посещаем top node
		node = st.top();
		cout << node->data << " ";
		//Извлекаем из стека
		st.pop();
		if (node->right != nullptr) {
			node = node->right;

			//следующий узел,который будет посещен - снова самый левый
			while (node != nullptr) {
				st.push(node);
				node = node->left;
			}
		}
		delete node;
	}
}

void insert(Node *r, Node *value) {
	while (r != nullptr) {
		//Если вставляемый элемент больше,чем хранимый в root
		if (value->data > r->data) { 
			if (r->right!= nullptr) {
				r = r->right;//спускаемся по правому поддереву
			}
			else {
				value->parent = r; //сохраняем ссылку на родительский узел
				r->right = value;//вставляем узел в дерево
				break; 
			}
		}
		else { 	//Если вставляемый элемент меньше,чем хранимый в root
			if (value->data < r->data) {
				if (r->left != nullptr) {
					r = r->left;//спускаемся по левому поддереву
				}
				else {
					value->parent = r;//сохраняем ссылку на родительский узел
					r->left = value;//вставляем узел в дерево
					break;
				}
			}
		}
	}
}

int main() {
	Node * r;
	int value, N;
	cin >> N >> value;
	r = new Node(value);
	Node *tmp;
	for (int i = 0; i < N-1; i++) {
		cin >> value;
		tmp = new Node(value);
		insert(r, tmp);
	}

	inorder(r);
	delete r;
	//_CrtDumpMemoryLeaks();
	return 0;
}