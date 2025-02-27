#include <iostream>
#include <fstream>
#include <cctype>
using namespace std;

 /*run this program using the console pauser or add your own getch, system("pause") or input loop */
class Node{
public:
	string data;//For the data
	Node* next;//Next pointer
	Node* prev;//Previous Pointer
	Node(string data){//Constructor For Node
		this->data=data;
		this->next=nullptr;
		this->prev=nullptr;
	}
	

};
class DoublyLinkedList{//Class for dunctions of doubly linked list
	public:
		void Insert(Node*& head,Node*& tail, string data){//Inserts, determines where in doubly linked list to insert
			Node* node = new Node(data);//Sets a new node to hold the data constructor
			if(!head){//No other nodes
			node->next = nullptr;//NExt is null, end of list
			node->prev = nullptr;//prev is null, beginning of list
			head=node;//HEad is this node
			tail=node;//tail is this node
			}else if(data < head->data){//Goes to the beginning of the list 
				node->next=head;//Next variable is now the old head
				node->prev=nullptr;//prev variable is null (beginning of the list)
				head->prev=node;//Sets old head node to the new head node 
				head=node;//Head is now the new node that was creatd
			}else if(data > tail->data){//Goes at end of the list
				node->next=nullptr;//Next variable is null(end of list)
				node->prev=tail;//Sets previous pointer to the current tail
				tail->next=node;//Old tails next node goes to new tail
				tail=node;//Tail is now the new node created
			}else{//This is somewhere in the middle of the list
				Node* insertBeforeNode=FindNodePlaceInsert(head,node);//Getting the node to insert before
				node->prev=insertBeforeNode->prev;//sets new node prev pointer to the insert before nodes
				node->next=insertBeforeNode;//new nodes next pointer to insert before node
				if (insertBeforeNode->prev) {//assure its not at head
                insertBeforeNode->prev->next = node;  //node before new node next set to new node
            	}
            	insertBeforeNode->prev = node;//insert before Node prev set to the new node
			}
		}
		void Delete(Node*& head, Node*& tail, string deleteData){//Deletes a node given data to delete
			Node* nodeToDelete=FindNodePlaceDelete(head,deleteData);//Uses FindNodePlaceDelete to find the location of the node and setts tis to the deletion node
			if(nodeToDelete==nullptr){//Node was not found
				return;//return from function, nothing to delete
			}
			if(nodeToDelete->prev==nullptr&&nodeToDelete->next==nullptr){//Only Node in Linnked list
				head=nullptr;//head is null
				tail=nullptr;//tail is null
				delete nodeToDelete;//free memory allocation
				return;//return
			}else if(nodeToDelete->prev!=nullptr&&nodeToDelete->next==nullptr){//node is at the tail of the function
				tail=nodeToDelete->prev;//set tail to the node before
				nodeToDelete->prev->next=nullptr;//set node before to null(its now the tail)
			}else if(nodeToDelete->prev==nullptr){//Its at the head
					head=nodeToDelete->next;//Set head to the node after
					nodeToDelete->next->prev=nullptr;//Set node after to null as it is now the head
			}else{//Nodes in the middle
				nodeToDelete->next->prev=nodeToDelete->prev;//Set node after previous to node vefore
				nodeToDelete->prev->next=nodeToDelete->next;//Set node prev to node after
			}
			delete nodeToDelete;//free memory
			return;//return
		}
		
		Node* FindNodePlaceInsert(Node*head,Node *insertionNode){//Finds the node in which to insert before
			Node* currNode=head;//Sets curr node to head
			bool nodeFound=false;//Boolean to stop the while loop
			while(currNode!=nullptr&&!nodeFound){//Not at the end and its not found
				currNode = currNode->next;//Traverses
				if(insertionNode->data < currNode->data){//Insertion node needs to be inserted before currNode
					nodeFound=true;//True to stop loop
				}
			}
			return currNode;//Return the correct node
			
		}

		Node* FindNodePlaceDelete(Node*head,string dataToDelete){//Finds the node to delte given data
			Node* currNode=head;//starts at head
			while(currNode!=nullptr){//not null
				if(currNode->data==dataToDelete){//if node is found
					return currNode;//Return the node
				}
				currNode = currNode->next;//if not traverse
			}
			return nullptr;//it wasnt found return null
		}
		void PrintFromFront(Node*head,ofstream& toOutput){//Prints out the doubly linked list data  from front to back (Forward Travsersal)
			Node* currNode = head;//Start at fron
			while(currNode != nullptr){//Not at end
				toOutput<<currNode->data<<endl<<"======================"<<endl;//Prints data out
				currNode=currNode->next;//traverses
			}
			return;
		}
		void PrintFromBack(Node*tail){//Prints out the doubly linked list data from back to front
			Node* currNode = tail;//start at back
			while(currNode!= nullptr){//Not at front/end
				cout<<currNode->data<<endl;//Print the nodes data
				currNode=currNode->prev;//Traverse backwards
			}
		}
};

int main() {
	DoublyLinkedList list;//Create a linked list
	Node* head=nullptr;//head pointer
	Node* tail=nullptr;//tail pointer
	ifstream names("input.txt");//creates file stream for input.txt store in a names name
	ofstream namesOut("output.txt");//creates file stream for output.txt to write to
	string nameCommand;//String to hold the name command
	if(names.is_open()){//Did the file open
		while(getline(names,nameCommand)){//read line by line while lines stille exist
			//convert to all lowercase
			for (int i = 0; i < nameCommand.length(); i++) {//Interates through the whole string
    			nameCommand[i] = tolower(nameCommand[i]);//Changes letter to lowercase
			}
			//Check for delete 
			int deleteFuncPos=nameCommand.find("delete");//Setting position for where word delete is
			if(deleteFuncPos != string::npos){//delete was found
				nameCommand.erase(deleteFuncPos,7);//trim delete off of the string, leaving just the name
				list.Delete(head,tail,nameCommand);//delete the name
				
			}else if(deleteFuncPos==string::npos){//delete not found
				list.Insert(head,tail,nameCommand);//insert the name
			}
		}
		//list.PrintFromFront(head);//Traverse from front of list and print
		names.close();
	}else{
		cerr<<"Input File did not open"<<endl;
	}
	if(namesOut.is_open()){//is output file open
		list.PrintFromFront(head,namesOut);
	}else{
		cerr<<"Output File did not open"<<endl;
	}
	
}


