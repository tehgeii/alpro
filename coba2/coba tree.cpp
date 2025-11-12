#include <iostream>
using namespace std;

struct ListNode {
    char val;
    ListNode* prev;
    ListNode* next;

    ListNode(char x) : val(x), prev(nullptr), next(nullptr) {}
};


int main() {
    ListNode* head = new ListNode('H'); //root
    head->prev = new ListNode('A'); //child left
    head->next = new ListNode('K'); //child left
    head->prev->next = new ListNode('C'); //LEAF left
    head->prev->prev = new ListNode('B');
    head->prev->next->prev = new ListNode('F');
    head->prev->next->next = new ListNode('G');


    cout<< "root : "<< head->val << endl;
    cout<< "child 1 (left) : "<< head->prev->val << endl;
    cout<< "child 2 (right) : "<< head->next->val << endl;
    cout<< "leaf kiri 1 : "<< head->prev->next->val << endl;
    cout<< "leaf kanan 1 : " << head->prev->prev->val << endl;
    cout<< "leaf kiri 2: " << head->prev->next->prev->val << endl;
    cout<< "leaf kanan 2: " << head->prev->next->next->val << endl;

    cout<< "Preorder" << endl;
    cout<< head->val << " " << head->prev->val << " " << head->prev->prev->val << " " << head->prev->next->val << " " << head->prev->next->prev->val << " " << head->prev->next->next->val << " " << head->next->val << endl;
    
    cout<< "Inorder" << endl;
    cout<< head->prev->prev->val << " " << head->prev->val << " " << head->prev->next->val << " " << head->prev->next->prev->val << " " << head->prev->next->next->val << " " << head->val << " " << head->next->val << endl;

    cout<< "Postorder" << endl;
    
    
    return 0;
}