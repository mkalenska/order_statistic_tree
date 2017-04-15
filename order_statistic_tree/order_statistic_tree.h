#pragma once
#include <string>

struct				car_model{
	std::string		name;
	std::string		brand;
	int				number;
};

class RedBlackTree {
    class Node{
        Node *rightChild = nullptr;
        Node *leftChild = nullptr;
        Node *parent = nullptr;
		car_model data;
        bool color;
		int size;
    public:
        Node():data(),color(false){
        }
		Node(car_model d){
            data = d;
            color = true;
			size = 1;
        }
		int getData(){
            return data.number;
        }
		car_model getAllData(){
			return data;
		}
        bool isRed(){
            return color;
        }
		void setData(car_model d){
            data = d;
        }
        void toBlack(){
            color = false;
        }
        void toRed(){
            color = true;
        }
        Node *getLeftChild(){
            return leftChild;
        }
        Node *getRightChild(){
            return rightChild;
        }
        Node *getBrother(){
            return parent->getLeftChild() == this ? parent->getRightChild() : parent->getLeftChild();
        }
        Node *getParent(){
            return parent;
        }
        Node *getUncle(){
            Node * grandparent = getGrandparent();
            return parent->isLeftChild() ? grandparent->getRightChild() : grandparent->getLeftChild();
        }
        Node *getGrandparent(){
            Node * parent = getParent();
            return parent->getParent();
        }
        bool isLeftChild(){
            return bool(data.number <= parent->getData());
        }
        void setLeftChild(Node * lChild){
            leftChild = lChild;
        }
        void setRightChild(Node * rChild){
            rightChild = rChild;
        }
        void setParent(Node * par){
            parent = par;
        }
		void setSize(int s){
			size = s;
		}
		int getSize(){
			return size;
		}
    }
	
	*root = nullptr;
    
    int leaves = 0;
    
    void rotateLeft(Node * rotateNode){
        Node * parent = rotateNode->getParent();
        Node * rChild = rotateNode->getRightChild();
        if (parent) {
            if (rotateNode->isLeftChild())
                parent->setLeftChild(rChild);
            else parent->setRightChild(rChild);
        } else root = rChild;
        rotateNode->setRightChild(rChild->getLeftChild());
        if (rChild->getLeftChild()) {
            Node * child = rChild->getLeftChild();
            child->setParent(rotateNode);
        }
        rotateNode->setParent(rChild);
        rChild->setLeftChild(rotateNode);
        rChild->setParent(parent);
    }
    
    void rotateRight(Node * rotateNode){
        Node * parent = rotateNode->getParent();
        Node * lChild = rotateNode->getLeftChild();
        rotateNode->setLeftChild(lChild->getRightChild());
        if (lChild->getRightChild()) {
            Node * child = lChild->getRightChild();
            child->setParent(rotateNode);
        }
        rotateNode->setParent(lChild);
        lChild->setRightChild(rotateNode);
        lChild->setParent(parent);
        if (parent) {
            if (lChild->isLeftChild())
                parent->setLeftChild(lChild);
            else parent->setRightChild(lChild);
        } else root = lChild;
    }
    
    void insertCase1(Node * insertedNode){
        Node * parent = insertedNode->getParent();
        if (parent->isRed()) {
            insertCase2(insertedNode);
        }
    }
    
    void insertCase2(Node * insertedNode){
        Node * uncle = insertedNode->getUncle();
        Node * parent = insertedNode->getParent();
        if (uncle && uncle->isRed() && parent->isRed()) {
            Node * grandparent = parent->getParent();
            uncle->toBlack();
            parent->toBlack();
            grandparent->toRed();
            if (grandparent->getParent()){
                insertCase1(grandparent);
            } else grandparent->toBlack();
        }
        else insertCase3(insertedNode);
    }
    
    void insertCase3(Node * insertedNode){
        Node * parent = insertedNode->getParent();
        if (parent->isLeftChild() && !(insertedNode->isLeftChild())) {
            rotateLeft(parent);
            insertedNode = parent;
        } else if (!(parent->isLeftChild()) && insertedNode->isLeftChild()) {
            rotateRight(parent);
            insertedNode = parent;
        }
        insertCase4(insertedNode);
    }
    
    void insertCase4(Node * insertedNode){
        Node * grandparent = insertedNode->getGrandparent();
        Node * parent = insertedNode->getParent();
        grandparent->toRed();
        parent->toBlack();
        if (insertedNode->isLeftChild() && parent->isLeftChild()){
            rotateRight(grandparent);
        } else{
            rotateLeft(grandparent);
        }
    }
    
    void deleteCase1(Node * deletedNode){
        if (!deletedNode->getParent()) {
            return;
        }
        Node * brother = deletedNode->getBrother();
        if (brother->isRed()) {
            Node * parent = deletedNode->getParent();
            parent->toRed();
            brother->toBlack();
            if (deletedNode->isLeftChild()) {
                rotateLeft(parent);
            } else {
                rotateRight(parent);
            }
        }
        deleteCase2(deletedNode);
    }
    
    void deleteCase2(Node * deletedNode){
        Node * parent = deletedNode->getParent();
        Node * brother = deletedNode->getBrother();
        Node * left = brother->getLeftChild();
        Node * right = brother->getRightChild();
        bool lChild = false, rChild = false;
        
        if (left) {
            lChild = left->isRed();
        }
        if (right) {
            rChild = right->isRed();
        }
        if (!parent->isRed() && !brother->isRed() && !lChild && !rChild) {
            brother->toRed();
            deleteCase1(parent);
        } else if (parent->isRed() && !brother->isRed() && !lChild && !rChild) {
            brother->toRed();
            parent->toBlack();
        } else {
            if (deletedNode->isLeftChild() && !rChild && lChild) {
                brother->toRed();
                left->toBlack();
                rotateRight(brother);
            } else if (!deletedNode->isLeftChild() && !lChild && rChild) {
                brother->toRed();
                right->toBlack();
                rotateLeft(brother);
            }
            if (parent->isRed())
                brother->toRed();
            else
                brother->toBlack();
            parent->toBlack();
            
            if (deletedNode->isLeftChild()) {
                right->toBlack();
                rotateLeft(parent);
            } else {
                left->toBlack();
                rotateRight(parent);
            }
        }
    }
    
    Node * findMin(Node * ptrToNode){
        while (ptrToNode->getLeftChild() != nullptr)
            ptrToNode = ptrToNode->getLeftChild();
        return ptrToNode;
    }
    
    Node * findMax(Node * ptrToNode){
        while (ptrToNode->getRightChild() != nullptr)
			ptrToNode = ptrToNode->getRightChild();
		leaves -= 1;
		return ptrToNode;
    }
	
	int getHeight(Node *startNode){
		if (!startNode)
			return 0;
		int heightLeft = getHeight(startNode->getLeftChild()), heightRight = getHeight(startNode->getRightChild());
		return (heightLeft > heightRight ? heightLeft : heightRight) + 1;
	}
	void showRedBlackTree(Node* startNode, int level = 0){
		std::cout << startNode->getAllData().brand << "  " << startNode->getAllData().name << "  " << startNode->getAllData().number << std::endl;
		if (startNode->isRed()) std::cout << "red\n";
		else std::cout << "black\n";
		std::cout << "size: " << startNode->getSize() << std::endl;
		std::cout << "level: " << level << std::endl << std::endl;

		level++;
		if (startNode->getLeftChild())
			showRedBlackTree(startNode->getLeftChild(), level);
		if (startNode->getRightChild())
			showRedBlackTree(startNode->getRightChild(), level);
	}
public:
    RedBlackTree(){
    }
	RedBlackTree(car_model data){
        root = new Node(data);
        root->toBlack();
    }
	void deleteRedBlackTree(Node* nodeToDelete){
		if (nodeToDelete){
			deleteRedBlackTree(nodeToDelete->getLeftChild());
			deleteRedBlackTree(nodeToDelete->getRightChild());
			delete nodeToDelete;
		}
	}
    ~RedBlackTree(){
		deleteRedBlackTree(root);
        leaves = 0;
    }
    
	void setAllSize(Node* cur){
		if (!cur->getLeftChild() && !cur->getRightChild()){
			cur->setSize(1);
			return;
		}

		int s = 1;
		if (cur->getLeftChild()){
			setAllSize(cur->getLeftChild());
			s += cur->getLeftChild()->getSize();
		}
		if (cur->getRightChild()){
			setAllSize(cur->getRightChild());
			s += cur->getRightChild()->getSize();
		}

		cur->setSize(s);
	}

	Node* search(car_model dataToSearch){
        Node * ptrToNode = root;
        while (ptrToNode != nullptr) {
            if (dataToSearch.number > ptrToNode->getData())
                ptrToNode = ptrToNode->getRightChild();
            else if (dataToSearch.number < ptrToNode->getData())
                ptrToNode = ptrToNode->getLeftChild();
			else
			{
				if (ptrToNode != nullptr) 
					std::cout << ptrToNode->getSize() << "  " << ptrToNode->getAllData().name << "  " << ptrToNode->getAllData().brand;
				return ptrToNode;
			}
        }
		if (ptrToNode != nullptr)
			std::cout << ptrToNode->getSize() << "  " << ptrToNode->getAllData().name << "  " << ptrToNode->getAllData().brand;
        return ptrToNode;
    }
    
	void insert(car_model dataToInsert){
        if (search(dataToInsert)) {
            return;
        }
        
        if (root == nullptr) {
            root = new Node(dataToInsert);
            root->toBlack();
            leaves++;
            return;
        }
        
        Node * NodeToInsert = new Node(dataToInsert);
        Node * ptrToNode = root;
        while (ptrToNode != nullptr){
            NodeToInsert->setParent(ptrToNode);
            if (NodeToInsert->getData() > ptrToNode->getData()) {
                ptrToNode = ptrToNode->getRightChild();
            } else {
                ptrToNode = ptrToNode->getLeftChild();
            }
        }
        Node * parent = NodeToInsert->getParent();
        if (NodeToInsert->getData() < parent->getData())
            parent->setLeftChild(NodeToInsert);
        else
            parent->setRightChild(NodeToInsert);
        insertCase1(NodeToInsert);

		setAllSize(root);
        leaves++;
    }
    
	void deleteElement(car_model dataToDelete){
        Node * ptrToDelete = search(dataToDelete);
        if (!ptrToDelete) {
            return;
        }
        if (ptrToDelete->getLeftChild() && ptrToDelete->getRightChild()) {
            Node * predecessor = findMax(ptrToDelete->getLeftChild());
            ptrToDelete = predecessor;
        }
        Node * child = ptrToDelete->getLeftChild() ? ptrToDelete->getLeftChild() : ptrToDelete->getRightChild();
        Node * parent = ptrToDelete->getParent();
        if (parent == nullptr) {
            root = child;
            if (child) {
                child->toBlack();
                child->setParent(nullptr);
            }
        } else if (ptrToDelete->isRed()) {
            if (ptrToDelete->isLeftChild())
                parent->setLeftChild(nullptr);
            else
                parent->setRightChild(nullptr);
        } else if (child) {
            child->toBlack();
            if (ptrToDelete->isLeftChild())
                parent->setLeftChild(child);
            else
                parent->setRightChild(child);
            child->setParent(parent);
        } else  {
            deleteCase1(ptrToDelete);
            if (ptrToDelete->isLeftChild())
                parent->setLeftChild(child);
            else
                parent->setRightChild(child);
            if (child) child->setParent(parent);
        }
        delete ptrToDelete;

		setAllSize(root);
        leaves -= 1;
    }

	int getHeight() {
		return getHeight(root);
	}

	void show(){
		showRedBlackTree(root);
	}
};