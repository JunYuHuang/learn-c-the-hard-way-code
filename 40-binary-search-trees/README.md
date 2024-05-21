# Exercise 39: Binary Search Trees

## Notes

- BSTs: an alt for hashmaps
  - like a triple linked list
  - double linked list is like a tree with 1 trunk
  - is a binary tree with a unique property:
    - for every node `n` in the tree,
      - `n.left.value` <= `n.right.value` and recursively
  - pros
    - fast insert
    - fast search
  - cons
    - hard to balance
    - hard to delete
  - traversal: DFS vs BFS
- misc
  - VOD review my recorded code review sessions to improve fast
  - BSTs recursive traversal can be broken via data that cause a stack overflow

## Extra Credit

- [ ] ~~1. There's an alternative way to do this data structure without using recursion. The Wikipedia page shows alternatives that don't use recursion but do the same thing. Why would this be better or worse?~~
  - Skipped
- [ ] ~~2. Read up on all of the different but similar trees you can find. There are AVL trees (named after Georgy Adelson-Velsky and E.M. Landis), red-black trees, and some non-tree structures like skip lists.~~
  - Skipped
