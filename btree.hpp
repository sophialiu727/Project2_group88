#include <iostream>
#include <string>
#include <vector>
#include <cmath>

template <typename T>
void shiftRight(T* arr, int i, int& size){
    for(int index = size - 1; index >= i ; index--){
        arr[index + 1] = arr[index];
    }
    size++;
}

template <typename T>
void shiftLeft(T* arr, int i, int& size){
    for(; i < size -1 ; i++){
        arr[i] = arr[i + 1];
    }
    size --;
}

template<typename T>
class node{
    public:
    node<T>** children; //children array
    T** data; //array of data

    int m; //tree order
    
    int min; //minimum number of keys

    bool leaf; //whether node is leaf or not

    int num_keys; //number of keys

    node(int m, bool leaf = true)
        : m(m), min(ceil(m/2.0) - 1), leaf(leaf), num_keys(0){
            //allocates memory for the array
            children = new node<T>*[m + 1]();
            data = new T*[m];
        }

    node<T>* insert(T* element, T*& up){
        int i  = 0;
        //find position of element
        while(i < num_keys && element -> key > data[i] -> key){
            ++i;
        }

        //if you are inserting into a leaf node, you shift all the data to the right and then insert the element
        if(leaf == true){
            shiftRight<T*>(data, i ,num_keys);
            data[i] = element;

            // if the number of keys is equal to m , the data is full and thus the tree needs to split
            if(num_keys == m){
                return split(up);
            }
        }
        else{
            node<T>* right = children[i] -> insert(element, up);

            if(right){
                shiftRight<T*>(data, i, num_keys);
                data[i] = up;

                int _num_keys = num_keys;
                shiftRight<node<T>*>(children, i+1, _num_keys);
                children[i + 1] = right;

                if(num_keys == m){
                    return split(up);
                }
            }
        }

        up = nullptr;
        return nullptr;
    }

    T* search(int key){
        int i = 0;
        for(; i < num_keys && key >= data[i] -> key; ++i){
            if(key == data[i] -> key){
                return data[i];
            }
        }

        if(leaf){
            return nullptr;
        }
        else{
            return children[i] -> search(key);
        }
    }

    void traverse(){
        for(int i = 0; i < num_keys ; ++i){
            if(!leaf){
                children[i] -> traverse();
            }
            std::cout << " " << data[i] -> key;
        }
        if(!leaf){
            children[num_keys] -> traverse();
        }
    }

    private:
    node<T>* split(T*& up){
        node<T>* right = new node<T>(m, leaf);

        up = data[min];
        data[min] = nullptr;

        for(int i = min + 1; i < num_keys; i++){
            right -> data[i - min - 1] = data[i];
            data[i] = nullptr;
            right -> num_keys++;
        }
        num_keys -= right -> num_keys + 1;

        if(!leaf){
            for(int i = min + 1; i <= m; i++){
                right ->children [i - min - 1] = children[i];
                children[i] = nullptr;
            }
        }

        return right;
    }
};

template<typename T>
class BTree{
    public:
    int m; //degree of the tree
    node<T>* root; //root
    
    BTree(int order):
        m(order){
            root = new node<T>(m, true);
            root -> min = 1;
        }

    void traverse(){
        root -> traverse();
    }

    void insert(T* element){
        T* up = nullptr;
        node<T>* right = root -> insert(element, up);

        if(right){
            node<T>* newRoot = new node<T>(m, false);

            newRoot -> data[0] = up;
            newRoot -> num_keys = 1;

            newRoot-> children[0] = root;
            newRoot -> children [1] = right;

            root = newRoot;
        }
    }

    T*& operator[](int key){
        return root -> search(key);
    }
};
