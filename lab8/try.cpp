#include <bits/stdc++.h>
#include "Heap.cpp"

using namespace std;

int main()
{
    Heap<int> *h = new Heap<int>();
    // h->insert(27);
    // h->insert(34);
    // h->insert(78);
    // h->insert(23);
    // h->insert(92);
    // h->insert(102);
    // h->insert(1);
    h->insert(102);
    h->insert(92);
    h->insert(78);
    h->insert(34);
    h->insert(27);
    h->insert(92);
    h->insert(34);
    h->insert(23);
    h->insert(1);
    h->printHeap(h->getroot());
    // h->displayAboveThresh(25);
}