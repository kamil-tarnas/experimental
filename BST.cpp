// 1. Move it outside of BinarySearchTree - make node not a nested class
// 2. Make Node a plain class rather than template class
// 3. template class nested in template class


#include <iostream>
#include <cstring>
//TODO: Copy-wise elements
// this header includes too much and element-wise copy will be probably compiled to memcpy like routine in asm

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
	//private:
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

	std::size_t MaxDepth(Node<NodeData>* node_p);
	std::size_t MaxDepth();
	std::size_t MaxDepth_iterative();

	//~BinarySearchTree();
private:

	Node<NodeData>* mRoot;
};


//// I forsee it will be problematic :)
//template <typename NodeData, template<typename> typename Data>
//BinarySearchTree<NodeData>::Node<Data>::Node(data)
//	:mData(data), mLeft_p(nullptr), mRight_p(nullptr)
//{
//}

template <typename NodeData>
BinarySearchTree<NodeData>::BinarySearchTree()
	:mRoot(nullptr) // Needs that NodeData type would have default constructor //TODO: Copy ctor for Node is needed
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
	Node<NodeData>* nodeToInsert_p = new Node<NodeData>(data);
	Node<NodeData>** nodePointerIter_p = &mRoot; // Take the root here!

	// If tree was created and root is newly a nullptr
	if (mRoot == nullptr)
	{
		mRoot = nodeToInsert_p;
		return;
	}

	// Traverse to the place where the element should be inserted
	// TODO: In first step it is not - if initial root value is assigned
	while (*nodePointerIter_p != nullptr)
	{
		// Change to data instead of node to insert ptr
		if (data <= (*nodePointerIter_p)->mData) // Duplicates will be added to the left side of the subtrees
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
	*nodePointerIter_p = nodeToInsert_p;
}

// Depth should be understood as the number of edges - in the opposite to height (?)
// Without a helper - default argument
template <typename NodeData>
std::size_t BinarySearchTree<NodeData>::MaxDepth(Node<NodeData>* node_p)
{
	if (node_p == nullptr)
	{
		return 0;
	}
	if (node_p->mLeft_p == nullptr && node_p->mRight_p == nullptr)
	{
		return 1;
	}
	else
	{
		std::size_t leftSubtree = MaxDepth(node_p->mLeft_p);
		std::size_t rightSubtree = MaxDepth(node_p->mRight_p);
		return 1 + (leftSubtree > rightSubtree ? leftSubtree : rightSubtree);
	}

}

// TODO: Are those two functions really needed?
// OMG... (not possible to do default parameter MaxDepth(Node<NodeData>* node_p = mRoot)
template <typename NodeData>
std::size_t BinarySearchTree<NodeData>::MaxDepth()
{
	//TODO: The common part could be wrapped in a subroutine
	Node<NodeData>* node_p = mRoot;
	if (node_p == nullptr)
	{
		return 0;
	}
	if (node_p->mLeft_p == nullptr && node_p->mRight_p == nullptr)
	{
		return 0; // Should return one if we do not count the edges
	}
	else
	{
		std::size_t leftSubtree = MaxDepth(node_p->mLeft_p);
		std::size_t rightSubtree = MaxDepth(node_p->mRight_p);
		return (leftSubtree > rightSubtree ? leftSubtree : rightSubtree);
	}

}

template <typename NodeData>
std::size_t BinarySearchTree<NodeData>::MaxDepth_iterative()
{
	Node<NodeData>** node_pp = &mRoot;

	// Allocate space for a stack of nodes
	// Push on stack the address of a node
	// 20 is an arbitrary number
	Node<NodeData>* nodeStack = new Node<NodeData>*[20];
	std::size_t currentStackLimit = 20;
	std::size_t currentStackSize = 0;

	std::size_t leftSubtreeSize = 0;
	std::size_t rightSubtreeSize = 0;
	std::size_t treeDepth = 0;

	if (currentStackSize == currentStackLimit)
	{
		Node<NodeData>* oldStorage = nodeStack;
		Node<NodeData>* newStorage = new Node<NodeData>*[currentStackLimit * 2];
		std::memcpy(newStorage, oldStorage, sizeof(Node<NodeData>) * currentStackLimit);
		delete oldStorage;
		nodeStack = newStorage;
		currentStackLimit *= 2;
	}

	while (*node_pp != nullptr)
	{
		// GO LEFT, IF NULLPTR POP AND GO RIGHT, SET THE POINTER TO LEFT, REPEAT
		// AT every back step increment? Or just keep the value of maximal stack count?
		// At every pop we decide which subtree was bigger?
		leftSubtreeSize++;
		node_pp = &(*node_pp)->mLeft_p;
	}

}

// With a helper function - no other way around - cannot create MaxDepth(Node<NodeData>* node_p = mRoot)
// default arguments can be a literal or a global scope
//https://stackoverflow.com/questions/32399730/default-arguments-as-non-static-member-variables/32399835

// Iteratively
// Morris traversal
// Adding to stack?
// In case of iterative method and the recirsive method there is a need to refer back to an object and accumulate
// Any optimization in case of big trees? For example the value in root and farthest current leaf says that there are
// no possibilities that in the other leafs will be something bigger

// Make the option template partial specialization XD


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
	BinarySearchTree<int> bst2;
	std::cout << sizeof(bst) << std::endl;

	bst.Insert(15);
	bst.Insert(7);
	bst.Insert(8);
	bst.Insert(3);
	bst.Insert(5);
	bst.Insert(6);

	bst2.Insert(7);
	bst2.Insert(5);
	bst2.Insert(1);
	bst2.Insert(6);
	bst2.Insert(9);
	bst2.Insert(8);

	std::cout << bst.MaxDepth() << " - here" << std::endl;
	std::cout << bst2.MaxDepth() << " - here2" << std::endl;

	outer test;
	std::cout << sizeof(outer) << std::endl;

	test.a = 7;

	outer::inner test2;

	return 0;
}
