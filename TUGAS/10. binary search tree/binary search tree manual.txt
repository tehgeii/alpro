//ada beberapa angka: 7, 5, 12, 3, 6, 1, 4, 9
//dengan algoritma: inorder, preorder, dan postorder

#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode* prev;
    ListNode* next;

    ListNode(int x) : val(x), prev(nullptr), next(nullptr) {}
};


int main() {
    ListNode* head = new ListNode(7); //root
    head->prev = new ListNode(5); //child left
    head->next = new ListNode(12); //child left
    head->prev->next = new ListNode(6); //LEAF left
    head->prev->prev = new ListNode(3);
    head->prev->prev->prev = new ListNode(1);
    head->prev->prev->next = new ListNode(4);
    head->next->prev = new ListNode(9);


    cout<< "root : "<< head->val << endl;
    cout<< "child 1 (left) : "<< head->prev->val << endl;
    cout<< "child 2 (right) : "<< head->next->val << endl;
    cout<< "leaf kiri 1 : "<< head->prev->prev->prev->val << endl;
    cout<< "leaf kanan 1 : " << head->prev->prev->next->val << endl;
    cout<< "leaf kiri 2 : " << head->prev->next->val << endl;
    cout<< "leaf kanan 2 : " << head->next->prev->val << endl;

    cout<< "Preorder" << endl;
    cout<< head->val << " " << head->prev->val << " " << head->prev->prev->val << " " << head->prev->prev->prev->val << " " << head->prev->prev->next->val << " " << head->prev->next->val << " " << head->next->val << " " << head->next->prev->val << endl;
    
    cout<< "Inorder" << endl;
    cout<< head->prev->prev->prev->val << " " << head->prev->prev->val << " " << head->prev->prev->next->val << " " << head->prev->val << " " << head->prev->next->val << " " << head->val << " " << head->next->prev->val << " " << head->next->val << endl;

    cout<< "Postorder" << endl;
    cout<< head->prev->prev->prev->val << " " << head->prev->prev->next->val << " " << head->prev->prev->val << " " << head->prev->next->val << " " << head->prev->val << " " << head->next->prev->val << " " << head->next->val << " " << head->val << endl;    
    
    return 0;
}