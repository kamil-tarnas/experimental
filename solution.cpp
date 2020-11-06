int solution(vector<int> &A) {
    bool* tablica = new bool[A.size()]();
    
    for (auto& elem: A)
    {
        if (elem > 0 && elem <= A.size())
        {
            tablica[elem - 1] = true;
        }
    }
    
    for (int i = 0; i < A.size(); ++i)
    {
        if (tablica[i] == false)
        {
            return i + 1;
        }
    }
    return A.size() + 1;
}  
