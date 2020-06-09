// The purpose is tho show that the rule of reverse-order destruction applies also to global objects and static storage duration object in general
// It applies also to static local variable, which initialization might depend on the program run (is not deterministic - might depend on the order of function calls)
//
// std::atexit()

// Check the initialization of static objects and the order of destruction

int main()
{
   return 0;
}
