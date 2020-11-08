// 1. Move it outside of BinarySearchTree - make node not a nested class
// 2. Make Node a plain class rather than template class
// 3. template class nested in template class


#include <iostream>


template <typename NodeData>
class BinarySearchTree
{
	// Other parameter than "Data" is needed here
	// because the inner template with the the same template-parameter shadows the outer one,
	// and it's impossible by the standard.
	template <typename Data>
	class Node
	{
	public:
		Node(Data data)
		 :mData(data), mLeft_p(nullptr), mRight_p(nullptr)
		 {};
		Node()
		 :mLeft_p(nullptr), mRight_p(nullptr)
		 {};
		//~Node();
	private:
		Data mData;
		Node<Data>* mLeft_p;
		Node<Data>* mRight_p;
	};

public:
	BinarySearchTree();
	BinarySearchTree(Node<NodeData> node);
	BinarySearchTree(NodeData nodeData);

	// Or make it return bool if the insertion was successful?
	void Insert(NodeData data);

	// Insert with a hint of where to start to search for insertion place
	// could pass root and then it will behave the same as Insert(NodeData)
	// But this (if no special functions encapsulating the getting of Node are implemented) will expose
	// Node implementation detail
	void Insert(NodeData data, Node<NodeData> nodeHint);

	// Iterative and recursive approach can be taken
	// How this should be done for pre-allocated arrays?
	NodeData FindMin();
	NodeData FindMax();

	//~BinarySearchTree();
private:

	Node<NodeData> mRoot;
};


//// I forsee it will be problematic :)
//template <typename NodeData, template<typename> typename Data>
//BinarySearchTree<NodeData>::Node<Data>::Node(data)
//	:mData(data), mLeft_p(nullptr), mRight_p(nullptr)
//{
//}

template <typename NodeData>
BinarySearchTree<NodeData>::BinarySearchTree()
	:mRoot(Node<NodeData>()) // Needs that NodeData type would have default constructor //TODO: Copy ctor for Node is needed
{
}

//TODO: Remove - Node should be kept as an implementation detail and should not be exposed to the user!
template <typename NodeData>
BinarySearchTree<NodeData>::BinarySearchTree(Node<NodeData> node)
	:mRoot(node) // For an use case in which tha BinarySearchTree would be created from a node
	             // But the node is really an implementation detail, so would be better to have a ctor
	             // that creates BinarySearchTree out of NodeData type
{
}

template <typename NodeData>
BinarySearchTree<NodeData>::BinarySearchTree(NodeData nodeData)
	:mRoot(nodeData)
{
}

//TODO: This can also be implemented recursively - take the alternative approach
// Insert(Node*, data)
// if (data <= root->data)
//   root->left = Insert(root->left, data)
//   ...
// the stopping condition is finding the NULL "subtree" or Node
// one more "else" is needed to go to the right subtree
//
template <typename NodeData>
void BinarySearchTree<NodeData>::Insert(NodeData data)
{
	Node<NodeData>* nodeToInsert_p = new Node(data);
	Node<NodeData>** nodePointerIter_p = &mRoot.mLeft_p; // Take the root here!

	// Traverse to the place where the element should be inserted
	while (*nodePointerIter_p != nullptr)
	{
		// Change to data instead of node to insert ptr
		if (data <= (*nodePointerIter_p)->data) // Duplicates will be added to the left side of the subtrees
		{
			nodePointerIter_p = &(*nodePointerIter_p)->mLeft_p;
		}
		else
		{
			nodePointerIter_p = &(*nodePointerIter_p)->mRight_p;
		}
	}

	// Need to alloc the memory for the node
	// Place is found, insert the element - should be a pointer to a pointer
	nodePointerIter_p = &nodeToInsert_p;
}



class outer
{
public:
	int a;
	class inner
	{
		int b;
		int c;
	};
};



// Caching or balancing properties?
// Just adding and letting be balanced if needed?
// Can be done by implementing a validity state and a function that can balance it on demand?
// Pre-allocated nodes? A parameter, which will take care if the locality of a specific set of nodes?
// But there would need to be a map of the connection of nodes?
// Allocate an array of nodes, which would then be accessed and removed and so on

// Function to erase nodes, for which the arrays that are used to hold them are not used fully
// Like a shrink_to_fit for a std::vector?

// Rearrange based on statistics?
// Have a function that will count the cached missed or some access pattern?
// Basic - could take an integer value indicating where is is best to put the node
// Version with moving existing elements and without it could be made

int main()
{
	BinarySearchTree<int> bst;
	std::cout << sizeof(bst) << std::endl;

	outer test;
	std::cout << sizeof(outer) << std::endl;

	test.a = 7;

	outer::inner test2;

	return 0;
}
