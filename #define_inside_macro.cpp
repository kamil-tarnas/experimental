// If the define is actually defined, the add the entry containing {define, value}

// TODO: Won't work
//#define ENTRY(define, value) \
//#ifdef(define) \
//{define, value}, \
//#endif

#define CONCAT2(x,y) x##y
#define CONCAT(x,y) CONCAT2(x,y)
#define ENTRY_YES(p1, p2) { p1 , p2 }
#define ENTRY_NO(p1)
#define IS_PAIR_HELPER(a, b, c, ...) c
#define IS_PAIR(...) IS_PAIR_HELPER(__VA_ARGS__, YES, NO)
#define ENTRY(pair) CONCAT(ENTRY_, IS_PAIR(pair))(pair)               //if ID expans to two values then YES
//-> CONCAT(ENTRY_, IS_PAIR(ID_1))(ID_1) -> CONCAT(ENTRY_, IS_PAIR_HELPER(ID_1, YES, NO))(ID_1)
//-> CONCAT(ENTRY_, IS_PAIR_HELPER(78723649, 1, YES, NO))(ID_1) -> CONCAT(ENTRY_, YES)(ID_1)
//-> ENTRY_YES(ID_1) -> ENTRY_YES(78723649, 1) -> {78723649, 1}


// NOT READY YET!!!!!!!!
// if define is defined then firstArg would be a define and secondArg would be the value DEFINED
//
//#define IS_NOT_DEFINED_helper(firstArg, secondArg, lastArg, ...) lastArg
//#define IS_NOT_DEFINED(...) IS_NOT_DEFINED_helper(__VA_ARGS__, NOT_DEFINED, DEFINED)
//#define NUMERAL_SYSTEM_DEFINED(numeral_system)
//#define NUMERAL_SYSTEM_NOT_DEFINED(numeral_system)

#define ID_1 78723649, 1
#define ID_3 2347602, 3

class valueList
{
public:
	int define;
	int value;
};

// TODO: Won't work
//static const valueList[] =
//{
//		ENTRY(ID_1, 1)
//		ENTRY(ID_2, 2)
//		ENTRY(ID_3, 3)
//		ENTRY(ID_4, 4)
//		ENTRY(ID_5, 5)
//};

static const valueList secondList[] =
{
    ENTRY( ID_1 ),
    ENTRY( ID_2 )
    ENTRY( ID_3 )
    ENTRY( ID_4 )
    ENTRY( ID_5 )
};




//static const valueList list[] =
//{
//#if defined(ID_1)
//		{ID_1, 1},
//#endif
//#if defined(ID_2)
//		{ID_2, 2},
//#endif
//#if defined(ID_3)
//		{ID_3, 3},
//#endif
//#if defined(ID_4)
//		{ID_4, 4},
//#endif
//#if defined(ID_5)
//		{ID_5, 5},
//#endif
//};

int main()
{
	return 0;
}

