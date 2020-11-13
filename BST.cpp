// 1. Move it outside of BinarySearchTree - make node not a nested class
// 2. Make Node a plain class rather than template class
// 3. template class nested in template class

// TODO: BST and DFS with a function pointer for an action to do

// DFT with a policy on a class enum non-type template parameter
// Type of DFS can be implemented using exceptions (?)

// TODO: Sort out the includes
#include <iostream>
#include <cstring>
#include <functional>
#include <cassert>

#define DEBUG

#ifdef DEBUG
#include <iostream>
#endif

//TODO: Copy-wise elements
// this header includes too much and element-wise copy will be probably compiled to memcpy like routine in asm

enum class OrderType
{
	PRE_ORDER,
	IN_ORDER,
	POST_ORDER
};

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
	// Constructor taking std::initializer_list for constructing the tree
	// Think of any possible hints and shortcuts that could be taken here
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

	//TODO: test those
	// This should be called only internally - given node_p it won't give good answer
	// based on classical "depth" definition - corrected already!!!
	// MaxDepth(Node<NodeData>) should be private here (?)
	// Node is an implementation detail and should not be visible to the customer of this code
	std::size_t MaxDepth(Node<NodeData>* node_p);
	std::size_t MaxDepth();
	// TODO: Given the data search for it and return back the depth of that argument
	std::size_t MaxDepth(const NodeData& data);

	std::size_t MaxDepth_iterative();

	// template and an argument for DFS type?
	//template <OrderType order> // std::function<void(Node<NodeData>*) should be generic!!
	// TODO: Version that instead of taking NodeData& runs from root on default
	BinarySearchTree<NodeData>& operator()(std::function<void(NodeData&)>); //std::function or some other callable as an argument?
	BinarySearchTree<NodeData>& operator_function_call_internal(Node<NodeData>* node_p, std::function<void(NodeData&)>);

	//TODO: Leaf to leaf path

	//template <OrderType order>
	void Bfs();
	void Bfs_internal(Node<NodeData>* node_p);

	// TODO: Detach the destruction on other thread?
	// TODO: Clear() method?
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

template <typename NodeData>
void BinarySearchTree<NodeData>::Bfs()
{
	Node<NodeData>* node_p = mRoot;

	#ifdef DEBUG
	std::cout << "BFS: \n";
	#endif

	return BinarySearchTree<NodeData>::Bfs_internal(node_p);
	// ADL (is it really it?) can figure out the namespace - the code below is perfectly fine
	// return Bfs_internal(node_p);
}

template <typename NodeData>
void BinarySearchTree<NodeData>::Bfs_internal(Node<NodeData>* node_p)
{
	if (!node_p)
	{
		return;
	}

	#ifdef DEBUG
	std::cout << node_p->mData << "\n";
	#endif

	BinarySearchTree<NodeData>::Bfs_internal(node_p->mLeft_p);
	BinarySearchTree<NodeData>::Bfs_internal(node_p->mRight_p);

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
	// TODO: 'if' statement could be merged into one, but it does not matter probably
	if (node_p == nullptr)
	{
		return 0;
	}
	if (node_p->mLeft_p == nullptr && node_p->mRight_p == nullptr)
	{
		return 0;
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
	//TODO: The common part could be wrapped in a subroutine that will be inlined (make sure that it is)
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
		return 1 + (leftSubtree > rightSubtree ? leftSubtree : rightSubtree);
	}
}

// TODO: Policy for allocating the stack on stack (sic!)
// TODO: Stress it with different extreme-valued parameters
// TODO: the same function with policy template argument of {iterative, recursive}
template <typename NodeData>
std::size_t BinarySearchTree<NodeData>::MaxDepth_iterative()
{
	Node<NodeData>** node_pp = &mRoot;

	// Allocate space for a stack of nodes
	// Push on stack the address of a node
	// 20 is an arbitrary number // TODO: Parametrize the 20 number
	Node<NodeData>* nodeStack = new Node<NodeData>*[20];
	std::size_t currentStackLimit = 20;
	std::size_t currentStackSize = 0;

	std::size_t leftSubtreeSize = 0;
	std::size_t rightSubtreeSize = 0;
	std::size_t treeDepth = 0;

	//TODO: count when going up the tree and count when going down?
	// currentMaxSubtreeSize -> incremented each time going down the tree and decremented during pop
	// maxSubtreeSize -> compared with currentMaxSubtreeSize when going back (popping from the stack)
	std::size_t currentSubtreeSize = 0;
	std::size_t maxSubtreeSize = 0;

	// TODO: Consider this expression
	while (*node_pp != nullptr) // TODO: Do it until *node_pp == mRoot coming back from right node
	{
		// GO LEFT, GO LEFT, IF LEFT IS NULLPTR, GO RIGHT, IF RIGHT IS NULL THEN POP
		// Need to keep the pointers because we need to go back in the tree
		// GO LEFT, IF NULLPTR POP AND GO RIGHT, SET THE POINTER TO LEFT, REPEAT
		// AT every back step increment? Or just keep the value of maximal stack count?
		// At every pop we decide which subtree was bigger?
		if ((*node_pp)->mLeft_p != nullptr) //TODO: Not correct - if we go back then this would go in circles
		{
			// Push the element on stack
			node_pp = &(*node_pp)->mLeft_p;
			//leftSubtreeSize++;
			currentSubtreeSize++;
		}
		else
		{
			// Pop the element from the stack and check right
			node_pp = &nodeStack[currentStackSize];
			currentStackSize--;

			if ((*node_pp)->mRight_p != nullptr) //TODO: Not correct - if we go back then this would go in circles
			{
				// Push the element on stack
				node_pp = &(*node_pp)->mLeft_p;
				//leftSubtreeSize++;
				currentSubtreeSize++;
			}

			if (currentSubtreeSize > maxSubtreeSize)
			{
				maxSubtreeSize = currentSubtreeSize;
			}
			currentSubtreeSize--;
		}

		// stack pointer being a pointer or var being a element number of array
		// the latter would probably exploit the data locality principle

		if (currentStackSize == currentStackLimit)
		{
			Node<NodeData>* oldStorage = nodeStack;
			Node<NodeData>* newStorage = new Node<NodeData>*[currentStackLimit * 2];
			std::memcpy(newStorage, oldStorage, sizeof(Node<NodeData>) * currentStackLimit);
			delete[] oldStorage;
			nodeStack = newStorage;
			currentStackLimit *= 2;
		}
	}

	// TODO: Need to return (after every pop?) the larger subtree path
	// After we have reached the root
	treeDepth = leftSubtreeSize > rightSubtreeSize ? leftSubtreeSize : rightSubtreeSize;
	return treeDepth;
}

template <typename NodeData>
BinarySearchTree<NodeData>& BinarySearchTree<NodeData>::operator()(std::function<void(NodeData&)> functor)
{
	Node<NodeData>* node_p = mRoot;
	// DFS pre-order
	// use(node_p);
	functor(node_p->mData);
	// pass the std::function
	BinarySearchTree<NodeData>::operator_function_call_internal(node_p->mLeft_p, functor);
	BinarySearchTree<NodeData>::operator_function_call_internal(node_p->mRight_p, functor);
	return (*this);
}

// TODO: Can return void? Return parameter not used at all?
template <typename NodeData>
BinarySearchTree<NodeData>&
	BinarySearchTree<NodeData>::operator_function_call_internal
		(Node<NodeData>* node_p, std::function<void(NodeData&)> functor)
{
	if (!node_p)
	{
		return (*this);
	}

	functor(node_p->mData);

	BinarySearchTree<NodeData>::operator_function_call_internal(node_p->mLeft_p, functor);
	BinarySearchTree<NodeData>::operator_function_call_internal(node_p->mRight_p, functor);
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
	// Example tree
	// compile time different instantiation of POD types? macro? template?
	// TODO: Any test-naming convention? pros? cons? and so on?
	BinarySearchTree<int> bst_leftDepthBiased_rightElementBiased;
	// Different insertion patterns // TODO: Should be tested in Insert() tests
	// BFI (breadth first insert) - insert in BFS manner
	// TODO: Any possible hints? Measure the time of insertion using this method versus other methods
	bst_leftDepthBiased_rightElementBiased.Insert(15);
	bst_leftDepthBiased_rightElementBiased.Insert(9);
	bst_leftDepthBiased_rightElementBiased.Insert(30);
	bst_leftDepthBiased_rightElementBiased.Insert(5);
	bst_leftDepthBiased_rightElementBiased.Insert(11);
	bst_leftDepthBiased_rightElementBiased.Insert(29);
	bst_leftDepthBiased_rightElementBiased.Insert(45);
	bst_leftDepthBiased_rightElementBiased.Insert(3);
	bst_leftDepthBiased_rightElementBiased.Insert(10);
	bst_leftDepthBiased_rightElementBiased.Insert(21);
	bst_leftDepthBiased_rightElementBiased.Insert(41);
	bst_leftDepthBiased_rightElementBiased.Insert(50);
	bst_leftDepthBiased_rightElementBiased.Insert(2);
	bst_leftDepthBiased_rightElementBiased.Insert(40);
	bst_leftDepthBiased_rightElementBiased.Insert(42);
	bst_leftDepthBiased_rightElementBiased.Insert(1);

	// Test MaxDepth(Node<>*) for partial depth

	// Test MaxDepth()
	auto value = bst_leftDepthBiased_rightElementBiased.MaxDepth();
	assert(("testTernary failed! 231_b3 != 28", value == std::size_t{5}));




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

	bst.Bfs();

	#ifdef DEBUG
	// TODO: Make the bst deduce the argument of std::function to be the same as NodeData (already deduced?)
	// Can implicitly pass the parameters?
	// Immediately short-invoked lambda creation -
	// TODO: The call could look like: bst([](int&){std::cout << "Woo\n";});
	bst([](int&){std::cout << "Woo\n";});
	#endif

	std::cout << bst.MaxDepth() << " - here" << std::endl;
	std::cout << bst2.MaxDepth() << " - here2" << std::endl;

	outer test;
	std::cout << sizeof(outer) << std::endl;

	test.a = 7;

	outer::inner test2;

	return 0;
}
