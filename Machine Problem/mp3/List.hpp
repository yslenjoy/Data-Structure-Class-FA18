/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */
using namespace std;

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(tail_->next);
}

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <typename T>
List<T>::~List() {
  /// @todo Graded in MP3.1
  _destroy();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  // ListNode* cur = head_;
  while (head_ != NULL) {
    ListNode* del_cur;
    del_cur = head_;
    head_ = head_->next;
    delete del_cur;
  }
  head_ = NULL;
  tail_ = NULL;
  length_ = 0;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * inserted = new ListNode(ndata);
  if (head_ != NULL) {
    inserted->next = head_;
    inserted->prev = NULL;
    head_->prev = inserted;
    head_ = inserted;
  } else {
    head_ = inserted; // inserted should be assigned first to head and then do the prev and next thing since the original head is NULL
    head_->prev = NULL;
    head_->next = NULL;
    tail_ = head_;
  }
  length_++;
  inserted = NULL;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode * inserted = new ListNode(ndata);
  if (tail_ != NULL) {
    tail_->next = inserted;
    inserted->prev = tail_;
    inserted->next = NULL;
    tail_ = inserted;
  } else {
    tail_ = inserted; // inserted should be assigned to head first
    tail_->next = NULL;
    tail_->prev = NULL;
    head_ = tail_;
  }
  length_++;
  inserted = NULL;
}

/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.1
  if (startPoint == endPoint || startPoint == NULL || endPoint == NULL) {
    return;
  }

  ListNode* givenStart = startPoint;
  ListNode* givenStart_prev = startPoint->prev;
  // ListNode* givenEnd = endPoint;
  ListNode* givenEnd_next = endPoint->next;

  ListNode* current = startPoint;
  while (current != endPoint) {
    ListNode* tmpNode1 = current->prev;
    current->prev = current->next;
    current->next = tmpNode1;
    current = current->prev;
  }
  ListNode* tmpNode2 = current->prev;
  current->prev = givenStart_prev;
  current->next = tmpNode2;
  // givenEnd_next->prev = startPoint; // this line should after check givenEnd_next is NULL
  givenStart->next = givenEnd_next;
  // givenStart_prev->next = current; // // this line should after check givenStart_prev is NULL


  if (givenStart_prev == NULL) {
    // starts from head
    head_ = current; // right now current = endpoint
  } else {
    // givenStart_prev = givenStart->next;
    givenStart_prev->next = current;
  }
  if (givenEnd_next == NULL){
    tail_ = givenStart; // givenStart is the same as startpoint
  } else {
    // givenEnd_next->prev = endPoint;
    givenEnd_next->prev = startPoint;
  }
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
typename List<T>::ListNode * List<T>::getNode(int n) { // helper function: get the listNode at index n, n should be less than the size of the linked list;
  ListNode* a = head_;
  for (int i = 0; i < n; i++) {
     // the upper limit is n, rather than (n+1) because the nature of the implementation of next line (a = a->next)
    a = a->next;
  }
  return a;
}

template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.1
  int i = 0;
  int size = this->size();
  if (n > size) { // special case 1
    this->reverse();
    return;
  }
  if (n == 0) { // special case 2
    return;
  }
  while (i+n-1 < size-1) {
    ListNode* s = head_;
    ListNode* e = head_;
    if (i != 0) { // avoid the case that the following for loop is useless when i = 0
      // for (int j = 0; j < i; j++) { // find the ListNode with index i
      //   s = s->next;
      // }
      s = this->getNode(i);
    }
    // for (int j = 0; j < i+n-1; j++) { // find the ListNode with index i+n-1
    //   e = e->next;
    // }
    e = this->getNode(i+n-1);
    this->reverse(s, e);
    // this->reverse(i, i+n-1);
    i += n;
  }
  ListNode* s = head_;
  // for (int j = 0; j < i; j++) { // find the ListNode with index i
  //   s = s->next;
  // }
  s = this->getNode(i);
  // for (int j = 0; j < size-1; j++) { // this for loop is optional since this is the case that (size-1) is the tail_
  //   e = e->next;
  // }
  this->reverse(s, tail_);
  // this->reverse(i, size-1);
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <typename T>
void List<T>::waterfall() {
  /// @todo Graded in MP3.1
  /// My implementation has segfault in the bookmark line
  ListNode* cur = head_;
  while (cur->next != NULL) {
    ListNode* prevI = cur->prev;
    ListNode* nextI = cur->next;
    ListNode* tmpCur = cur;
    tmpCur->prev = prevI;
    if (nextI->next == NULL) { // also need to check this to avoid segfault
      return;
    }

    cur->next = nextI->next;
    cur = nextI->next;
    tmpCur->next = cur;
    cur->prev = tmpCur;

    tail_->next = nextI;
    nextI->prev = tail_;
    nextI->next = NULL;
    tail_ = nextI;
  }
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <typename T>
List<T> List<T>::split(int splitPoint) {
    if (splitPoint > length_)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode * secondHead = split(head_, splitPoint);

    int oldLength = length_;
    if (secondHead == head_) {
        // current list is going to be empty
        head_ = NULL;
        tail_ = NULL;
        length_ = 0;
    } else {
        // set up current list
        tail_ = head_;
        while (tail_ -> next != NULL)
            tail_ = tail_->next;
        length_ = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head_ = secondHead;
    ret.tail_ = secondHead;
    if (ret.tail_ != NULL) {
        while (ret.tail_->next != NULL)
            ret.tail_ = ret.tail_->next;
    }
    ret.length_ = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.2
  if (start == NULL){
        return NULL;
    }
    ListNode* new_head = start;
    for (int ct=0; ct<splitPoint-1; ct++){
        new_head = new_head->next;
    }
    ListNode* output = new_head->next;
    output->prev = NULL;
    new_head->next->prev = NULL;
    new_head->next = NULL;
    return output;

  // my own implementation below is the reason for mergesort function goes into infinite loop, detailed and specific reason is not well thought
  
  // ListNode* cur = head_;
  //
  // if (start == NULL) {
  //   return NULL;
  // }
  // for (int i = 0; i < splitPoint - 1; i++) {
  //   if (cur->next == NULL) { // when the step is beyond the linked list range
  //     break;
  //   }
  //   cur = cur->next;
  // }
  // ListNode* nextOne = cur->next;
  // if (nextOne == NULL) {
  //   return start;
  // }
  // nextOne->prev = NULL;
  // cur->next = NULL;
  //
  // return nextOne;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2

  if (first == NULL && second == NULL) {
    return NULL;
  }
  if (first == NULL) {
    return second;
  }
  if (second == NULL) {
    return first;
  }
  // cout << "here infinite!!!!!-----" << endl;
  ListNode* n1 = first;
  ListNode* n2 = second;
  ListNode* cur;

  // cout<< "n1 data (before while): " << n1->data << endl;
  // cout<< "n2 data (before while): " << n2->data << endl;
  if (n1->data < n2->data) {
    cur = n1;
    n1 = n1->next;
  } else {
    cur = n2;
    n2 = n2->next;
  }
  // cout<< "cur data: " << cur->data << endl;

  while (n1 != NULL || n2 != NULL) {
    if (n1 == NULL || (n2 != NULL && (n2->data < n1->data))) {
      // cout<< "n2 data: " << n2->data << endl;
      cur->next = n2;
      cur->next->prev = cur;
      cur = cur->next;
      n2 = n2->next;
    } else {
      // cout<< "n1 data: " << n1->data << endl;
      cur->next = n1;
      cur->next->prev = cur;
      cur = cur->next;
      n1 = n1->next;
      // if (n1 == nullptr)
      //   cout << "n1 null" << endl;
    }
  }

  if (first->data < second->data) {
    // cout << "merge helper function return: (first)" << endl;
    // this->printListNode(first);
    return first;
  } else {
    // cout << "merge helper function return: (second)" << endl;
    // this->printListNode(second);
    return second;
  }
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <typename T>
void List<T>::sort() {
    if (empty())
        return;
    head_ = mergesort(head_, length_);
    tail_ = head_;
    while (tail_->next != NULL)
        tail_ = tail_->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if (start == NULL) {
    return NULL;
  }
  if (chainLength == 0) {
    return start;
  }
  if (chainLength == 1) { // rather than check the size of the ListNode
    // cout << "here: length = 1--------" << endl;
    return start;
  }
  // cout << "chainLength: " << chainLength << endl;
  int l = int(chainLength / 2);
  // cout << "l: " << l << "-----" << endl;
  ListNode* left = start;
  ListNode* right = split(start, l);
  // cout << "merge left====" << endl;
  // this->printListNode(left);
  // cout << "merge right====" << endl;
  // this->printListNode(right);
  // cout<< "merge result: =================" << endl;
  // this->printListNode(merge(mergesort(left, l), mergesort(right, chainLength - l)));
  return merge(mergesort(left, l), mergesort(right, chainLength - l));
}

template <typename T>
void List<T>::printListNode(ListNode *head) {
  if (head == NULL) {
    cout << "Empty list" << endl;
    return;
  }

  ListNode *temp = head;
  int count = 0;
  while(temp != NULL) {
    cout << "Node " << count << ": " << temp ->data << endl;
    count++;
    temp = temp->next;
  }
}

/**
 * Code Summary:
 *
 * 1. Merge() function:
 *    1) Not returning the current node, but return first or second
 *    based on its value
 *    2) The smartest step: cur->next = n1; cur->next->prev = cur:
 *       don’t need to care whether it’s n1 or n2:
 *       *****: now see the power of pointers
 *       Some prev pointer was temporary left, but it can be reconnected using the code above
 *    3) Another smart thought: the if condition considering the end of
 *       n1 and n2:
 *       n2 == NULL, go n1;
 *       n1 == NULL, go n2
 *       n2 < n1, go n2;
 *      one line code can combine this case together.
 *    4) the head and tail of the returning linklist is not necessarily
 *       needed based on the requirement
 * 2. Mergesort() function:
 *    the reason for mergesort() function goes into an infinite loop is because of my own implementation of split() function
 */
