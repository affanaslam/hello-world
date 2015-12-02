#include <iostream>
#include <cstddef>
#include <stdlib.h>
#include <vector>
#include <algorithm>    // std::swap
#include <map>

using namespace std;


template<class VecType = int>
class MyVector
{
public:
    int v_size; //the index
    int m_currentSize;
    int m_index;
    VecType *m_pData;


    MyVector(int max_elements=3) //set constructor to size 100
    {
        v_size = max_elements;
        m_pData = new VecType[max_elements];
        m_currentSize = -1;
        m_index = m_currentSize + 1;
    }

    ~MyVector (){

            delete [] m_pData;
    }

    int GetLength()
    {
        return m_currentSize + 1; // Add 1 as it is zero based index
    }

    // Adds the element at the end
    bool AddElement(VecType data)
    {
        //index
        m_currentSize++;
        if(m_currentSize - 1 >= v_size){
            VecType* m_pData2 = new VecType[v_size*2];
            for (int i = 0; i <= v_size; i++) {
                m_pData2[i] = m_pData[i];

            }

            delete  m_pData;
            m_pData = m_pData2;
            v_size = v_size + v_size;
           }
                                             //return false; // Maximum threshold reached
        m_pData[m_currentSize] = data;


        return true;
    }

    // 0 based index
    bool insertElement(int pos, VecType data) //PUSH
    {
        if(pos <= m_currentSize)
        {
            m_pData[pos] = data;
            return true;
        }
        return false;
    }


   void pop(int i)

{
    cout << m_currentSize << endl;
    cout << v_size;
    for (int x = i + 1; x <= m_currentSize; x++) {
        m_pData[x - 1] = m_pData[x];
    }
    m_currentSize--;
}


    bool DeleteElement()
    {

        if(m_currentSize < 0)
            return false; // No elements in the vector
         m_currentSize--;
        return true;
    }




    bool clear() {

    for (int i = 0; i < v_size; i++)
        DeleteElement();

    }

    VecType operator [] (int index)
    {
        if(index > m_currentSize)
            throw -1;
        return m_pData[index];
    }

    void DisplayVector()
    {
        for(int i = 0; i < GetLength(); i++)
        {
            std::cout << m_pData[i];
            if(  i == GetLength() - 1)
                std::cout << "\n";
            else
                std::cout << ", ";
        }
    }


};



int main()
{
    MyVector<int> vec(3);

    vec.AddElement(12);
    vec.AddElement(13);
    vec.AddElement(14);
    vec.AddElement(15);
    vec.AddElement(15);
    //vec.insertElement(2,22.5);

   //vec.~MyVector();

    std::cout << "\n\nAfter adding four elements in the vector\n";
    vec.DisplayVector();

    cout << vec.v_size;

   //vec.~MyVector();

    //vec.pop(1);



    std::cout << "\n\nAfter deleting two elements in the vector\n";


    //vec.~MyVector();

    //vec.clear();

  //  vec.DeleteElement();void myvector::erase(int i)

  //  vec.DeleteElement();
    vec.DisplayVector();

    std::cout << "\n\nAfter adding three elements in the vector\n";
    vec.AddElement(22);
    vec.AddElement(22);
    vec.AddElement(22);
    for(int i = 0; i < vec.GetLength(); i++)
        std::cout << vec[i] << "\n";

    std::cout << "\n\n";

    return 0;
}
